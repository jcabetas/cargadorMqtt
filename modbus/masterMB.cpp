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
#include "dispositivos.h"
#include "lcd.h"
#include "stdio.h"
#include "externRegistros.h"
#include "cargador.h"

extern registrosModbus *registrosMB;

extern "C" {
    uint8_t initModbusMaster(void);
}
/*
 * Hay dos interfaces Modbus:
 * - Modbus esclavo: recibe ajustes a grabar en holdingRegisters, y proporciona inputRegisters
 * - Modbus maestro: habla con medidor, y actualiza datos regularmente en inputRegisters
 */
//
//uint32_t modbusSpeed[10] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};

thread_t *masterMBThread = NULL;
modbusMaster *medidorMB;

extern modbusSlave *controlMB;
sdm120ct *med120ct;
sdm630ct *med630ct;
extern cargador *cargKona;

#ifdef MODODEBUG
float incEner = 0.0f;
#endif

medida *Ia;
medida *Ib;
medida *Ic;
medida *Ptot;
medida *kWhActual;
medida *kWhIniCarga;




void actualizaIa(float valorPar, bool esValidoPar)
{
    char bufferLCD[25];

#ifdef MODODEBUG
    float nuevoValor;
    if (contactor1IR->getValor()==1)
    {
        nuevoValor = 0.01f*IsetpointIR->getValor();
    }
    else
        nuevoValor = 0.0f;
    IarealIR->setValor(100*nuevoValor);
    if (contactor2IR->getValor()==1)
        IbrealIR->setValor(100*nuevoValor);
    else
        IbrealIR->setValor(0);
    if (contactor2IR->getValor()==1)
        IcrealIR->setValor(100*nuevoValor);
    else
        IcrealIR->setValor(0);
#else
    IarealIR->setValor(100*valorPar);
    if (medModeloHR->getValor() == 1)  // sdm120ct
    {
        IbrealIR->setValor(0);
        IcrealIR->setValor(0);
    }
#endif
    medValidasIR->setValor(esValidoPar);
    if (esValidoPar)
        snprintf(bufferLCD,sizeof(bufferLCD),"I:%4.1f P:%5d",0.01f*IarealIR->getValor(), PrealIR->getValor());
    else
        snprintf(bufferLCD,sizeof(bufferLCD),"I:??   P: ??   ");
    ponEnColaLCD(1,bufferLCD);
}

void actualizaIaTrifasico(float valorPar, bool esValidoPar)
{
    char bufferLCD[25];

#ifdef MODODEBUG
    float nuevoValor;
    if (contactor1IR->getValor()==1)
    {
        nuevoValor = 0.01f*IsetpointIR->getValor();
    }
    else
        nuevoValor = 0.0f;
    IarealIR->setValor(100*nuevoValor);
    if (contactor2IR->getValor()==1)
        IbrealIR->setValor(100*nuevoValor);
    else
        IbrealIR->setValor(0);
    if (contactor2IR->getValor()==1)
        IcrealIR->setValor(100*nuevoValor);
    else
        IcrealIR->setValor(0);
#else
    IarealIR->setValor(100*valorPar);
#endif
    medValidasIR->setValor(esValidoPar);
    if (esValidoPar)
        snprintf(bufferLCD,sizeof(bufferLCD),"Ia:%4.1f P:%5d",0.01f*IarealIR->getValor(), PrealIR->getValor());
    else
        snprintf(bufferLCD,sizeof(bufferLCD),"I:??   P: ??   ");
    ponEnColaLCD(1,bufferLCD);
}


void actualizaPtot(float valor, bool esValido)
{
    char bufferLCD[25];
#ifdef MODODEBUG
    if (contactor1IR->getValor()==1)
    {
        if (contactor2IR->getValor()==1)
            valor = 3.0f*IarealIR->getValor()*2.30f;   // trifasico (I está dividida por 100)
        else
            valor = IarealIR->getValor()*2.30f; // monofásico
    }
    else
        valor = 0.0f;
    if (valor>0.1)
    {
        incEner += 0.01f;
    }
    PrealIR->setValor(valor);
#else
    PrealIR->setValor(valor);
    medValidasIR->setValor(esValido);
#endif
    medValidasIR->setValor(esValido);
    if (esValido)
        snprintf(bufferLCD,sizeof(bufferLCD),"I:%4.1f P:%5d",0.01f*IarealIR->getValor(), PrealIR->getValor());
    else
        snprintf(bufferLCD,sizeof(bufferLCD),"I:??   P: ??   ");
    ponEnColaLCD(1,bufferLCD);
}

