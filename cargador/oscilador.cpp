/*
 * cargador.cpp
 *
 *  Created on: 17 jun. 2021
 *      Author: joaquin
 */


#include "ch.hpp"
#include "hal.h"
#include "cargador.h"
#include "externRegistros.h"

extern "C" {
    void initCargador(void);
}
using namespace chibios_rt;



//
//uint8_t osciladorOculto = 0;

//void initADC(void);

/*
 * Duty cycle = Amps / 0.6
 * 100% = 8000
 * Ciclos = A*600
 *
 * Hasta 51A
 */


/*
 * TIM2 CH0 (sin salida) Trigger para Injected ADC
 * TIM2 CH1 (sin salida) Trigger para regular ADC
 * TIM2 CH3 (PA2) salida PWM Coche
 */
static PWMConfig pwmcfgTIM2 = {
        8000000,                                 /* 10kHz PWM clock frequency.   */
        8000,                                    /* Initial PWM 10% width       */
        NULL,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  0,
  0,
  0
};


void testCargadorBasico(void)
{
    // PA2TIM2CH3 es el pin de entrada al ondulador
    // configuramos la salida
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_ALTERNATE(0));
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_OUTPUT_PUSHPULL);
    while (true) {
        palClearLine(LINE_OSCILADOR);
        chThdSleepMilliseconds(1000);
        palSetLine(LINE_OSCILADOR);
        chThdSleepMilliseconds(1000);
    }
}

void cargador::fijaAmperios(float amperios)
{
    uint16_t ancho;
    // si hay que bajar mucho, cuidado
    // (% de ciclo de trabajo) = corriente[A]/0,6
    // esta configurado de forma que ancho=8000 => 100%
    // 30A == 50% => ancho=4000
    float Imin = iMinHR->getValor();
    if (amperios<Imin)
        amperios = Imin;
    ancho = (uint16_t) (amperios*133.0f);
    pwmEnableChannel(&PWMD2, 2, ancho);      // Onda para wallbox TIM2CH3
    pwmEnableChannel(&PWMD2, 1, ancho-200);  // detección tensión +12V
    pwmEnableChannel(&PWMD2, 0, ancho+3000); // detección tensión -12 V
}

void cargador::ocultaOscilador(void)
{
    // desconecto oscilador
    palSetLine(LINE_OSCILADOR);
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_ALTERNATE(0));
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_OUTPUT_PUSHPULL);
//
//  palSetPad(GPIOA, 8);
//  palClearPad(GPIOA,7);
//  palSetPadMode(IOPORT1,8, PAL_MODE_OUTPUT_PUSHPULL);
//    palSetPadMode(IOPORT1,7, PAL_MODE_OUTPUT_PUSHPULL);
    osciladorOculto = 1;
}

void cargador::sacaOscilador(void)
{
    // PA8 => TIM1_CH1
    // PA7 => TIM1_CH1N (D32 en extension-pin10)
    //PWMD1.tim->CNT = 1L;
    PWMD2.tim->CNT = PWMD2.tim->ARR;
//  palClearPad(GPIOA, 8);
//  palSetPad(GPIOA,7);
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_ALTERNATE(1));
//  palSetPadMode(IOPORT1,8, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
//    palSetPadMode(IOPORT1,7, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    osciladorOculto = 0;
    ondaNegOk = 1; // se actualizará mas tarde
}

void cargador::setEstadoRes(estadoRes_t estR)
{
    haCambiadoR = true;
    oldStatusResis = (estadoRes_t) conexCocheIR->getValor();
    conexCocheIR->setValor(estR);
}

estadoRes_t cargador::getEstadoRes(void)
{
    return (estadoRes_t) conexCocheIR->getValor();
}


void cargador::initOscilador(void)
{
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_ALTERNATE(1));
    // TIM3_CH2 lo tenemos en PB5 (para probar si TIM3 funciona)
    //palSetPadMode(GPIOB, GPIOB_PIN5, PAL_MODE_ALTERNATE(2));
    // usamos sincronización de timers: TIM2 como maestro, y TIM3 como esclavo

//  Configure Timer 2 master mode to send its Enable as trigger output (MMS=001 in the TIM2_CR2 register).
//    TIM2->CR2 = STM32_TIM_CR2_MMS(0b100);
//  Configure Timer 2 slave mode to get the input trigger from TI1 (TS=100 in the TIM2_SMCR register).
//  Configure Timer 2 in trigger mode (SMS=110 in the TIM2_SMCR register).
//  Configure the Timer 2 in Master/Slave mode by writing MSM=1 (TIM2_SMCR register).
//    TIM2->SMCR = STM32_TIM_SMCR_TS(0b100) | STM32_TIM_SMCR_SMS(0b110) | STM32_TIM_SMCR_MSM;
//  Configure Timer 3 to get the input trigger from Timer 2 (TS=001 in the TIM3_SMCR register).
//  Configure Timer 3 in trigger mode (SMS=110 in the TIM3_SMCR register).
//    TIM3->SMCR = STM32_TIM_SMCR_TS(0b001) | STM32_TIM_SMCR_SMS(0b111) | STM32_TIM_SMCR_MSM;
//    pwmStart(&PWMD3, &pwmcfgTIM3);
    pwmStart(&PWMD2, &pwmcfgTIM2);


    pwmEnableChannel(&PWMD2, 2, 1300); // CH3 Onda para wallbox
    pwmEnableChannel(&PWMD2, 1,  300); // CH2 4% after start pulse (top side). Ojo, en parada se fija al 5%, necesita margen
    pwmEnableChannel(&PWMD2, 0, 6400); // CH1 80% after start pulse (low side) injected


    fijaAmperios(5.0f);
    sacaOscilador();
    //ocultaOscilador();

//    initADC();
//    statusResisOld = RDESCONOCIDO;

}



//void testCargador(void)
//{
//    // PB12 es el rele (GPIOB_RELE, LINE_RELE)
//    // PE9TIM1CH1 es el pin de entrada al ondulador
//    palSetLineMode(LINE_RELE, PAL_MODE_OUTPUT_PUSHPULL);
//    palClearLine(LINE_RELE);
//    /*
//      * Starting PWM driver 1 and enabling the notifications.
//      * GPIOE9 is programmed as PWM output (channel 1 of TIM1).
//      */
//    palSetLineMode(LINE_OSCILADOR, PAL_MODE_ALTERNATE(1));
//    pwmStart(&PWMD1, &pwmcfg);
//    fijaAmperios(10.0f);
//    pwmEnableChannel(&PWMD1, 2,  400); // CH3 5% after start pulse (top side)
//    pwmEnableChannel(&PWMD1, 3, 6400); // CH4 80% after start pulse (low side)
//    initADC();
//    while (true)
//     {
////         PWMD1.tim->CNT = PWMD1.tim->ARR;
//   //  para ocultar oscilador
//   //  palSetLineMode(LINE_TIM1_CH1, PAL_MODE_ALTERNATE(0));
//   //  palSetLineMode(LINE_TIM1_CH1, PAL_MODE_OUTPUT_PUSHPULL);
//         chThdSleepMilliseconds(5000);
//     };
//
//}
