/*
 * serial.cpp
 *
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;

#include "tty.h"
#include "gets.h"
#include "string.h"
#include <stdlib.h>
#include "chprintf.h"
#include "version.h"
#include "modbus.h"
#include "lcd.h"
#include "stdio.h"
#include "externRegistros.h"
#include "dispositivos.h"

extern "C" {
    void initHM10(void);
    void initSerial(void);
}
static const SerialConfig ser_cfg = {115200, 0, 0, 0, };

uint8_t idEnvio = 2;

#define ttyHM10 &SD6

//extern uint32_t modbusSpeed[10]; // {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
//extern char *modbusSpeedStr[10];// = {"300", "600", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"};
//extern char *modoStr[4]; // {"manual","modbus"};
extern char *cocheStr[5]; // {"desconocido", "desconectado", "conectado","pide","pide vent."};
//extern char *ctrlContactStr[3];// = {"monofasico","mono-tri","trifasico"};
//extern char *medStr[3];// = {"sdm120ct","sdm630ct"};

extern medida *Ia;
extern medida *Ptot;
extern medida *kWhActual;
extern medida *kWhIniCarga;

uint8_t modoDebug;
bool sdHM10open = false;
bool hayConectadoHM10;

extern uint8_t hayW25q16;
thread_t *thrHM10 = NULL;
thread_t *thrConexHM10 = NULL;


static const SerialConfig ser_cfg9600 = {9600, 0, 0, 0, };//{115200, 0, 0, 0, };
static const SerialConfig ser_cfg19200 = {19200, 0, 0, 0, };//{115200, 0, 0, 0, };



extern modbusSlave *controlMB;

/*
 * Las ordenes a HM10 deben terminar en 0D+0A
   Dialogo tipico:
   => AT\r\n
      OK
   => AT+BAUD\r\n
      +BAUD=5    (5=19200, 4=9800)
   => AT+NAME\r\n
      +NAME=Pozo
   => AT+RESET\r\n

 */
uint8_t testHM10(char buffer[], uint8_t sizeBuffer)
{
    uint8_t huboTimeout;
    // devuelve 1 si hay alguien, 2 si no hay nadie y esta a 19200 y 3 idem a 9600
    // compruebo si el modulo esta a 19200
    sdStart(ttyHM10, &ser_cfg19200);
    // Veo si hay alguien conectado
    chprintf((BaseSequentialStream*) ttyHM10,"AT\r\n");
    chgetsNoEchoTimeOut((BaseChannel *) ttyHM10, (uint8_t *) buffer, sizeBuffer, TIME_MS2I(100), &huboTimeout);
    if (strstr(buffer,"OK"))
        return 2;  // no hay nadie, y modulo a 19200
    sdStop(ttyHM10);
    sdStart(ttyHM10, &ser_cfg9600);
    chprintf((BaseSequentialStream*) ttyHM10,"AT\r\n");
    chgetsNoEchoTimeOut((BaseChannel *) ttyHM10, (uint8_t *) buffer, sizeBuffer, TIME_MS2I(100), &huboTimeout);
    if (strstr(buffer,"OK"))
        return 3;  // no hay nadie, y modulo a 9600
    // debe haber alguien conectado, lo dejo en 19200
    sdStop(ttyHM10);
    sdStart(ttyHM10, &ser_cfg19200);
    chprintf((BaseSequentialStream*) ttyHM10,"\nHola\n");
    return 1;
}

