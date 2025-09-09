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
#include "cargador.h"

extern "C" {
    void initSerial(void);
}

extern cargador *cargKona;
extern char *cocheStr[5];// = {"desconocido", "sin coche", "conectado","pide","pide vent."};
static const SerialConfig ser_cfg115200 = {115200, 0, 0, 0, };
thread_t *thrXiao = NULL;
event_source_t enviarCoche_source;
event_source_t enviarMedidas_source;
event_source_t haCambiadoPsp_source;

extern char bufferMedidas[500];

static THD_WORKING_AREA(waThreadXiao, 2048);
static THD_FUNCTION(ThreadXiao, arg) {
    (void)arg;
    chRegSetThreadName("xiao");
    uint8_t huboTimeout;
    eventmask_t evt;
    eventflags_t flags;
    event_listener_t reciboDeXiaou_lis, enviarCoche_lis, enviarMed_lis;
    uint8_t buffer[300];
    StaticJsonDocument<300> doc;
    chEvtRegisterMaskWithFlags(chnGetEventSource(&SD1),&reciboDeXiaou_lis, EVENT_MASK (0),CHN_INPUT_AVAILABLE);
    chEvtRegisterMask(&enviarCoche_source, &enviarCoche_lis, EVENT_MASK(1));
    chEvtRegisterMask(&enviarMedidas_source, &enviarMed_lis, EVENT_MASK(2));
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
                    ponEnColaLCD(3,"Error JSON");
                    continue;
                }
                // tengo que enviar estado ("orden\":\"diconfig\") ?
                if (doc["orden"] && !strcmp("diconfig",doc["orden"]))
                {
                    uint16_t pmin = 230.0f*iMinHR->getValor();
                    uint16_t pmax = numFasesHR->getValor()*230.0f*iMaxHR->getValor();
                    chprintf((BaseSequentialStream *)&SD1,"{\"orden\":\"config\",\"numfases\":\"%d\""
                             ",\"imin\":\"%.1f\",\"imax\":\"%.1f\",\"pmin\":\"%d\",\"pmax\":\"%d\",\"numcontactores\":\"%d\""
                             ",\"medbaud\":\"%d\",\"medid\":\"%d\"}\n",
                             numFasesHR->getValor(), iMinHR->getValor(), iMaxHR->getValor(), pmin, pmax,numContactoresHR->getValor(),
                             medBaudHR->getValor(),medIdHR->getValor());
                }
                // tengo que enviar estado actual ("orden\":\"diestado\") ?
                if (doc["orden"] && !strcmp("diestado",doc["orden"]))
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"orden\":\"estado\",\"coche\":\"%s\",\"psp\":\"%.1f\"}\n",cocheStr[conexCocheIR->getValor()], pSetPointModbusHR->getValor());
                }
                const char* isp = doc["isp"];
                if (isp)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"isp\":\"%s\"}\n",isp);
                    float Isp = atof(isp);
                    iSetPointModbusHR->setValor(Isp);
                }
                const char* psp = doc["psp"];
                if (psp)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"psp\":\"%s\"}\n",psp);
                    float Psp = atof(psp);
                    pSetPointModbusHR->setValor(Psp);
                    cargKona->ponEstadoEnLCD();
                    chEvtBroadcast(&haCambiadoPsp_source);  // notifica el cambio de PSP
                }
                const char* iminStr = doc["imin"];
                if (iminStr)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"imin\":\"%s\"}\n",iminStr);
                    float imin = atoi(iminStr);
                    iMinHR->setValor(imin);
                }
                const char* imaxStr = doc["imax"];
                if (imaxStr)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"imax\":\"%s\"}\n",imaxStr);
                    float imax = atoi(imaxStr);
                    iMaxHR->setValor(imax);
                }
                const char* numfasesStr = doc["numfases"];
                if (numfasesStr)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"numfases\":\"%s\"}\n",numfasesStr);
                    uint8_t numFases = atoi(numfasesStr);
                    numFasesHR->setValor(numFases);
                }
                const char* numcontactoresStr = doc["numcontactores"];
                if (numcontactoresStr)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"numcontactores\":\"%s\"}\n",numcontactoresStr);
                    uint8_t numContact = atoi(numcontactoresStr);
                    numContactoresHR->setValor(numContact);
                }
                // hay que reconfigurar home assistant
                if (imaxStr || iminStr || numfasesStr || numcontactoresStr)
                {
                    uint16_t pmin = 230.0f*iMinHR->getValor();
                    uint16_t pmax = numFasesHR->getValor()*230.0f*iMaxHR->getValor();
                    chprintf((BaseSequentialStream *)&SD1,"{\"orden\":\"config\",\"numfases\":\"%d\""
                             ",\"imin\":\"%.1f\",\"imax\":\"%.1f\",\"pmin\":\"%d\",\"pmax\":\"%d\",\"numcontactores\":\"%d\"}\n",
                             numFasesHR->getValor(), iMinHR->getValor(), iMaxHR->getValor(), pmin, pmax,numContactoresHR->getValor());
                }
                const char* medBaud = doc["medbaud"];
                if (medBaud)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medbaud\":\"%s\"}\n",medBaud);
                    uint32_t baudios = atoi(medBaud);
                    medBaudHR->setValor(baudios);
                }
                const char* medId = doc["medid"];
                if (medId)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medid\":\"%s\"}\n",medId);
                    uint8_t id = atoi(medId);
                    medIdHR->setValor(id);
                }
                const char* medModelo = doc["medmodelo"];
                if (medModelo)
                {
                    chprintf((BaseSequentialStream *)&SD1,"{\"medmodelo\":\"%s\"}\n",medModelo);
//                    uint8_t modMed = atoi(medModelo);
                    medModeloHR->setValor(medModelo);
                }

            }
        }
        if (evt & EVENT_MASK(1)) // Me han pedido que envie estado de coche
        {
            chprintf((BaseSequentialStream *)&SD1,"{\"coche\":\"%s\",\"psp\":\"%.1f\"}\n",cocheStr[conexCocheIR->getValor()], pSetPointModbusHR->getValor());
        }
        if (evt & EVENT_MASK(2)) // Me han pedido que envie medidas
        {
            chprintf((BaseSequentialStream *)&SD1,"%s\n",bufferMedidas);
            bufferMedidas[0] = (char) 0;
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

