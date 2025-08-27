#ifndef CARGADOR_H_
#define CARGADOR_H_

#include "modbus.h"

#define MAXDSCAMBIORELE 300

typedef enum { RDESCONOCIDO=0, RDESCONECTADO, RCONECTADO, RPIDECARGA, RPIDEVENTILACION} estadoRes_t;
//typedef enum { DESCONOCIDO=0, DESCONECTADO, RECIENCONECTADO, CARGANDO_MAX, CARGANDO_POCO,
//               CARGADO, ESPERANDOCAPACIDAD, DIODOMAL } estadoCarga_t;
//
//typedef enum {CPFIJO=0, CPMAXIMO, CPNOEXPORTA, CPDESCONOCIDO} tipoControlP_t;
//typedef enum {TMFIJO=0, TMESCLAVO, TMMAESTRO, TMDESCONOCIDO} tipoMaestro_t;

class cargador
{
private:
    uint8_t osciladorOculto;
    uint8_t ondaNegOk;
    bool haCambiadoR;
    estadoRes_t oldStatusResis;
    uint16_t dsCambioRele2;          // solo cambia si ha pasado mas de 30s
    uint16_t dsSinModbus;
public:
    cargador(void);
    void fijaAmperios(float amperios);
    void ocultaOscilador(void);
    void sacaOscilador(void);
    void initCargador(void);
    void initOscilador(void);
    void initReles(void);
    void ponReles(void);
    void estimaValoresADC(void);
    void bucleCargador(void);
    void controlIntensidad(void);
    void cambioEstado(void);
    void incrementaTimers(uint16_t ds);
    void setEstadoRes(estadoRes_t estR);
    estadoRes_t getEstadoRes(void);
    void ponEstadoEnLCD(void);
    void initADC(void);
    int8_t init(void);
};


#endif /* CARGADOR_H_ */
