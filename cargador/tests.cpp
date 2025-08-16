/*
 * testReles.cpp
 *
 *  Created on: 28 jun 2025
 *      Author: joaquin
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;


extern "C" {
    void testReles(void);
    void testPilot(void);
}

void testReles(void)
{
    palClearLine(LINE_LED_RELE1);
    palSetLineMode(LINE_LED_RELE1, PAL_MODE_OUTPUT_PUSHPULL);
    chThdSleepMilliseconds(1000);
    palSetLine(LINE_LED_RELE1);
    chThdSleepMilliseconds(1000);
    palClearLine(LINE_LED_RELE1);

    palClearLine(LINE_RELE2);
    palSetLineMode(LINE_RELE2, PAL_MODE_OUTPUT_PUSHPULL);
    chThdSleepMilliseconds(1000);
    palSetLine(LINE_RELE2);
    chThdSleepMilliseconds(1000);
    palClearLine(LINE_RELE2);

}

void testPilot(void)
{
    // PA15
    palClearLine(LINE_OSCILADOR);
    palSetLineMode(LINE_OSCILADOR, PAL_MODE_OUTPUT_PUSHPULL);
    chThdSleepMilliseconds(1000);
    palSetLine(LINE_OSCILADOR);
    chThdSleepMilliseconds(1000);
    palClearLine(LINE_OSCILADOR);
}
