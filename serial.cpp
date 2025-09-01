/*
 * serial.cpp
 *
 */


#include "ch.hpp"
#include "hal.h"
using namespace chibios_rt;

#include "tty.h"
#include "gets.h"
#include "string.h"
#include <stdlib.h>
#include "chprintf.h"
#include "version.h"
#include "modbus.h"
#include "lcd.h"
#include "ArduinoJson.h"
#include "externRegistros.h"
#include "dispositivos.h"
#include "modbus.h"

extern "C" {
    void initSerial(void);
}

extern char *cocheStr[5];// = {"desconocido", "sin coche", "conectado","pide","pide vent."};
static const SerialConfig ser_cfg115200 = {115200, 0, 0, 0, };
thread_t *thrXiao = NULL;
event_source_t enviarCoche_source;

static THD_WORKING_AREA(waThreadXiao, 2048);
static THD_FUNCTION(ThreadXiao, arg) {
    (void)arg;
    chRegSetThreadName("xiao");
    uint8_t huboTimeout;
    eventmask_t evt;
    eventflags_t flags;
    event_listener_t reciboDeXiaou_lis, enviarCoche_lis;
    uint8_t buffer[50];
    StaticJsonDocument<100> doc;
    chEvtRegisterMaskWithFlags(chnGetEventSource(&SD1),&reciboDeXiaou_lis, EVENT_MASK (0),CHN_INPUT_AVAILABLE);
    chEvtRegisterMask(&enviarCoche_source, &enviarCoche_lis, EVENT_MASK(1));
    while (true)
    {
        evt = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(10000));
        if (chThdShouldTerminateX())
        {
            chEvtUnregister(chnGetEventSource(&SD1), &reciboDeXiaou_lis);
            chEvtUnregister(&enviarCoche_source, &enviarCoche_lis);
            chThdExit((msg_t) 1);
        }
        if (evt & EVENT_MASK(0)) // Algo ha entrado desde SD1
        {
            flags = chEvtGetAndClearFlags(&reciboDeXiaou_lis);
            if (! (flags & CHN_INPUT_AVAILABLE))
                continue;
            chgetsNoEchoTimeOut((BaseChannel *)&SD1, buffer, sizeof(buffer),TIME_MS2I(1000), &huboTimeout);
            if (!huboTimeout)
            {
                // Deserialize the JSON document
                DeserializationError error = deserializeJson(doc, buffer);
                // Test if parsing succeeds.
                if (error) {
                    continue;
                }
                // tengo que enviar estado ("orden\":\"diestado\") ?
                if (doc["orden"] && !strcmp("diestado",doc["orden"]))
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"orden\":\"estado\",\"numfases\":\"%d\""
                             ",\"imin\":\"%.1f\",\"imax\":\"%.1f\",\"numcontactores\":\"d\"}\n",
                             numFasesHR->getValor(), iMinHR->getValor(), iMaxHR->getValor(), numContactoresHR->getValor());
                }

                const char* isp = doc["isp"];
                if (isp)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"isp\":\"%s\"}\n",isp);
                    float Isp = atof(isp);
                    iSetPointModbusHR->setValor(Isp);
                }
                const char* medBaud = doc["medBaud"];
                if (medBaud)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medBaudios\":\"%s\"}\n",medBaud);
                    uint32_t baudios = atoi(medBaud);
                    medBaudHR->setValor(baudios);
                }
                const char* medId = doc["medId"];
                if (medId)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medId\":\"%s\"}\n",medId);
                    uint8_t id = atoi(medId);
                    medIdHR->setValor(id);
                }
                const char* medModelo = doc["medModelo"];
                if (medModelo)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medModelo\":\"%s\"}\n",medModelo);
                    uint8_t modMed = atoi(medModelo);
                    medModeloHR->setValor(modMed);
                }

            }
        }
        if (evt & EVENT_MASK(1)) // Me han pedido que envie estado de coche
        {
            chprintf((BaseSequentialStream *)&SD1,"{\"coche\":\"%s\"}\n",cocheStr[conexCocheIR->getValor()]);
        }
    }
}

void initSD1(void) {
    palClearLine(LINE_TX1);
    palSetLine(LINE_RX1);
    palSetLineMode(LINE_TX1, PAL_MODE_ALTERNATE(7));
    palSetLineMode(LINE_RX1, PAL_MODE_ALTERNATE(7));
    sdStart(&SD1, &ser_cfg115200);
}


void initSerial(void)
{
    initSD1();
    // envio valores iniciales
//    chprintf((BaseSequentialStream *)&SD1,"{\"orden\":\"estado\",\"numfases\":\"%d\""
//             ",\"imin\":\"%.1f\",\"imax\":\"%.1f\",\"numcontactores\":\"d\"}\n",
//             numFasesHR->getValor(), iMinHR->getValor(), iMaxHR->getValor(), numContactoresHR->getValor());
//    chprintf((BaseSequentialStream *)&SD1,"{\"coche\":\"%s\"}\n",cocheStr[conexCocheIR->getValor()]);
//    float Isp = iSetPointModbusHR->getValor();
//    chprintf((BaseSequentialStream *)&SD1,"{\"isp\":\"%.1f\"}\n",Isp);
    if (thrXiao==NULL)
        thrXiao = chThdCreateStatic(waThreadXiao, sizeof(waThreadXiao), NORMALPRIO, ThreadXiao, NULL);
}

