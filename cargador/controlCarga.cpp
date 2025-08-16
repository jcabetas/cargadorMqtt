/*
 * controlCarga.cpp
 *
 *  Created on: 30 jun 2025
 *      Author: joaquin
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;
#include "cargador.h"
#include "modbus.h"
#include "lcd.h"
#include "stdio.h"
#include "dispositivos.h"
#include "externRegistros.h"

extern cargador *cargKona;

//typedef enum { RDESCONOCIDO=0, RDESCONECTADO, RCONECTADO, RPIDECARGA, RPIDEVENTILACION} estadoRes_t;
const char *cocheStr[5] = {"desconoc.", "sin coche", "conectado","pide","pide vent."};

extern medida *Ia;
extern medida *Ptot;
extern medida *kWhActual;
extern medida *kWhIniCarga;

//holdingRegisterOpciones *modoHR;       // {"manual","modbusI"};
void  cargador::controlIntensidad(void)
{
    if (modoHR->getValor()==0) // manual?
    {
        IsetpointIR->setValor(100*iSetPointManualHR->getValor());
        cargKona->fijaAmperios(0.01f*IsetpointIR->getValor());
    }
    else if (modoHR->getValor()==1) // modbusI, pongo intensidad que dicta modbus
    {
        IsetpointIR->setValor(100*iSetPointModbusHR->getValor());
        cargKona->fijaAmperios(0.01f*iSetPointModbusHR->getValor());
    }
    else if (modoHR->getValor()==2) // modbusP, pongo intensidad para que de la potencia que dicta modbus
    {
        bool puedoRegular =  (dsSinModbus<timeOutControlHR->getValor()) ||
                             (medValidasIR->getValor() && IarealIR->getValor()>600 && PrealIR->getValor()>1000);
        if (puedoRegular)
        {
            float relP2I =0.01f*IarealIR->getValor()/PrealIR->getValor();
            float Pspactual = (float) (pSetPointModbusHR->getValor());
            float Ispnuevo = relP2I*Pspactual;
            if (Ispnuevo > iMaxHR->getValor())
                Ispnuevo = iMaxHR->getValor();
            if (Ispnuevo < iMinHR->getValor())
                Ispnuevo = iMinHR->getValor();
            IsetpointIR->setValor((uint16_t) (100.0f*Ispnuevo));
        }
        else
        {
            IsetpointIR->setValor(100*iSetPointManualHR->getValor());
        }
        cargKona->fijaAmperios(0.01f*IsetpointIR->getValor());
    }
}

void cargador::cambioEstado(void)
{
    char bufferLCD[20];
    switch (conexCocheIR->getValor())
    {
        case RDESCONOCIDO:
        case RDESCONECTADO:
            cargKona->ponReles();  // desconecta cargador
            ocultaOscilador();
            break;
        case RCONECTADO:
            cargKona->ponReles();  // desconecta cargador
            sacaOscilador();
            if (cargKona->oldStatusResis == RDESCONECTADO)
            {
                kWhCargadosIR->setValor(0);
                kWhIniCarga->setValor(kWhActual->getValor());
            }
            break;
        case RPIDECARGA:
        case RPIDEVENTILACION:
            sacaOscilador();
            cargKona->ponReles();  // conecta cargador
            if (cargKona->oldStatusResis == RDESCONECTADO)
            {
                kWhCargadosIR->setValor(0);
                kWhIniCarga->setValor(kWhActual->getValor());
            }
            break;
    }
    snprintf(bufferLCD,sizeof(bufferLCD),"%s (ADC:%d)",cocheStr[cargKona->getEstadoRes()],(uint16_t) ADC1->DR);
    ponEnColaLCD(3,bufferLCD);
}
