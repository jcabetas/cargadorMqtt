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


const char *cocheStr[5] = {"Desconoc", "Desconect", "Conectado","Pide","Pide vent"};


extern medida *kWhActual;
extern medida *kWhIniCarga;
extern medida *Ptot;
extern uint8_t numFasesReal;
extern bool hayPot;
uint16_t dsPAlta = 0;
systime_t startUltEstado;

// en monofasica la potencia va de 1.610 a iMax*230. En trifásico de 4.830 a iMax*230
// si la Ptot es mayor de 0.8*iMax*230 más de 30s, activamos segundo rele
// si la Ptot<
void  cargador::controlCarga(void)
{
    estadoRes_t estadoCoche = cargKona->getEstadoRes();
    // si no esta conectado, apaga y vamonos!
    if (estadoCoche < RCONECTADO)
    {
        ocultaOscilador();
        ponReles(0, 0);
        return;
    }
    // miramos si hay potencia
    float Isetpoint = pSetPointModbusHR->getValor()/230.0f/numFasesReal;
    if (Isetpoint>=7.0f)
        hayPot = true;
    else
        hayPot = false;
    // actualizo hay mucha potencia
    if (Isetpoint>13.0f)
    {
        if (horaHayMuchaPot==0)
            horaHayMuchaPot = chVTGetSystemTime();
    }
    else
        horaHayMuchaPot = 0;
    // pon oscilador si hay potencia
    if (hayPot)
    {
        if (osciladorOculto) // compruebo que ha pasado un tiempo desde ult. desconexion por potencia
        {
            sysinterval_t duracion = chVTTimeElapsedSinceX(horaDescFaltapot);
            if (TIME_I2S(duracion) > 10)
                sacaOscilador();
        }
        else
            sacaOscilador();
    }
    else
    {
        if (!osciladorOculto)
            horaDescFaltapot = chVTGetSystemTime();
        ocultaOscilador();
    }
    // RELES
    // si no hay chicha, no pomgas reles
    if (!hayPot || osciladorOculto)
    {
        ponReles(0, 0);
        return;
    }
    // configuración de intensidad
    cargKona->fijaAmperios(Isetpoint);
    // monofásico o solo un contactor: poner reles, si procede
    if (numFasesReal==1 || numContactoresHR->getValor()==1)
    {
        ponReles(1,0);          // si hay potencia y he puesto oscilador, pongo rele
    }
    else
    {
        // hay dos contactores...
        // si hay mucha potencia, conecta los dos contactores
        sysinterval_t duracion = chVTTimeElapsedSinceX(horaHayMuchaPot);
        if (TIME_I2S(duracion) > 30)
            ponReles(1, 1);
        else
            ponReles(1, 0);
    }
}

//sysinterval_t duracion = chVTTimeElapsedSinceX(start);
//systime_t start = chVTGetSystemTime();


