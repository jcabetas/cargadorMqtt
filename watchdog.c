/*
 * watchdog.c
 *
 *  Created on: 5/8/2017
 *      Author: joaquin
 */

#include "ch.h"
#include "hal.h"
#include "watchdog.h"
#include "chprintf.h"

thread_t *procesoWD = NULL;

//
// vigilador de procesos
// p.e. rf95check, inicialmente a 0
// el thread lo pone a 1, y entonces el watchdog lo va incrementando cada 0,5s
// si llega a 10 (5s sin actualizacion), no resetea el watchdog para que entre en boot
//
uint8_t checkRf95int = 0;
uint8_t checkTrataMsgRf95 = 0;

static THD_WORKING_AREA(waThreadReavivaWatchDog, 180);
static THD_FUNCTION(ThreadReavivaWatchDog, arg) {
    (void)arg;
    chRegSetThreadName("aliveWD");
    while (TRUE)
    {
        if (checkRf95int>0)
            checkRf95int++;
        if (checkTrataMsgRf95>0)
            checkTrataMsgRf95++;
        if (checkRf95int<10 && checkTrataMsgRf95<10)
        {
            /* Reload IWDG counter */
            wdgReset(&WDGD1);
        }
        osalThreadSleepMilliseconds(500);
    }
    return;
}

/*
 * Watchdog deadline set to more than one second (LSI=40000 / (64 * 1000)).
 */
static const WDGConfig wdgcfg = {
  STM32_IWDG_PR_64,
  STM32_IWDG_RL(1000)
};

void arrancaWatchDog(void)
{
    if (!procesoWD)
        procesoWD = chThdCreateStatic(waThreadReavivaWatchDog, sizeof(waThreadReavivaWatchDog), NORMALPRIO, ThreadReavivaWatchDog, NULL);
  wdgStart(&WDGD1, &wdgcfg);
//  chprintf(tty2,"Arrancado watchdog\n\r");
  osalThreadSleepMilliseconds(300);
}