void initSerialHM10(void) {
    uint8_t huboTimeout;
    char buffer[20];
    char bufferLCD[30];

    palClearLine(LINE_TX6);
    palSetLine(LINE_RX6);
    palSetLineMode(LINE_RX6, PAL_MODE_ALTERNATE(8));
    palSetLineMode(LINE_TX6, PAL_MODE_ALTERNATE(8));

    //chprintf((BaseSequentialStream*) ttyHM10,"AT+PIO11\r\n"); // el led debe replicar el estado de conexion
    uint8_t estadoHM10 = testHM10(buffer,sizeof(buffer));
    if (estadoHM10 == 1)  // debe haber alguien conectado, todo esta ok
        return;
    if (estadoHM10 == 3) // esta a 9600 => paso el modulo a 19200
    {
        chprintf((BaseSequentialStream*) ttyHM10,"AT+BAUD5\r\n"); // 4=>9600, 5=>19200
        chgetsNoEchoTimeOut((BaseChannel *) ttyHM10, (uint8_t *) buffer,sizeof(buffer), TIME_MS2I(100), &huboTimeout);
//        chLcdprintfFila(3,"Pasado HM10 a 19200");
        sdStop(ttyHM10);
        sdStart(ttyHM10, &ser_cfg19200);
        chThdSleepMilliseconds(100);
    }
    limpiaBuffer((BaseChannel *) ttyHM10);
    chprintf((BaseSequentialStream*) ttyHM10,"AT+NAME\r\n");
    chgetsNoEchoTimeOut((BaseChannel *) ttyHM10, (uint8_t *) buffer,sizeof(buffer), TIME_MS2I(100), &huboTimeout);
    if (!strstr(buffer,"AT+NAME"))
    {
        buffer[13] = (char) 0;
        snprintf(bufferLCD,sizeof(bufferLCD),"HM10: %s",&buffer[6]);
        ponEnColaLCD(3,bufferLCD);
    }
}


void ajustaNumero(SerialDriver *sdCOM, const char *desc, holdingRegisterInt *holdReg)
{
    int16_t result;
    uint32_t opcion;
    result = preguntaNumeroHM10((BaseChannel *) sdCOM, desc, &opcion, holdReg->getValorMin(), holdReg->getValorMax());
    if (result != 0)
        return;
    holdReg->setValorInterno((uint16_t) opcion);
    controlMB->escribeHR(false);
}

void ajustaNumeroFloat(SerialDriver *sdCOM, const char *desc, holdingRegisterFloat *holdReg)
{
    int16_t result;
    float opcion;
    result = preguntaNumeroHM10Float((BaseChannel *) sdCOM, desc, &opcion, holdReg->getValorMin(), holdReg->getValorMax());
    if (result != 0)
        return;
    holdReg->setValor(opcion);
//    controlMB->escribeHR(holdReg);
}

void ajustaNumeroEscala(SerialDriver *sdCOM, const char *desc, holdingRegisterFloat *holdReg)
{
    int16_t result;
    float opcion;
    result = preguntaNumeroHM10Float((BaseChannel *) sdCOM, desc, &opcion, holdReg->getValorMin(), holdReg->getValorMax());
    if (result != 0)
        return;
    holdReg->setValor(opcion);
}

/*
 * MENUS
 */

uint8_t ajustaSeleccionInt2Ext(SerialDriver *sdCOM, holdingRegisterInt2Ext *regOpcHR)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    for (uint16_t pos=1; pos<=regOpcHR->getNumOpciones();pos++)
        chprintf(ttyOpciones,"%d: %d\n", pos-1, regOpcHR->getValor(pos-1));
    chprintf(ttyOpciones,"%d Volver\n",regOpcHR->getNumOpciones());
    limpiaBuffer((BaseChannel *) ttyHM10);
    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Dime opcion", &opcion, 0, regOpcHR->getNumOpciones());
    if (result != 0 || (result==0 && opcion==regOpcHR->getNumOpciones()))
        return 1;
    regOpcHR->setValor(regOpcHR->getValor(opcion));
    return 0;
}

uint8_t ajustaSeleccion(SerialDriver *sdCOM, holdingRegisterOpciones *regOpcHR)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    for (uint16_t pos=1; pos<=regOpcHR->getNumOpciones();pos++)
        chprintf(ttyOpciones,"%d: %s\n", pos-1, regOpcHR->getDescripcion(pos-1));
    chprintf(ttyOpciones,"%d Volver\n",regOpcHR->getNumOpciones());
    limpiaBuffer((BaseChannel *) ttyHM10);
    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Dime opcion", &opcion, 0, regOpcHR->getNumOpciones());
    if (result != 0 || (result==0 && opcion==regOpcHR->getNumOpciones()))
        return 1;
    regOpcHR->setValor(opcion);
    return 0;
}

