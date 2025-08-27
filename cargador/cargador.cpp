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

thread_t *procesoCargador = NULL;
cargador *cargKona;
extern medida *Ia;
extern const char *cocheStr[5];

cargador::cargador(void)
{
    osciladorOculto = 1;
    ondaNegOk = 1;
    haCambiadoR = false;
    oldStatusResis = RDESCONOCIDO;
}

void cargador::initReles(void)
{
    dsCambioRele2 = 0;
    palSetLineMode(LINE_RELE1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_RELE2, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_RELE1);
    palClearLine(LINE_RELE2);
}

void cargador::ponReles(void)
{
    uint8_t rele1;
    // gestionamos rele1
    if (conexCocheIR->getValor() >= 3) // coche pide
    {
        rele1 = 1;
        palSetLine(LINE_RELE1);
    }
    else
    {
        rele1 = 0;
        palClearLine(LINE_RELE1);
    }
    contactor1IR->setValor(rele1);

    // veamos rele2
    // lo apagamos si rele1 esta apagado
    if (rele1 == 0)
    {
        palClearLine(LINE_RELE2);
        contactor2IR->setValor(0);
        return;
    }
    uint16_t controlCont = controlContactHR->getValor();
    uint8_t  oldRele2 = contactor2IR->getValor();
    // apagamos rele2 si es monofasico o un solo rele
    if (controlCont==0 || numContactoresHR->getValor()==1)
    {
        palClearLine(LINE_RELE2);
        contactor2IR->setValor(0);
        return;
    }

    // si es trifasico seguimos a Rele1
    if (controlCont == 2)
    {
        contactor2IR->setValor(rele1);
        if (rele1)
            palSetLine(LINE_RELE2);
        else
            palClearLine(LINE_RELE2);
        return;
    }
    // automatico, miro a ver si ha pasado tiempo desde ultimo cambio
    if (dsCambioRele2 < MAXDSCAMBIORELE)
        return;
    // si la intensidad es elevada, y modbus activado, activamos rele2
    if (medValidasIR->getValor()==1 && 0.01f*IarealIR->getValor()>=0.8*iMaxHR->getValor())
    {
        contactor2IR->setValor(1);
        palSetLine(LINE_RELE2);
    }
    else
    {   // solo lo apago después de estar un tiempo conectado
        if (dsCambioRele2>=MAXDSCAMBIORELE)
        {
            contactor2IR->setValor(0);
            palClearLine(LINE_RELE2);
        }
    }
    if (oldRele2 != contactor2IR->getValor())
        dsCambioRele2 = 0;
}

void cargador::initCargador(void)
{
    initReles();
    initADC();
    initOscilador();
    sacaOscilador();
    dsSinModbus = 0;
    dsCambioRele2 = 0;
}

void cargador::incrementaTimers(uint16_t incds)
{
    if (dsCambioRele2<MAXDSCAMBIORELE)
    {
        dsCambioRele2 += incds;
        if (dsCambioRele2 > MAXDSCAMBIORELE)
            dsCambioRele2 = MAXDSCAMBIORELE;
    }
    dsSinModbus = tLastMsgRxIR->getValor();
    if (dsSinModbus<600)
    {
        dsSinModbus += incds;
        if (dsSinModbus > 600)
            dsSinModbus = 600;
        tLastMsgRxIR->setValor(dsSinModbus);
    }
}

void cargador::ponEstadoEnLCD(void)
{
    char bufferLCD[25];
    snprintf(bufferLCD,sizeof(bufferLCD),"%s Isp:%.1f",cocheStr[cargKona->getEstadoRes()], 0.01f*IsetpointIR->getValor());
    ponEnColaLCD(0,bufferLCD);
}


void cargador::bucleCargador(void)
{
    if (haCambiadoR)
    {
        cambioEstado();
        haCambiadoR = false;
    }
    controlIntensidad();
    ponReles();
    incrementaTimers(5);
    ponEstadoEnLCD();
}


static THD_WORKING_AREA(waCargador, 1024);
static THD_FUNCTION(threadCargador, arg) {
    (void) arg;
//    uint32_t valorActual;
//    uint32_t valorActualJ;
//    char bufferLCD[25];
    chRegSetThreadName("Cargador");
    while (true) {
        cargKona->bucleCargador();
//        valorActual = ADC1->DR;
//        valorActualJ = ADC1->JDR1;
//        uint32_t htr = ADC1->HTR;
//        uint32_t ltr = ADC1->LTR;
//        snprintf(bufferLCD,sizeof(bufferLCD),"htr:%ld  ltr:%ld  ",htr,ltr);
//        ponEnColaLCD(2,bufferLCD);
//        snprintf(bufferLCD,sizeof(bufferLCD),"ADC:%ld  J:%ld  ",valorActual,valorActualJ);
//        ponEnColaLCD(3,bufferLCD);
        chThdSleepMilliseconds(500);
    }
}

void initCargador(void)
{
    cargKona = new cargador();
    cargKona->initCargador();
    if (!procesoCargador)
        procesoCargador = chThdCreateStatic(waCargador, sizeof(waCargador), NORMALPRIO, threadCargador, NULL);

}

