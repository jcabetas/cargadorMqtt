/*
 * cargador.cpp
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;
#include "cargador.h"
#include "lcd.h"
#include "stdio.h"
#include "colas.h"

#include "externRegistros.h"

extern "C"
{
    void initCargador(void);
}

extern cargador *cargKona;
thread_t *procesoCargador = NULL;


cargador *cargKona;
extern medida *Ia;
extern medida *Ptot;
extern uint8_t numFasesReal;
extern const char *cocheStr[5];
extern medida *kWhActual;
extern medida *kWhIniCarga;
systime_t startEstado;
extern bool hayPot;
extern event_source_t enviarCoche_source;
extern event_source_t haCambiadoADC_source;
extern event_source_t haCambiadoPsp_source;

cargador::cargador(void)
{
    palSetLineMode(LINE_RELE1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_RELE2, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_RELE1);
    palClearLine(LINE_RELE2);
    osciladorOculto = 1;
    ondaNegOk = 1;
    haCambiadoR = false;
    oldStatusResis = RDESCONOCIDO;
    horaDescFaltapot = 0;           // la primera desconexion puede ser rápida
    horaHayMuchaPot = 0;
    numFasesReal = 1;               // salvo que se demuestre lo contrario
    initADC();
    initOscilador();
    uint16_t pspdef = pDefaultSetPointHR->getValor();
    pSetPointModbusHR->setValor(pspdef);
    fijaAmperios(7.0f);
    ocultaOscilador();
    ponEstadoEnLCD();
}

void cargador::cambioEstado(void)
{
    switch (cargKona->getEstadoRes())
    {
        case RDESCONOCIDO:
        case RDESCONECTADO:
            cargKona->ponReles(0,0);  // desconecta cargador
            ocultaOscilador();
            break;
        case RCONECTADO:
            extern medida *kWhActual;
            cargKona->ponReles(0,0);  // desconecta cargador
            if (hayPot)
                sacaOscilador();
            else
                ocultaOscilador();
            if (cargKona->oldStatusResis == RDESCONECTADO)
            {
                kWhIniCarga->setValor(kWhActual->getValor());
            }
            break;
        case RPIDECARGA:
        case RPIDEVENTILACION:
            if (hayPot)
            {
                sacaOscilador();
                if (getEstadoRele2() == 0)
                    cargKona->ponReles(1,0);
                else
                    cargKona->ponReles(1,1);
            }
            else
            {
                ocultaOscilador();
                cargKona->ponReles(0,0);
            }
            if (cargKona->oldStatusResis == RDESCONECTADO)
            {
                kWhIniCarga->setValor(kWhActual->getValor());
            }
            break;
    }
}


void cargador::ponReles(uint8_t rele1, uint8_t rele2)
{
    if (rele1>=1)
        palSetLine(LINE_RELE1);
    else
        palClearLine(LINE_RELE1);
    if (rele1>=1 && rele2>=1 && numContactoresHR->getValor()==2)
        palSetLine(LINE_RELE2);
    else
        palClearLine(LINE_RELE2);
    estadoRele1 = rele1;
    estadoRele2 = rele2;
}


void cargador::setNumFasesReal(uint8_t numFasesPar)
{
    numFasesReal = numFasesPar;
}

uint8_t cargador::getNumFasesReal(void)
{
    return numFasesReal;
}

uint8_t cargador::getOsciladorOculto(void)
{
    return osciladorOculto;
}

uint8_t cargador::getEstadoRele1(void)
{
    return estadoRele1;
}

uint8_t cargador::getEstadoRele2(void)
{
    return estadoRele2;
}

uint8_t getEstadoRele1(void);
uint8_t getEstadoRele2(void);
void setReles(uint8_t rele1, uint8_t rele2);



void cargador::ponEstadoEnLCD(void)
{
    char bufferLCD[25];
    snprintf(bufferLCD,sizeof(bufferLCD),"%-9s Psp:%5d",cocheStr[cargKona->getEstadoRes()], (uint16_t) pSetPointModbusHR->getValor());
    ponEnColaLCD(0,bufferLCD);
}


void cargador::bucleCargador(void)
{
    controlCarga();
    ponEstadoEnLCD();
}


static THD_WORKING_AREA(waCargador, 1024);
static THD_FUNCTION(threadCargador, arg) {
    (void) arg;
    eventmask_t evt;
    chRegSetThreadName("Cargador");
    chEvtBroadcast(&enviarCoche_source);  // envia estado inicial
    event_listener_t haCambiadoADC_lis, haCambiadoPsp_lis;
    chEvtRegisterMask(&haCambiadoADC_source, &haCambiadoADC_lis, EVENT_MASK(0));
    chEvtRegisterMask(&haCambiadoPsp_source, &haCambiadoPsp_lis, EVENT_MASK(1));
    while (true) {
        evt = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(500));
        if (chThdShouldTerminateX())
        {
            chEvtUnregister(&haCambiadoADC_source, &haCambiadoADC_lis);
            chThdExit((msg_t) 1);
        }
        if (evt & EVENT_MASK(0)) // Ha cambiado ADC
        {
            cargKona->cambioEstado();
            cargKona->ponEstadoEnLCD();
            chEvtBroadcast(&enviarCoche_source);  // envia el cambio a Xiao
            continue;
        }
        cargKona->bucleCargador();
//        chThdSleepMilliseconds(500);
    }
}


void initCargador(void)
{
    cargKona = new cargador();
    if (!procesoCargador)
        procesoCargador = chThdCreateStatic(waCargador, sizeof(waCargador), NORMALPRIO, threadCargador, NULL);

}