void ajustaMedidor(SerialDriver *sdCOM)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    while (true)
     {
         chprintf(ttyOpciones,"\n");
         chprintf(ttyOpciones,"1 Modelo medidor (%s)\n",medModeloHR->getDescripcion());
         chprintf(ttyOpciones,"2 Id modbus (%d)\n",medIdHR->getValor());
         chprintf(ttyOpciones,"3 Baud (%d)\n",medBaudHR->getValor());
         chprintf(ttyOpciones,"4 Volver\n");
         limpiaBuffer((BaseChannel *) ttyHM10);
         result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 4);
         chprintf(ttyOpciones,"\n");
         if (result != 0 || (result==0 && opcion==4))
             return;
         if (opcion==1)
         {
             ajustaSeleccion(sdCOM, medModeloHR);
         }
         if (opcion==2)
         {
             ajustaNumero(ttyHM10, "ID MB medidor", medIdHR);
         }
         if (opcion==3)
         {
             ajustaSeleccionInt2Ext(sdCOM, medBaudHR);
         }
     }
}


void ajustaOrdenador(SerialDriver *sdCOM)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    while (true)
     {
         chprintf(ttyOpciones,"\n");
         chprintf(ttyOpciones,"1 Id MB cargador (%d)\n",ordenIdHR->getValor());
         chprintf(ttyOpciones,"2 Baud (%d)\n",ordenBaudHR->getValor());
         chprintf(ttyOpciones,"3 Timeout modbus (%d s)\n",timeOutControlHR->getValor());
         chprintf(ttyOpciones,"4 Volver\n");
         limpiaBuffer((BaseChannel *) ttyHM10);
         result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 4);
         chprintf(ttyOpciones,"\n");
         if (result != 0 || (result==0 && opcion==4))
             return;
         if (opcion==1)
         {
             ajustaNumero(ttyHM10, "ID MB ordenador", medIdHR);
         }
         if (opcion==2)
         {
             ajustaSeleccionInt2Ext(sdCOM, ordenBaudHR);
         }
         if (opcion==3)
         {
             ajustaNumero(ttyHM10, "Timeout modbus", timeOutControlHR);
         }
     }
}


void ajustaContactores(SerialDriver *sdCOM)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    while (true)
     {
         chprintf(ttyOpciones,"\n");
         chprintf(ttyOpciones,"1 Num. contactores (%d)\n",numContactoresHR->getValor());
         chprintf(ttyOpciones,"2 Control (%s)\n",controlContactHR->getDescripcion());
         chprintf(ttyOpciones,"3 Volver\n");
         limpiaBuffer((BaseChannel *) ttyHM10);
         result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 3);
         chprintf(ttyOpciones,"\n");
         if (result != 0 || (result==0 && opcion==3))
             return;
         if (opcion==1)
         {
             ajustaNumero(ttyHM10, "Num. contactores", numContactoresHR);
         }
         if (opcion==2)
         {
             ajustaSeleccion(sdCOM, controlContactHR);
         }
     }
}



void ajustaSistElectrico(SerialDriver *sdCOM)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    while (true)
     {
         chprintf(ttyOpciones,"\n");
         chprintf(ttyOpciones,"1 Num. fases (%d)\n",numFasesHR->getValor());
         chprintf(ttyOpciones,"2 Num. contactores (%d)\n",numContactoresHR->getValor());
         chprintf(ttyOpciones,"3 Imax (%.1f A)\n",iMaxHR->getValor());
         chprintf(ttyOpciones,"4 Imin (%.1f A)\n", iMinHR->getValor());
         chprintf(ttyOpciones,"5 Volver\n");
         limpiaBuffer((BaseChannel *) ttyHM10);
         result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 5);
         chprintf(ttyOpciones,"\n");
         if (result != 0 || (result==0 && opcion==5))
             return;
         if (opcion==1)
         {
             ajustaNumero(ttyHM10, "Num. fases", numFasesHR);
         }
         if (opcion==2)
         {
             ajustaNumero(ttyHM10, "Num. contactores", numContactoresHR);
         }
         if (opcion==3)
         {
             ajustaNumeroFloat(ttyHM10, "Imax (A)", iMaxHR);
         }
         if (opcion==4)
         {
             ajustaNumeroFloat(ttyHM10, "Imin (mA)", iMinHR);
         }
     }
}


