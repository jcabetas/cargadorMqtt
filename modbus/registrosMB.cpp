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
#include "stdio.h"



extern "C" {
    void initRegistrosMB(void);
    void ponConfigEnLCD(void);
}

registrosModbus *registrosMB;

/*
 * Hay dos interfaces Modbus:
 * - Modbus esclavo: recibe ajustes a grabar en holdingRegisters, y proporciona inputRegisters
 * - Modbus maestro: habla con dispositivos (vacon,..) y actualiza datos regularmente en inputRegisters del esclavo
 */

uint32_t modbusSpeed[10] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
const char *modbusSpeedStr[10] = {"300", "600", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"};
const char *medStr[3] = {"No hay","sdm120ct","sdm630ct"};
const char *ctrlContactStr[3] = {"solo el primero","mono-tri","los dos a la vez"};
extern char *cocheStr[5];// {"desconoc.", "sin coche", "conectado","pide","pide vent."};


holdingRegisterInt *medIdHR;         // Id modbus ordenador
holdingRegisterInt2Ext *medBaudHR;   // baudios ordenador
holdingRegisterOpciones *medModeloHR;  // modelo medidor
holdingRegisterInt *numFasesHR;        // #fases
holdingRegisterFloat *iMaxHR;          // I max (A) *100
holdingRegisterFloat *iMinHR;          // mA cuando no hay potencia (si es 0 abre contactor)
holdingRegisterInt *numContactoresHR;  // numero de contactores
holdingRegisterOpciones *controlContactHR;  // control de contactores {"solo el primero","mono-tri","los dos a la vez"};
holdingRegisterInt *pDefaultSetPointHR;     // pSetpoint de defecto
holdingRegisterFloat *iSetPointModbusHR;     // iSetpoint x100
holdingRegisterFloat *pSetPointModbusHR;       // pSetpoint


bool checkIspmodbus(uint16_t nuevoValorInterno)
{
    float valor = nuevoValorInterno/iSetPointModbusHR->getEscala();
    if (valor > iMaxHR->getValor())
        return true;
    if (valor < iMinHR->getValor())
        return true;
    return false;
}

bool checkPspmodbus(uint16_t nuevoValorInterno)
{
    float valor = nuevoValorInterno/pSetPointModbusHR->getEscala();
    if (valor > 230.0f*numFasesHR->getValor()*iMaxHR->getValor())
        return true;
    if (valor < 230.0f*iMinHR->getValor()) // se supone que puede quedarse en una fase
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

void initHoldingRegisters(registrosModbus *modbusRegs)
{
   // comunes
   medIdHR = modbusRegs->addHoldingRegisterInt("med IdMB", 1, 127, 5, true, modbusRegs);
   medBaudHR = modbusRegs->addHoldingRegisterInt2Ext("med Baud",modbusSpeed,10,115200,true, modbusRegs);
   medModeloHR = modbusRegs->addHoldingRegisterOpciones("modelo medidor",medStr, 3, 0, true, modbusRegs);
   numFasesHR = modbusRegs->addHoldingRegisterInt("num Fases", 1,3,1, true, modbusRegs);
   iMaxHR = modbusRegs->addHoldingRegisterFloat("iMax",7.0f,32.0f,16.0f, 100.0f, true, modbusRegs);
   iMinHR = modbusRegs->addHoldingRegisterFloat("iMin",0.0f,7.0f, 5.0f, 100.0f, true, modbusRegs);
   numContactoresHR = modbusRegs->addHoldingRegisterInt("num Contact.", 1,2,1, true, checkNumContactores, modbusRegs);
   controlContactHR = modbusRegs->addHoldingRegisterOpciones("cont. Contact.", ctrlContactStr, 3,0, true, checkControlContactores, modbusRegs);
   pDefaultSetPointHR = modbusRegs->addHoldingRegisterInt("Psp def. modbus", 1200, 11040, 5000, true, checkPspmodbus, modbusRegs);
   iSetPointModbusHR = modbusRegs->addHoldingRegisterFloat("Isp modbus", 7.0f, 32.0f, 16.0f, 100.0f, false, checkIspmodbus, modbusRegs);
   pSetPointModbusHR = modbusRegs->addHoldingRegisterFloat("Psp modbus", 0.0f, 11040.0f, 3600.0f, 1.0f, false, checkPspmodbus, modbusRegs);
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
inputRegister *kWhIniCargaHiIR;  // kWh*100
inputRegister *kWhIniCargaLoIR;  // kWh*100
inputRegister *numFasesRealIR;
inputRegister *IsetpointIR;    // *100
inputRegister *contactor1IR;
inputRegister *contactor2IR;
inputRegister *tLastMsgRxIR;




void initInputRegisters(registrosModbus *modbusRegs)
{
   // comunes
   conexCocheIR = modbusRegs->addInputRegister("Estado coche");
   medValidasIR = modbusRegs->addInputRegister("Medidas validas");
   IarealIR = modbusRegs->addInputRegister("Iareal");            // A*100
   IbrealIR = modbusRegs->addInputRegister("Ibreal");            // A*100
   IcrealIR = modbusRegs->addInputRegister("Icreal");            // A*100
   PrealIR = modbusRegs->addInputRegister("Preal");              // W
   kWhCargadosIR = modbusRegs->addInputRegister("kWh carga");    // kWh*100
   kWhActualLoIR = modbusRegs->addInputRegister("kWh total Lo");
   kWhActualHiIR = modbusRegs->addInputRegister("kWh total Hi"); // kWh*100
   kWhIniCargaLoIR = modbusRegs->addInputRegister("kWh ini carga Lo");
   kWhIniCargaHiIR = modbusRegs->addInputRegister("kWh ini carga Hi"); // kWh*100
   numFasesRealIR = modbusRegs->addInputRegister("#Fases");
   IsetpointIR = modbusRegs->addInputRegister("Isp actual");
   contactor1IR = modbusRegs->addInputRegister("Contactor1");
   contactor2IR = modbusRegs->addInputRegister("Contactor2");
   tLastMsgRxIR = modbusRegs->addInputRegister("tLastMsg (ds)");
   tLastMsgRxIR->setValor(0);
}

void ponConfigEnLCD(void)
{
    char bufferLCD[25];
    snprintf(bufferLCD,sizeof(bufferLCD),"Modelo med: %s", medModeloHR->getDescripcion());
    ponEnColaLCD(0,bufferLCD);
    snprintf(bufferLCD,sizeof(bufferLCD),"Id:%-3d    baud:%5ld", medIdHR->getValor(),medBaudHR->getValor());
    ponEnColaLCD(1,bufferLCD);
    snprintf(bufferLCD,sizeof(bufferLCD),"fases:%d     #reles:%d", numFasesHR->getValor(),numContactoresHR->getValor());
    ponEnColaLCD(2,bufferLCD);
    snprintf(bufferLCD,sizeof(bufferLCD),"iMin:%.1f   iMax:%.1f", iMinHR->getValor(),iMaxHR->getValor());
    ponEnColaLCD(3,bufferLCD);
    chThdSleepMilliseconds(5000);
    ponEnColaLCD(0," ");
    ponEnColaLCD(1," ");
    ponEnColaLCD(2," ");
    ponEnColaLCD(3," ");
    chThdSleepMilliseconds(100);
}


/*
 * Modbus registros
 */
void initRegistrosMB(void)
{
    registrosMB = new registrosModbus();
    initHoldingRegisters(registrosMB);
    initInputRegisters(registrosMB);
    registrosMB->leeHR();
}
