/*
 * modbus.cpp
 *
 *  Created on: 17 abr. 2021
 *      Author: joaquin
 */

#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;
#include "chprintf.h"

#include "string.h"
#include "stdlib.h"
#include "tty.h"
#include "colas.h"
#include "modbus.h"
#include "registros.h"
#include "lcd.h"



extern "C" {
    uint8_t initModbusSlave(void);
}
/*
 * Hay dos interfaces Modbus:
 * - Modbus esclavo: recibe ajustes a grabar en holdingRegisters, y proporciona inputRegisters
 * - Modbus maestro: habla con dispositivos (vacon,..) y actualiza datos regularmente en inputRegisters del esclavo
 */



thread_t *slaveMBThread = NULL;
modbusSlave *controlMB;

static THD_WORKING_AREA(wamodbus, 3000);
static THD_FUNCTION(modbusThrd, arg) {
    (void)arg;
    uint8_t contador = 0;
    uint8_t buffer[256];
    uint16_t bytesReceived;
    chRegSetThreadName("modbus");
    while (true) {
        controlMB->esperaSilencioModbus();
        bool hayMsg = controlMB->readModbus(buffer, sizeof(buffer),&bytesReceived, chTimeMS2I(5000));
        if (hayMsg)
        {
            controlMB->interpretaMsg(contador, buffer, bytesReceived);
            if (++contador > 9)
                contador = 0;
        }
        if (chThdShouldTerminateX())
        {
            chThdExit((msg_t) 1);
        }
    }
}



/*
 * Modbus para recibir ordenes
 */
uint8_t initModbusSlave(void)
{
    palSetLineMode(LINE_TX6,PAL_MODE_ALTERNATE(8) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(LINE_RX6,PAL_MODE_ALTERNATE(8) | PAL_STM32_OSPEED_HIGHEST);
    palClearLine(LINE_TXRX6);
    palSetLineMode(LINE_TXRX6, PAL_MODE_OUTPUT_PUSHPULL);
    controlMB = new modbusSlave(&SD6, LINE_TXRX6);
    holdingRegister::setMBSlave(controlMB);
    initHoldingRegistersControl(controlMB);
    initInputRegistersControl(controlMB);
    controlMB->leeHR();
    controlMB->startMBSerial(ordenBaudHR->getValor());
    if (slaveMBThread==NULL)
        slaveMBThread = chThdCreateStatic(wamodbus, sizeof(wamodbus), NORMALPRIO, modbusThrd, NULL);
    else
        return 1;
    return 0;
}
