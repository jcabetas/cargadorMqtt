/*
 * modbus.cpp
 *
 *  Created on: 17 abr. 2021
 *      Author: joaquin
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;

#include "registros.h"
#include "string.h"
#include "lcd.h"

#include "modbus.h"

void error(const char *)
{
    //ponEnColaLCD(3, msg);
    while (true) {
        chThdSleepMilliseconds(500);
    }
}



holdingRegister::holdingRegister(uint8_t pos, const char *nombrePar, bool grabablePar, registrosModbus *padreReg)
{
    strncpy(nombre, nombrePar, sizeof(nombre));
    valInterno = 0; //¿aqui?
    grabable = grabablePar;
    posicion = pos;
    funcionHayError = NULL;
    padreRegistros = padreReg;
}

uint8_t holdingRegister::getPosicion(void)
{
    return posicion;
}

bool holdingRegister::esGrabable(void)
{
    return grabable;
}

bool holdingRegister::valorNuevoEsOk(uint16_t )
{
    return true;
}

uint8_t holdingRegister::setValorInterno(uint16_t valor)
{
    if (!valorNuevoEsOk(valor))
        return 1;
    if (funcionHayError!=NULL && funcionHayError(valor))
        return 1;
    valInterno = valor;
    if (grabable)
        padreRegistros->grabaHR(this);
    return 0;
}

uint8_t holdingRegister::setValorInternoSinGrabar(uint16_t valor)
{
    if (!valorNuevoEsOk(valor))
    {
        return 1;   // algo ha ido mal
    }
    valInterno = valor;
    return 0;
}

uint16_t holdingRegister::getValorInterno(void)
{
    return valInterno;
}

uint16_t holdingRegister::getValorInternoDefecto(void)
{
    return valInternoDefecto;
}

char *holdingRegister::getNombre(void)
{
    return nombre;
}


holdingRegisterInt2Ext::holdingRegisterInt2Ext(uint8_t pos, const char *nombrePar, const uint32_t int2ext[], uint16_t numOpcionesPar,
                                               uint32_t opcExternoDefault,bool grabablePar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    uint16_t i;
    valExternoDefecto = opcExternoDefault;
    numOpciones = numOpcionesPar;
    if (int2ext == NULL)
        error("falta int2ext");
    valInt2Ext = int2ext;
    for (i=1;i<=numOpciones;i++)
        if (valInt2Ext[i-1]==opcExternoDefault)
        {
            valInterno = i-1;
            break;
        }
    if (i > numOpciones)
        error("HR: valor invalido");
    valInternoDefecto = valInterno;
    padreRegistros = padreReg;
}

uint8_t holdingRegisterInt2Ext::setValor(uint32_t valor)
{
    for (uint16_t i=1;i<=numOpciones;i++)
        if (valInt2Ext[i-1]==valor)
        {
            setValorInterno(i-1);//            valInterno = i-1;
            return 0;
        }
    error("HR: valor invalido");
    return 1;
}

uint32_t holdingRegisterInt2Ext::getValor(void)
{
    return valInt2Ext[valInterno];
}

uint32_t holdingRegisterInt2Ext::getValor(uint16_t pos)
{
    return valInt2Ext[pos];
}

uint16_t holdingRegisterInt2Ext::getNumOpciones(void)
{
    return numOpciones;
}

bool holdingRegisterInt2Ext::valorNuevoEsOk(uint16_t nuevoValor)
{
    if (nuevoValor<numOpciones)
        return true;
    else
        return false;
}


holdingRegisterOpciones::holdingRegisterOpciones(uint8_t pos, const char *nombrePar,const char *opcionesStr[],  uint16_t numOpcionesPar,
                                            uint16_t opcDefault , bool grabablePar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    numOpciones = numOpcionesPar;
    if (opcDefault>=numOpciones)
        error("Opcion no valida");

    valInterno = opcDefault;
    valInternoDefecto = opcDefault;
    if (opcionesStr==NULL)
    error("Falta opcStr");
    for (uint8_t i=1;i<=numOpciones;i++)
        descValInt[i-1] = opcionesStr[i-1];
    funcionHayError = NULL;
}

holdingRegisterOpciones::holdingRegisterOpciones(uint8_t pos, const char *nombrePar,const char *opcionesStr[],  uint16_t numOpcionesPar,
                                            uint16_t opcDefault , bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    numOpciones = numOpcionesPar;
    if (opcDefault>=numOpciones)
        error("Opcion no valida");

    valInterno = opcDefault;
    valInternoDefecto = opcDefault;
    if (opcionesStr==NULL)
    error("Falta opcStr");
    for (uint8_t i=1;i<=numOpciones;i++)
        descValInt[i-1] = opcionesStr[i-1];
    funcionHayError = funcionPar;
}

uint16_t holdingRegisterOpciones::getValor(void)
{
    return valInterno;
}

bool holdingRegisterOpciones::valorNuevoEsOk(uint16_t nuevoValor)
{
    if (nuevoValor<numOpciones)
        return true;
    else
        return false;
}

uint8_t holdingRegisterOpciones::setValor(uint16_t valor)
{
    if (valor>=numOpciones)
        error("Opcion no valida");
    setValorInterno(valor); //    valInterno = valor;
    return 0;
}


uint8_t holdingRegisterOpciones::setValor(const char *valorStr)
{
    for (int8_t i=0;i<numOpciones;i++)
        if (!strcmp(descValInt[i], valorStr))
        {
            setValorInterno(i);
            return 0;
        }
    return 1;
}


const char *holdingRegisterOpciones::getDescripcion(void)
{
    return descValInt[valInterno];
}

const char *holdingRegisterOpciones::getDescripcion(uint16_t numOpc)
{
    if (numOpc>=numOpciones)
        error("Opcion no valida");
    return descValInt[numOpc];
}

uint16_t holdingRegisterOpciones::getNumOpciones(void)
{
    return numOpciones;
}


holdingRegisterFloat::holdingRegisterFloat(uint8_t pos, const char *nombrePar, float valMinPar,
                                           float valMaxPar, float opcDefecto, float escalaPar, bool grabablePar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    valDefecto = opcDefecto;
    escala = escalaPar;
    valInterno = (uint16_t) (opcDefecto*escala);
    valInternoDefecto = valInterno;
    valMin = valMinPar;
    valMax = valMaxPar;
    funcionHayError = NULL;
}

holdingRegisterFloat::holdingRegisterFloat(uint8_t pos, const char *nombrePar, float valMinPar, float valMaxPar, float opcDefecto,
                                           float escalaPar, bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    valDefecto = opcDefecto;
    escala = escalaPar;
    valInterno = (uint16_t) (opcDefecto*escala);
    valInternoDefecto = valInterno;
    valMin = valMinPar;
    valMax = valMaxPar;
    funcionHayError = funcionPar;
}

float holdingRegisterFloat::getValorDefecto(void)
{
    return valDefecto;
}

float holdingRegisterFloat::getValorMax(void)
{
    return valMax;
}

float holdingRegisterFloat::getValorMin(void)
{
    return valMin;
}

float holdingRegisterFloat::getValor(void)
{
    return (float) (valInterno/escala);
}

bool holdingRegisterFloat::valorNuevoEsOk(uint16_t nuevoValor)
{
    float newValor = nuevoValor/escala;
    if (newValor>valMax || newValor<valMin)
        return false;
    else
        return true;
}

uint8_t holdingRegisterFloat::setValor(float valor)
{
    setValorInterno((uint16_t) (valor*escala));
    return 0;
}

float holdingRegisterFloat::getEscala(void)
{
    return escala;
}


holdingRegisterInt::holdingRegisterInt(uint8_t pos, const char *nombrePar, uint16_t opcMin, uint16_t opcMax
                                       , uint16_t opcDefault, bool grabablePar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    valDefecto = opcDefault;
    valInterno = opcDefault;
    valInternoDefecto = valInterno;
    valMin = opcMin;
    valMax = opcMax;
    funcionHayError = NULL;
}


holdingRegisterInt::holdingRegisterInt(uint8_t pos, const char *nombrePar, uint16_t opcMin, uint16_t opcMax
                                       , uint16_t opcDefault, bool grabablePar, functionCheckPtr funcionPar, registrosModbus *padreReg) : holdingRegister(pos, nombrePar, grabablePar, padreReg)
{
    valDefecto = opcDefault;
    valInterno = opcDefault;
    valInternoDefecto = valInterno;
    valMin = opcMin;
    valMax = opcMax;
    funcionHayError = funcionPar;
}

uint16_t holdingRegisterInt::getValorDefecto(void)
{
    return valDefecto;
}

uint16_t holdingRegisterInt::getValorMax(void)
{
    return valMax;
}

uint16_t holdingRegisterInt::getValorMin(void)
{
    return valMin;
}

uint16_t holdingRegisterInt::getValor(void)
{
    return valInterno;
}

bool holdingRegisterInt::valorNuevoEsOk(uint16_t nuevoValor)
{
    if (nuevoValor>=valMin && nuevoValor<=valMax)
        return true;
    else
        return false;
}

uint8_t holdingRegisterInt::setValor(uint16_t valor)
{
    if (valor<valMin || valor>valMax)
        error("valor erroneo");
    setValorInterno(valor);
    return 0;
}

