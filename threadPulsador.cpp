#include "ch.hpp"
#include "hal.h"
#include "lcd.h"
#include <stdio.h>
#include "colas.h"
#include "registros.h"
#include "externRegistros.h"

extern "C" {
  void initPulsador(void);
}

thread_t *procesoPulsador = NULL;
//extern const char *strModControl[]; // {"Off", "Forzado On","setPoint"};
extern const char *modoStr[3]; // {"manual","modbus"};


static THD_WORKING_AREA(waPulsador, 256);
static THD_FUNCTION(threadPulsador, arg) {
    (void) arg;
    char buffer[25];
    chRegSetThreadName("Pulsador");

    palSetLineMode(LINE_SENSOR, PAL_MODE_INPUT);
    /* Enabling the event on the Line for a Rising edge. */
    palEnableLineEvent(LINE_SENSOR, PAL_EVENT_MODE_FALLING_EDGE);
    /* main() thread loop. */
    while (true) {
      /* Waiting for the even to happen. */
      palWaitLineTimeout(LINE_SENSOR, TIME_INFINITE);
      /* Our action. */
      uint16_t modoActual = modoHR->getValor();
      if (++modoActual>1)
          modoActual = 0;
      modoHR->setValorInterno(modoActual);
      snprintf(buffer,sizeof(buffer),"Modo:%s",modoStr[modoHR->getValor()]);
      ponEnColaLCD(3,buffer);
      // espera 250 ms hasta volver a hacer caso
      chThdSleepMilliseconds(250);
    }
}


void initPulsador(void)
{
    if (!procesoPulsador)
        procesoPulsador = chThdCreateStatic(waPulsador, sizeof(waPulsador), NORMALPRIO, threadPulsador, NULL);
}


/** @} */

