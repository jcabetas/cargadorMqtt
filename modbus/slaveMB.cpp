/*
 * modbus.cpp
 *
 *  Created on: 17 abr. 2021
 *      Author: joaquin
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;
#include "chprintf.h"

#include "string.h"
#include "stdlib.h"
#include "tty.h"
#include "colas.h"
#include "modbus.h"
#include "registros.h"
#include "lcd.h"



extern "C" {
    uint8_t initModbusSlave(void);
}
/*
 * Hay dos interfaces Modbus:
 * - Modbus esclavo: recibe ajustes a grabar en holdingRegisters, y proporciona inputRegisters
 * - Modbus maestro: habla con dispositivos (vacon,..) y actualiza datos regularmente en inputRegisters del esclavo
 */

uint32_t modbusSpeed[10] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
const char *modbusSpeedStr[10] = {"300", "600", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"};
const char *medStr[3] = {"No hay","sdm120ct","sdm630ct"};
const char *modoStr[3] = {"manual","modbus I"};
const char *ctrlContactStr[3] = {"solo el primero","mono-tri","los dos a la vez"};
extern char *cocheStr[5];// {"desconoc.", "sin coche", "conectado","pide","pide vent."};



holdingRegisterInt *medIdHR;         // Id modbus medidor
holdingRegisterInt2Ext *medBaudHR;   // baudios medidor  {0:300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
holdingRegisterOpciones *medModeloHR;  // {"No hay","sdm120ct","sdm630ct"};
holdingRegisterOpciones *modoHR;       // {"manual","modbus I", "modbus P"};
holdingRegisterInt *timeOutControlHR;  // tiempo para pasar a manual
holdingRegisterInt *ordenIdHR;         // Id modbus ordenador
holdingRegisterInt2Ext *ordenBaudHR;       // baudios ordenador
holdingRegisterInt *numFasesHR;        // #fases
holdingRegisterFloat *iMaxHR;          // I max (A) *100
holdingRegisterFloat *iMinHR;          // mA cuando no hay potencia (si es 0 abre contactor)
holdingRegisterInt *numContactoresHR;  // numero de contactores
holdingRegisterOpciones *controlContactHR;  // control de contactores {"solo el primero","mono-tri","los dos a la vez"};
holdingRegisterFloat *iSetPointManualHR;     // iSetpoint x100
holdingRegisterFloat *iSetPointModbusHR;     // iSetpoint x100
holdingRegisterInt *pSetPointModbusHR;       // pSetpoint modbus W

bool checkIspmanual(uint16_t nuevoValorInterno)
{
    float valor = nuevoValorInterno/iSetPointManualHR->getEscala();
    if (valor > iMaxHR->getValor())
        return true;
    if (valor < iMinHR->getValor())
        return true;
    return false;
}

bool checkIspmodbus(uint16_t nuevoValorInterno)
{
    float valor = nuevoValorInterno/iSetPointModbusHR->getEscala();
    if (valor > iMaxHR->getValor())
        return true;
    if (valor < iMinHR->getValor())
        return true;
    return false;
}

bool checkNumContactores(uint16_t nuevoValorInterno)
{
    if (nuevoValorInterno==2 && numFasesHR->getValor()==1) // no pones dos si solo hay una fase
        return true;
    return false;
}

bool checkControlContactores(uint16_t nuevoValorInterno)
{
    if (nuevoValorInterno>0 && numContactoresHR->getValor()==1) // no gestionas segundo contactor si solo hay uno
        return true;
    return false;
}

void initHoldingRegistersControl(modbusSlave *modbusControl)
{
   // comunes
   medIdHR = modbusControl->addHoldingRegisterInt("med IdMB", 2, 127, 2, true);
   medBaudHR = modbusControl->addHoldingRegisterInt2Ext("med Baud",modbusSpeed,10, 9600, true);
   medModeloHR =  modbusControl->addHoldingRegisterOpciones("med Modelo",medStr,3, 0, true);
   modoHR =  modbusControl->addHoldingRegisterOpciones("modo Control",modoStr,3, 1, true);
   timeOutControlHR =  modbusControl->addHoldingRegisterInt("timeout Control (ds)", 50, 36000, 100, true);                 //  2
   ordenIdHR = modbusControl->addHoldingRegisterInt("orden IdMB", 2, 127, 5, true);
   ordenBaudHR = modbusControl->addHoldingRegisterInt2Ext("ord Baud",modbusSpeed,10,115200,true);
   numFasesHR = modbusControl->addHoldingRegisterInt("num Fases", 1,3,1, true);
   iMaxHR = modbusControl->addHoldingRegisterFloat("iMax",7.0f,32.0f,16.0f, 100.0f, true);
   iMinHR = modbusControl->addHoldingRegisterFloat("iMin",0.0f,7.0f, 5.0f, 100.0f, true);
   numContactoresHR = modbusControl->addHoldingRegisterInt("num Contact.", 1,2,1, true, checkNumContactores);       //  0
   controlContactHR = modbusControl->addHoldingRegisterOpciones("cont. Contact.", ctrlContactStr, 3,0, true, checkControlContactores);       //  0
   iSetPointManualHR = modbusControl->addHoldingRegisterFloat("Isp manual", 7.0f, 32.0f, 14.0f, 100.0f, true, checkIspmanual);   //  4
   iSetPointModbusHR = modbusControl->addHoldingRegisterFloat("Isp modbus", 7.0f, 32.0f, 16.0f, 100.0f, false, checkIspmodbus);   //  4
   pSetPointModbusHR = modbusControl->addHoldingRegisterInt("Psp modbus", 0, 12000, 6500, false);
}


inputRegister *conexCocheIR; // 0: ilegal, 1: no hay coche, 2: conectado: 3: pidiendo, 4: ventilacion
inputRegister *medValidasIR;
inputRegister *IarealIR;
inputRegister *IbrealIR;
inputRegister *IcrealIR;
inputRegister *PrealIR;
inputRegister *kWhCargadosIR;  // kWh*100
inputRegister *kWhActualHiIR;  // kWh*100
inputRegister *kWhActualLoIR;  // kWh*100
inputRegister *numFasesRealIR;
inputRegister *IsetpointIR;    // *100
inputRegister *contactor1IR;
inputRegister *contactor2IR;
inputRegister *tLastMsgRxIR;


void initInputRegistersControl(modbusSlave *modbusControl)
{
   // comunes
   conexCocheIR = modbusControl->addInputRegister("Estado coche");
   medValidasIR = modbusControl->addInputRegister("Medidas validas");
   IarealIR = modbusControl->addInputRegister("Iareal");            // A*100
   IbrealIR = modbusControl->addInputRegister("Ibreal");            // A*100
   IcrealIR = modbusControl->addInputRegister("Icreal");            // A*100
   PrealIR = modbusControl->addInputRegister("Preal");              // W
   kWhCargadosIR = modbusControl->addInputRegister("kWh carga");    // kWh*100
   kWhActualLoIR = modbusControl->addInputRegister("kWh total Lo");
   kWhActualHiIR = modbusControl->addInputRegister("kWh total Hi"); // kWh*100
   numFasesRealIR = modbusControl->addInputRegister("#Fases");
   IsetpointIR = modbusControl->addInputRegister("Isp actual");
   contactor1IR = modbusControl->addInputRegister("Contactor1");
   contactor2IR = modbusControl->addInputRegister("Contactor2");
   tLastMsgRxIR = modbusControl->addInputRegister("tLastMsg (ds)");
   tLastMsgRxIR->setValor(0);
}


thread_t *slaveMBThread = NULL;
modbusSlave *controlMB;

static THD_WORKING_AREA(wamodbus, 3000);
static THD_FUNCTION(modbusThrd, arg) {
    (void)arg;
    uint8_t contador = 0;
    uint8_t buffer[256];
    uint16_t bytesReceived;
    chRegSetThreadName("modbus");
    while (true) {
        controlMB->esperaSilencioModbus();
        bool hayMsg = controlMB->readModbus(buffer, sizeof(buffer),&bytesReceived, chTimeMS2I(5000));
        if (hayMsg)
        {
            controlMB->interpretaMsg(contador, buffer, bytesReceived);
            if (++contador > 9)
                contador = 0;
        }
        if (chThdShouldTerminateX())
        {
            chThdExit((msg_t) 1);
        }
    }
}



/*
 * Modbus para recibir ordenes
 */
uint8_t initModbusSlave(void)
{
    palSetLineMode(LINE_TX2,PAL_MODE_ALTERNATE(7) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(LINE_RX2,PAL_MODE_ALTERNATE(7) | PAL_STM32_OSPEED_HIGHEST);
    palClearLine(LINE_TXRX2);
    palSetLineMode(LINE_TXRX2, PAL_MODE_OUTPUT_PUSHPULL);
    controlMB = new modbusSlave(&SD2, LINE_TXRX2);
    holdingRegister::setMBSlave(controlMB);
    initHoldingRegistersControl(controlMB);
    initInputRegistersControl(controlMB);
    controlMB->leeHR();
    controlMB->startMBSerial(ordenBaudHR->getValor());
    if (slaveMBThread==NULL)
        slaveMBThread = chThdCreateStatic(wamodbus, sizeof(wamodbus), NORMALPRIO, modbusThrd, NULL);
    else
        return 1;
    return 0;
}
