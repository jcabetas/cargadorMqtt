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
#include "chprintf.h"

extern cargador *cargKona;
extern event_source_t enviarCoche_source;

//typedef enum { RDESCONOCIDO=0, RDESCONECTADO, RCONECTADO, RPIDECARGA, RPIDEVENTILACION} estadoRes_t;
const char *cocheStr[5] = {"desconocido", "sin coche", "conectado","pide","pide vent."};

//extern medida *Ia;
//extern medida *Ptot;
//extern medida *kWhActual;
//extern medida *kWhIniCarga;

//holdingRegisterOpciones *modoHR;       // {"manual","modbusI"};
void  cargador::controlIntensidad(void)
{
    IsetpointIR->setValor(100*iSetPointModbusHR->getValor());
    cargKona->fijaAmperios(iSetPointModbusHR->getValor());
}

void cargador::cambioEstado(void)
{
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
                // kWhIniCarga->setValor(kWhActual->getValor());
                kWhIniCargaLoIR->setValor(kWhActualLoIR->getValor());
                kWhIniCargaHiIR->setValor(kWhActualHiIR->getValor());
            }
            break;
        case RPIDECARGA:
        case RPIDEVENTILACION:
            sacaOscilador();
            cargKona->ponReles();  // conecta cargador
            if (cargKona->oldStatusResis == RDESCONECTADO)
            {
                kWhCargadosIR->setValor(0);
                //kWhIniCarga->setValor(kWhActual->getValor());
                kWhIniCargaLoIR->setValor(kWhActualLoIR->getValor());
                kWhIniCargaHiIR->setValor(kWhActualHiIR->getValor());
            }
            break;
    }
    ponEstadoEnLCD();
    chEvtBroadcast(&enviarCoche_source);
}