void ajustaControl(SerialDriver *sdCOM)
{
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    while (true)
     {
         chprintf(ttyOpciones,"\n");
         chprintf(ttyOpciones,"1 Modo control (%s)\n",modoHR->getDescripcion());
         chprintf(ttyOpciones,"2 Timeout modbus (%d s)\n",timeOutControlHR->getValor());
         chprintf(ttyOpciones,"3 control reles (%s)\n",controlContactHR->getDescripcion());
         chprintf(ttyOpciones,"4 Isp manual (%.1f A)\n", iSetPointManualHR->getValor());
         chprintf(ttyOpciones,"5 Volver\n");
         limpiaBuffer((BaseChannel *) ttyHM10);
         result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 5);
         chprintf(ttyOpciones,"\n");
         if (result != 0 || (result==0 && opcion==5))
             return;
         if (opcion==1)
         {
             ajustaSeleccion(sdCOM, modoHR);
         }
         if (opcion==2)
         {
             ajustaNumero(ttyHM10, "Timeout modbus (s)", timeOutControlHR);
         }
         if (opcion==3)
         {
             ajustaSeleccion(sdCOM, controlContactHR);
         }
         if (opcion==4)
         {
             ajustaNumeroEscala(ttyHM10, "Isp manual", iSetPointManualHR);
         }
     }
}


void listadoRegistros(SerialDriver *sdCOM)
{
    BaseSequentialStream *ttyOpciones = (BaseSequentialStream *) sdCOM;
    chprintf(ttyOpciones,"Hay %d HoldingRegisters:\n",controlMB->getNumHR());
    for (uint8_t reg=1;reg<=controlMB->getNumHR();reg++)
    {
        holdingRegister *hr = controlMB->getHoldingRegister(reg-1);
        chprintf(ttyOpciones,"%d: %s (%d)\n",reg-1,hr->getNombre(),hr->getValorInterno());
    }
    chprintf(ttyOpciones,"\nY %d InputRegisters:\n",controlMB->getNumIR());
    for (uint8_t reg=1;reg<controlMB->getNumIR();reg++)
    {
        inputRegister *ir = controlMB->getInputRegister(reg-1);
        chprintf(ttyOpciones,"%d: %s (%d)\n",reg-1,ir->getNombre(),ir->getValor());
    }
}



//
//void ajustaIDMed(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "ID MB medidor", &opcion, 1, 248);
//    if (result != 0)
//        return;
//    medIdHR->setValorInterno((uint16_t) opcion);
//    controlMB->escribeHR(false);
//}

//void ajustaBaudiosMed(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Baudios med", &opcion, 300, 115200);
//    if (result != 0)
//        return;
//    // chequeo si es valido
//    for (uint16_t pos=0; pos<10;pos++)
//        if (modbusSpeed[pos] == opcion)
//        {
//            medBaudHR->setValorInterno((uint16_t) pos);
//            controlMB->escribeHR(false);
//            sdStop(&SD2);
//            uint32_t  baudios = medBaudHR->getValor();
//            controlMB->startMBSerial(baudios);
//            return;
//        }
//    chprintf((BaseSequentialStream *)sdCOM,"ERROR: velocidad ilegal!!\n");
//}
//
//
//void ajustaIDOrd(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "ID MB ordenador", &opcion, 1, 248);
//    if (result != 0)
//        return;
//    ordenIdHR->setValorInterno((uint16_t) opcion);
//    controlMB->escribeHR(false);
//}
//
//void ajustaBaudiosOrd(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Baudios ord.", &opcion, 300, 115200);
//    if (result != 0)
//        return;
//    // chequeo si es valido
//    for (uint16_t pos=0; pos<10;pos++)
//        if (modbusSpeed[pos] == opcion)
//        {
//            medBaudHR->setValorInterno((uint16_t) pos);
//            controlMB->escribeHR(false);
//            sdStop(&SD2);
//            uint32_t  baudios = ordenBaudHR->getValor();
//            controlMB->startMBSerial(baudios);
//            return;
//        }
//    chprintf((BaseSequentialStream *)sdCOM,"ERROR: velocidad ilegal!!\n");
//}
//
//void ajustaTimeout(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Timeout para paso a manual (s)", &opcion, 1, 65000);
//    if (result != 0)
//        return;
//    timeOutControlHR->setValorInterno((uint16_t) opcion);
//    controlMB->escribeHR(false);
//}

