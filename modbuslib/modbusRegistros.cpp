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
#include "w25q16.h"



holdingRegisterInt2Ext *registrosModbus::addHoldingRegisterInt2Ext(const char *nombrePar, const uint32_t int2extPar[], uint16_t numOpcionesPar,
                                                      uint32_t opcExternoDefault,bool grabablePar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterInt2Ext *nuevoHR = new holdingRegisterInt2Ext(numHoldingRegistros, nombrePar, int2extPar, numOpcionesPar, opcExternoDefault, grabablePar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}

holdingRegisterInt *registrosModbus::addHoldingRegisterInt(const char *nombrePar, uint16_t opcMin, uint16_t opcMax, uint16_t opcDefault, bool grabablePar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterInt *nuevoHR = new holdingRegisterInt(numHoldingRegistros, nombrePar, opcMin, opcMax, opcDefault, grabablePar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}

holdingRegisterInt *registrosModbus::addHoldingRegisterInt(const char *nombrePar, uint16_t opcMin, uint16_t opcMax, uint16_t opcDefault, bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterInt *nuevoHR = new holdingRegisterInt(numHoldingRegistros, nombrePar, opcMin, opcMax, opcDefault, grabablePar, funcionPar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}

holdingRegisterOpciones *registrosModbus::addHoldingRegisterOpciones(const char *nombrePar,const char *opcionesStr[]
                                                           , uint16_t numOpcionesPar, uint16_t opcDefault , bool grabablePar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterOpciones *nuevoHR = new holdingRegisterOpciones(numHoldingRegistros, nombrePar, opcionesStr, numOpcionesPar, opcDefault, grabablePar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}

holdingRegisterOpciones *registrosModbus::addHoldingRegisterOpciones(const char *nombrePar,const char *opcionesStr[]
                                                           , uint16_t numOpcionesPar, uint16_t opcDefault , bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterOpciones *nuevoHR = new holdingRegisterOpciones(numHoldingRegistros, nombrePar, opcionesStr, numOpcionesPar, opcDefault, grabablePar, funcionPar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}


holdingRegisterFloat *registrosModbus::addHoldingRegisterFloat(const char *nombrePar, float valMinPar, float valMaxPar, float opcDefecto, float escalaPar, bool grabablePar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterFloat *nuevoHR = new holdingRegisterFloat(numHoldingRegistros, nombrePar, valMinPar, valMaxPar, opcDefecto, escalaPar, grabablePar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}

holdingRegisterFloat *registrosModbus::addHoldingRegisterFloat(const char *nombrePar, float valMinPar, float valMaxPar, float opcDefecto, float escalaPar, bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreRegs)
{
    if (numHoldingRegistros>=MAXHOLDINGREGISTERS)
        return NULL;
    holdingRegisterFloat *nuevoHR = new holdingRegisterFloat(numHoldingRegistros, nombrePar, valMinPar, valMaxPar, opcDefecto, escalaPar, grabablePar, funcionPar, padreRegs);
    listHoldingRegister[numHoldingRegistros] = nuevoHR;
    numHoldingRegistros++;
    return nuevoHR;
}


inputRegister *registrosModbus::addInputRegister(const char *nombrePar)
{
    if (numInputRegistros>=MAXINPUTREGISTERS)
        return NULL;
    inputRegister *nuevoIR = new inputRegister(nombrePar);
    listInputRegister[numInputRegistros] = nuevoIR;
    numInputRegistros++;
    return nuevoIR;
}

uint8_t registrosModbus::setHR(uint16_t numHR, uint16_t valor)
{
    if (numHR>=numHoldingRegistros)
        return 2;
    uint8_t hayError = listHoldingRegister[numHR]->setValorInterno(valor);
    if (hayError)
        return 3;
    if (listHoldingRegister[numHR]->esGrabable())
        escribeHR(false);
    return 0;
}

holdingRegister *registrosModbus::getHoldingRegister(uint8_t numHR)
{
    if (numHR>=numHoldingRegistros)
        return NULL;
    return listHoldingRegister[numHR];
}

uint8_t registrosModbus::getNumHR(void)
{
    return numHoldingRegistros;
}

inputRegister *registrosModbus::getInputRegister(uint8_t numIR)
{
    if (numIR>=numInputRegistros)
        return NULL;
    return listInputRegister[numIR];
}

uint8_t registrosModbus::getNumIR(void)
{
    return numInputRegistros;
}

//uint8_t registrosModbus::getHR(uint16_t numHR, uint32_t *valor)
//{
//    if (numHR>=numHoldingRegistros)
//        return 1;
//    *valor = listHoldingRegister[numHR]->getValor();
//    return 0;
//}

uint8_t registrosModbus::getHRInterno(uint16_t numHR, uint16_t *valor)
{
    if (numHR>=numHoldingRegistros)
        return 1;
    *valor = listHoldingRegister[numHR]->getValorInterno();
    return 0;
}


uint8_t registrosModbus::escribeHR(bool useDefaultValues)
{
  uint16_t valor;
  chMtxLock(&mtxUsandoW25q16);
  uint16_t hayW25q16 = W25Q16_start();
  if (hayW25q16) // hay w25q16 instalado?
  {
      W25Q16_sectorErase(0);
      for (uint8_t v=0; v<numHoldingRegistros; v++)
      {
          holdingRegister *hr = listHoldingRegister[v];
          if (hr==NULL)
              continue;
          if (useDefaultValues)
              valor = hr->getValorInternoDefecto();
          else
              valor = hr->getValorInterno();
          W25Q16_write_u16(0, 2+2*v, valor);
      }
      W25Q16_write_u16(0, 0, 0x7851);
  }
  spiStop(&SPID1);
  chMtxUnlock(&mtxUsandoW25q16);
  return hayW25q16;
  //leeVariables();
}

uint8_t registrosModbus::leeHR(void)
{
  //chprintf(ttyCOM,"Leo variables\n");
  uint8_t hayError = 0;
  chMtxLock(&mtxUsandoW25q16);
  uint16_t hayW25q16 = W25Q16_start();
  if (hayW25q16)
  {
      //chprintf(ttyCOM,"- Detectado flash\n");
      uint16_t claveEEprom = W25Q16_read_u16(0, 0);
      if (claveEEprom != 0x7851)
      {
          //chprintf(ttyCOM,"- No esta inicializada... la reseteamos\n");
          // escribimos valores iniciales, tengo que liberar memoria
          spiStop(&SPID1);
          chMtxUnlock(&mtxUsandoW25q16);
          escribeHR(true); //reseteaEeprom();
          // volvemos a pillar la memoria
          chMtxLock(&mtxUsandoW25q16);
          W25Q16_start();
      }
      for (uint8_t v=0;v<numHoldingRegistros;v++)
      {
          holdingRegister *hr = listHoldingRegister[v];
          if (hr->esGrabable())
          {
              uint16_t valorLeido = W25Q16_read_u16(0, 2+v*2);
              uint8_t error = hr->setValorInternoSinGrabar(valorLeido);
              if (error)
                  hayError = 1;
          }
      }
      if (hayError)
      {
          spiStop(&SPID1);
          chMtxUnlock(&mtxUsandoW25q16);
          escribeHR(true); //reseteaEeprom();
          // volvemos a pillar la memoria
          chMtxLock(&mtxUsandoW25q16);
          W25Q16_start();
      }
  }
  spiStop(&SPID1);
  chMtxUnlock(&mtxUsandoW25q16);
  return hayW25q16;
}

// mira si el valor del holdingRegister es diferente a la flash
uint8_t registrosModbus::grabaHR(holdingRegister *holdReg)
{
  if (!holdReg->esGrabable())
      return false;
  chMtxLock(&mtxUsandoW25q16);
  uint16_t hayW25q16 = W25Q16_start();
  if (!hayW25q16)
      return 1; // no merece la pena escribir
  uint16_t claveEEprom = W25Q16_read_u16(0, 0);
  if (claveEEprom != 0x7851)
  {
      spiStop(&SPID1);
      chMtxUnlock(&mtxUsandoW25q16);
      escribeHR(true); //reseteaEeprom();
      // volvemos a pillar la memoria
      chMtxLock(&mtxUsandoW25q16);
      W25Q16_start();
  }
  uint16_t posicionHR = holdReg->getPosicion();
  uint16_t valorFlash = W25Q16_read_u16(0, 2+posicionHR*2);
  spiStop(&SPID1);
  chMtxUnlock(&mtxUsandoW25q16);
  if (valorFlash != holdReg->getValorInterno())
      escribeHR(false);
  return 0;
}



registrosModbus::registrosModbus(void)
{
    chMtxObjectInit(&mtxUsandoW25q16);
    // inicializamos listado HR
    for (uint16_t i=0;i<MAXHOLDINGREGISTERS;i++)
        listHoldingRegister[i] = NULL;
    numHoldingRegistros = 0;
    // idem input registers
    for (uint16_t i=0;i<MAXINPUTREGISTERS;i++)
        listInputRegister[i] = NULL;
    numInputRegistros = 0;
}