void actualizakWh(float valor, bool esValido)
{
    char bufferLCD[25];
#ifdef MODODEBUG
    valor += incEner;
#endif
    uint32_t valorInt = (uint32_t) (valor*100.0f);
    kWhActualHiIR->setValor((valorInt & 0xFFFF0000)>>16);
    kWhActualLoIR->setValor(valorInt & 0xFFFF);
    if (cargKona->getEstadoRes() >= 2 && kWhIniCarga->getValor()<0.01f)
        kWhIniCarga->setValor(valor);
    kWhCargadosIR->setValor(valorInt - 100.0f*kWhIniCarga->getValor());
    medValidasIR->setValor(esValido);
    snprintf(bufferLCD,sizeof(bufferLCD),"kWh: %.3f    ",valor);
    ponEnColaLCD(2,bufferLCD);
}



static THD_WORKING_AREA(wamodbus, 3000);
static THD_FUNCTION(modbusMasterThrd, arg) {
    (void)arg;
    uint16_t msDelay = 999; // para que se actualicen todas las medidas
    chRegSetThreadName("modbus");
    while (true) {
        //    if (medModeloHR->getValor() == 1)  // sdm120ct
        systime_t start = chVTGetSystemTime();
        if (medModeloHR->getValor() == 1)  // sdm120ct
            medidorMB->lee(0, msDelay);
        else if (medModeloHR->getValor() == 2)  // sdm630ct
            medidorMB->lee(1, msDelay);
        if (chThdShouldTerminateX())
        {
            chThdExit((msg_t) 1);
        }
        chThdSleepMilliseconds(100);
        sysinterval_t duracion = chVTTimeElapsedSinceX(start);
        msDelay = chTimeI2MS(duracion);
    }
}

// define dos medidores (sdm120ct y sdm630ct) y usa el que esté configurado

uint8_t initModbusMaster(void)
{
    palSetLineMode(LINE_TX6,PAL_MODE_ALTERNATE(8) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(LINE_RX6,PAL_MODE_ALTERNATE(8) | PAL_STM32_OSPEED_HIGHEST);
    palClearLine(LINE_TXRX6);
    palSetLineMode(LINE_TXRX6, PAL_MODE_OUTPUT_PUSHPULL);
    medidorMB = new modbusMaster(&SD6, LINE_TXRX6, registrosMB);
    // inicio medidas
    Ia = new medida(actualizaIa);
    Ib = new medida(NULL);
    Ic = new medida(NULL);
    Ptot = new medida(actualizaPtot);
    kWhActual = new medida(actualizakWh);
    kWhIniCarga = new medida(NULL);
    // defino medidor sdm120ct
    med120ct = new sdm120ct(medidorMB,"medPot", medIdHR->getValor());
    med120ct->attachMedida(Ptot, "P", 1000, "Potencia");
    med120ct->attachMedida(Ia, "I", 1000, "Ia");
    med120ct->attachMedida(kWhActual, "kWh", 5000, "kWh");
//    medidorMB->addDisp(med120ct); // dispositivo numero 0
    // defino medidor sdm630ct
    med630ct = new sdm630ct(medidorMB,"medPot",medIdHR->getValor());
    med630ct->attachMedida(Ptot, "P", 1000, "Potencia");
    med630ct->attachMedida(Ia, "Ia", 1000, "Ia");
    med630ct->attachMedida(Ia, "Ib", 1000, "Ib");
    med630ct->attachMedida(Ia, "Ic", 1000, "Ic");
    med630ct->attachMedida(kWhActual, "kWh", 5000, "kWh");
//    medidorMB->addDisp(med630ct); // dispositivo numero 1

     //startMBSerial();
    /*
     * Holding registers (se guardan en flash):
       Modbus ID
       Baudios
       Timeout recepcion (s)
       numDimmersInstalados
     */
    // Inicializo bus de medida
    uint32_t  baudios = medBaudHR->getValor();
    medidorMB->startMBSerial(baudios);
    if (masterMBThread==NULL)
        masterMBThread = chThdCreateStatic(wamodbus, sizeof(wamodbus), NORMALPRIO, modbusMasterThrd, NULL);
    return 0;
}
