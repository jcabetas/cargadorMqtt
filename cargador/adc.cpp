/*
 * emulateADC.c
 *
 *  Created on: 1/5/2016
 *      Author: joaquin
 */


#include "ch.hpp"
#include "hal.h"
#include "gets.h"
#include "string.h"
extern "C" {
    void testCargador(void);
    void adcAWDCallback(void);
}
using namespace chibios_rt;

#include "dispositivos.h"
#include "cargador.h"
#include "externRegistros.h"

extern cargador *cargKona;

///* Algunas definiciones que faltan en Chibios */
#define ADC_JSQR_JSQ4_N(n)       ((n) << 15)  /**< @brief 1st channel in seq. */
#define ADC_JSQR_NUM_CH(n)      (((n) - 1) << 20)

#define STM32_ADC_NUMBER         18
#define STM32_ADC_IRQ_PRIORITY    6


// fuente roja y nuevo OPAMP
uint16_t minSinCocheADC=250, maxSinCocheADC=689, minConectadoADC=690, maxConectadoADC=1092;
uint16_t minPidecargaADC=1093, maxPidecargaADC=1542, \
         minPideVentilacionADC=1543, maxPideVentilacionADC=1999;

event_source_t haCambiadoADC_source;


void adcAWDCallback(void)
{
    uint32_t valorADC;
    int32_t minWD, maxWD;
    valorADC = ADC1->DR;
    estadoRes_t statusResis = RDESCONOCIDO;
    if (valorADC>=minSinCocheADC && valorADC<=maxSinCocheADC)
    {
        statusResis = RDESCONECTADO;
        ADC1->HTR = maxSinCocheADC;
        ADC1->LTR = minSinCocheADC;
    }
    else if (valorADC>=minConectadoADC && valorADC<=maxConectadoADC)
    {
        statusResis = RCONECTADO;
        ADC1->HTR = maxConectadoADC;
        ADC1->LTR = minConectadoADC;
    }
    else if (valorADC>=minPidecargaADC && valorADC<=maxPidecargaADC)
    {
        statusResis = RPIDECARGA;
        ADC1->HTR = maxPidecargaADC;
        ADC1->LTR = minPidecargaADC;
    }
    else if (valorADC>=minPideVentilacionADC && valorADC<=maxPideVentilacionADC)
    {
        statusResis = RPIDEVENTILACION;
        ADC1->HTR = maxPideVentilacionADC;
        ADC1->LTR = minPideVentilacionADC;
    }
    if (statusResis == RDESCONOCIDO) // valor raro
    {
        minWD = valorADC - 50;
        if (minWD<0) minWD = 0;
        maxWD = valorADC + 50;
        if (maxWD>0xFFF) maxWD = 0xFFF;
        // escribo limites en ADC
        ADC1->HTR = maxWD;//0xFFF;
        ADC1->LTR = minWD;
    }
    cargKona->setEstadoRes(statusResis);
    chSysLockFromISR();
    if (chEvtIsListeningI(&haCambiadoADC_source))
        chEvtBroadcastI(&haCambiadoADC_source);
    chSysUnlockFromISR();
    ADC1->SR = 0;
}


void cargador::initADC(void)
{
    // La senyal PWN sale de PA15-TIM2CH1
    // input en PA1 ADC1IN1
    // Muestreamos IN1 como regular usando TIM2CH3 y como injected usando TIM2CH4

    palSetLineMode(LINE_ADC, PAL_MODE_INPUT_ANALOG);
    rccEnableADC1(FALSE);
    ADC1->CR1 = 0;
    ADC1->CR2 = ADC_CR2_ADON; //  | ADC_CR2_RSTCAL; parece que stm32f767 no tiene calibracion
    // TIM2-CH2  (sin salida) Trigger para regular ADC
    // TIM2-CH1  (sin salida) Trigger para Injected ADC
    ADC1->CR1   = ADC_CR1_SCAN | ADC_CR1_AWDEN | ADC_CR1_AWDIE;
//    ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_EXTEN_FALLING  | ADC_CR2_EXTSEL_SRC(0b0011) | (0b10<<20) | (0b0101<<16); //ADC_CR2_JEXTEN_FALLING + JEXTSEL(TIM3CH4)
    ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_EXTEN_FALLING  | ADC_CR2_EXTSEL_SRC(0b0011) | (0b10<<20) | (0b0010<<16); //ADC_CR2_JEXTEN_FALLING + JEXTSEL(TIM2CH0)
    ADC1->SMPR1 = 0;//ADC_SMPR1_SMP_AN10(ADC_SAMPLE_144);
    ADC1->SMPR2 = ADC_SMPR2_SMP_AN1(ADC_SAMPLE_480);
    ADC1->SQR1  = ADC_SQR1_NUM_CH(1);
    ADC1->SQR2  = 0;
    ADC1->SQR3  = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN1);
    ADC1->JSQR = ADC_JSQR_NUM_CH(1) | ADC_JSQR_JSQ4_N(ADC_CHANNEL_IN1);
    // Activo Watchdog en todos los canales regulares
    ADC1->HTR = 5; // para que se active enseguida, pongo un rango estrecho
    ADC1->LTR = 3;
    nvicEnableVector(STM32_ADC_NUMBER, STM32_ADC_IRQ_PRIORITY);
    ADC1->HTR = 0x50;
    ADC1->LTR = 0x10;
}