//void ajustaPsetpoint(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "Set point de potencia", &opcion, 0, 100);
//    if (result != 0)
//        return;
//    saveHoldingRegister(HR_PSETPOINT, (uint16_t) opcion);
//}

//
//void ajustaModoControl(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    //{"Off", "Forzado On","setPoint","setPoint/calendario"};
//    BaseSequentialStream *ttyCOM = (BaseSequentialStream *) sdCOM;
//    chprintf(ttyCOM,"Modo de control:\n");
//    chprintf(ttyCOM,"0: Manual\n");
//    chprintf(ttyCOM,"1: Modbus\n");
//    chprintf(ttyCOM,"2: volver\n");
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "modo", &opcion, 0, 2);
//    if (result==2 || (result==0 && opcion==2))
//        return;
//    modoHR->setValorInterno((uint16_t) opcion);
//    controlMB->escribeHR(false);
//}



uint8_t cambiaNombreModulo(SerialDriver *sdCOM)
{
    uint8_t huboTimeout;
    char buffer[15];
    BaseSequentialStream *ttyCOM = (BaseSequentialStream *) sdCOM;
    chprintf(ttyCOM,"Nuevo nombre modulo (3-10 caracteres):");
    chgetsNoEchoTimeOut((BaseChannel *) sdCOM, (uint8_t *) buffer,sizeof(buffer), TIME_MS2I(20000), &huboTimeout);
    chprintf(ttyCOM,"\n");
    if (strlen(buffer)<3 || strlen(buffer)>10)
    {
        chprintf(ttyCOM,"Longitud erronea\n");
        return 0;
    }
    chprintf(ttyCOM,"Pongo nombre %s\n",buffer);
    chprintf(ttyCOM,"Desconectate de HM10 !!\n");
    chThdSleepMilliseconds(10000);
    // reseteamos el modulo
    chprintf((BaseSequentialStream *)ttyHM10,"AT+NAME%s\r\n",buffer);
    chThdSleepMilliseconds(100);
    chprintf((BaseSequentialStream *)ttyHM10,"AT+RESET\r\n");
    chThdSleepMilliseconds(100);
    chThdSleepMilliseconds(4000);
    return 1;
}


//
//void cambiaId(SerialDriver *sdCOM)
//{
//    int16_t result;
//    uint32_t opcion;
//    result = preguntaNumeroHM10((BaseChannel *) sdCOM, "idEnvio", &opcion, 1, 148);
//    if (result==2)
//        return;
//    idEnvio = (uint8_t) opcion;
//}

void enviaModbus(SerialDriver *)
{
    //controlMB->enviaModbus(idEnvio);
}

void initSerial(void) {
    palClearPad(GPIOA, GPIOA_TX1);    // Salida a USB
    palSetPad(GPIOA, GPIOA_RX1);
    palSetPadMode(GPIOA, GPIOA_TX1, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, GPIOA_TX1, PAL_MODE_ALTERNATE(7));
    sdStart(&SD1, &ser_cfg);
}

