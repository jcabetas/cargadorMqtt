/*
 * externRegistros.h
 *
 *  Created on: 2 jul 2025
 *      Author: joaquin
 */

#ifndef MODBUS_EXTERNREGISTROS_H_
#define MODBUS_EXTERNREGISTROS_H_

extern holdingRegisterInt *ordenIdHR;         // Id modbus ordenador
extern holdingRegisterInt2Ext *ordenBaudHR;       // baudios ordenador
extern holdingRegisterInt *numFasesHR;        // #fases
extern holdingRegisterFloat *iMaxHR;            // I max (A) *100
extern holdingRegisterFloat *iMinHR;            // mA cuando no hay potencia (si es 0 abre contactor)
extern holdingRegisterInt *numContactoresHR;  // numero de contactores
extern holdingRegisterOpciones *controlContactHR;  // control de contactores (1 solo monofasico, 2: gestiona mono-tri, 3: trifasico)
extern holdingRegisterFloat *iSetPointModbusHR;       // iSetpoint x100


extern inputRegister *conexCocheIR; // 0: desconocido, 1: no hay coche, 2: conectado: 3: pidiendo, 4: ventilacion
extern inputRegister *medValidasIR;
extern inputRegister *IarealIR;
extern inputRegister *IbrealIR;
extern inputRegister *IcrealIR;
extern inputRegister *PrealIR;
extern inputRegister *kWhCargadosIR;  // kWh*100
extern inputRegister *kWhActualHiIR;  // kWh*100
extern inputRegister *kWhActualLoIR;  // kWh*100
extern inputRegister *kWhIniCargaHiIR;  // kWh*100
extern inputRegister *kWhIniCargaLoIR;  // kWh*100
extern inputRegister *numFasesRealIR;
extern inputRegister *IsetpointIR;    // *100
extern inputRegister *contactor1IR;
extern inputRegister *contactor2IR;
extern inputRegister *tLastMsgRxIR;


#endif /* MODBUS_EXTERNREGISTROS_H_ */
