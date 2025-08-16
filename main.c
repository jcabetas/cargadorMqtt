/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "lcd.h"
#include <stdio.h>

void initSerial(void);
void initColas(void);
void initDisplay(void);
int8_t initModbusSlave(void);
int8_t initModbusMaster(void);
void initHM10(void);
void initPulsador(void);
void initCargador(void);

extern event_source_t updateLCD_source;

/*
 * Cargador STM32 modbus
 */

int main(void) {
  halInit();
  chSysInit();

  chEvtObjectInit(&updateLCD_source);
  initSerial();
  initColas();
  initDisplay();
  initModbusSlave();
  initModbusMaster();
  initHM10();
  initPulsador();
  initCargador();



  while (1==1) {
      chThdSleepMilliseconds(1000);
  }
}