static THD_WORKING_AREA(waThreadHM10, 1024);
static THD_FUNCTION(ThreadHM10, arg) {
    (void)arg;
    chRegSetThreadName("HM10");
    int16_t result;
    uint32_t opcion;
    BaseSequentialStream *ttyOpciones;
    ttyOpciones = (BaseSequentialStream *)ttyHM10;
    palSetLineMode(LINE_ENHM10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_STHM10, PAL_MODE_INPUT);
    // reseteamos modulo (mantener RESET bajo >100ms)
    palClearLine(LINE_ENHM10);
    chThdSleepMilliseconds(120);
    palSetLine(LINE_ENHM10);
    initSerialHM10();
    while (true)
    {
        if (!palReadLine(LINE_STHM10))
        {
            chThdSleepMilliseconds(100);
            continue;
        }
        chThdSleepMilliseconds(1000);
        chprintf(ttyOpciones,"\n");
        chprintf(ttyOpciones,"GIT Tag:%s Commit:%s\n",GIT_TAG,GIT_COMMIT);
        chprintf(ttyOpciones,"Reles: %d (%d,%d) %s\n",numContactoresHR->getValor(), contactor1IR->getValor(),
                                             contactor2IR->getValor(), controlContactHR->getDescripcion());
        chprintf(ttyOpciones,"Modo control: %s\n", modoHR->getDescripcion());
        //{"manual","modbusI", "modbusP", "modbusPreg"};
        if (modoHR->getValor() == 0)
            chprintf(ttyOpciones,"Isp manual: %.1f\n",iSetPointManualHR->getValor());
        else if (modoHR->getValor() == 1)
            chprintf(ttyOpciones,"Isp modbus: %.1f\n",iSetPointModbusHR->getValor());
        else
            chprintf(ttyOpciones,"Psp modbus: %d\n",pSetPointModbusHR->getValor());
        chprintf(ttyOpciones,"Coche: %s\n",cocheStr[conexCocheIR->getValor()]);
        chprintf(ttyOpciones,"Isp:%.1f I:%.1f\n",0.01f*IsetpointIR->getValor(), 0.01f*IarealIR->getValor());
        chprintf(ttyOpciones,"NumFases: %d P:%d\n", numFasesRealIR->getValor(), PrealIR->getValor());
        chprintf(ttyOpciones,"kWh cargados:%.01f\n", 0.01f*kWhCargadosIR->getValor());

        chprintf(ttyOpciones,"\n");
        chprintf(ttyOpciones,"1 Ajuste medidor\n");
        chprintf(ttyOpciones,"2 Ajuste ordenador\n");
        chprintf(ttyOpciones,"3 Sist. electrico\n");
        chprintf(ttyOpciones,"4 Control\n");
        chprintf(ttyOpciones,"5 Listado regs\n");

        limpiaBuffer((BaseChannel *) ttyHM10); // por si esta conectado HM-10 y da mensajes de error
        result = preguntaNumeroHM10((BaseChannel *) ttyHM10, "Dime opcion", &opcion, 1, 5);
        chprintf(ttyOpciones,"\n");
        if (result != 0)
            continue;
        if (opcion==1)
            ajustaMedidor(ttyHM10);
        if (opcion==2)
            ajustaOrdenador(ttyHM10);
        if (opcion==3)
            ajustaSistElectrico(ttyHM10);
        if (opcion==4)
            ajustaControl(ttyHM10);
        if (opcion==5)
            listadoRegistros(ttyHM10);
//
//            ajustaNumero(ttyHM10, "ID MB medidor", 1, 248, medIdHR);
//        if (opcion==2)
//            ajustaBaudiosMed(ttyHM10);
//        if (opcion==3)
//            ajustaNumero(ttyHM10, "ID MB Ordenador", 1, 248, ordenIdHR);
//        if (opcion==4)
//            ajustaBaudiosOrd(ttyHM10);
//        if (opcion==5)
//            ajustaNumero(ttyHM10, "Imax", 7, 32, iMaxHR);
//        if (opcion==6)
//            ajustaNumero(ttyHM10, "Num. Fases", 1, 3, numFasesHR);
//        if (opcion==7)
//            ajustaNumero(ttyHM10, "Num. Contactores", 1, 2, numContactoresHR);
//        if (opcion==8)
//            ajustaNumero(ttyHM10, "Isetpoint manual", 6, iMaxHR->getValor(), iSetPointManualHR);
    }
}

void initHM10(void)
{
    if (thrHM10==NULL)
        thrHM10 = chThdCreateStatic(waThreadHM10, sizeof(waThreadHM10), NORMALPRIO, ThreadHM10, NULL);
}


