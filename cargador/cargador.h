#ifndef CARGADOR_H_
#define CARGADOR_H_

#include "modbus.h"


typedef enum { RDESCONOCIDO=0, RDESCONECTADO, RCONECTADO, RPIDECARGA, RPIDEVENTILACION} estadoRes_t;


class cargador
{
private:
    uint8_t osciladorOculto;
    uint8_t ondaNegOk;
    uint8_t numFasesReal;
    bool haCambiadoR;
    estadoRes_t oldStatusResis;
    systime_t horaDescFaltapot;
    systime_t horaHayMuchaPot;
public:
    cargador(void);
    void fijaAmperios(float amperios);
    void ocultaOscilador(void);
    void sacaOscilador(void);
    void initOscilador(void);
    void initReles(void);
    void estimaValoresADC(void);
    void bucleCargador(void);
    void controlCarga(void);
    void cambioEstado(void);
    void incrementaTimers(uint16_t ds);
    void ponReles(uint8_t rele1, uint8_t rele2);
    void setNumFasesReal(uint8_t numFasesPar);
    uint8_t getNumFasesReal(void);
    void setEstadoRes(estadoRes_t estR);
    estadoRes_t getEstadoRes(void);
    void ponEstadoEnLCD(void);
    void initADC(void);
    int8_t init(void);
};


#endif /* CARGADOR_H_ */
