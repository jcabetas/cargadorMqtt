/*
 * externRegistros.h
 *
 *  Created on: 2 jul 2025
 *      Author: joaquin
 */

#ifndef MODBUS_EXTERNREGISTROS_H_
#define MODBUS_EXTERNREGISTROS_H_

extern holdingRegisterInt *medIdHR;     // Id modbus medidor
extern holdingRegisterInt2Ext *medBaudHR;   // baudios medidor  {0:300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
extern holdingRegisterOpciones *medModeloHR;       // {"sdm120ct","otroMed"};
extern holdingRegisterOpciones *modoHR;            // {"manual","modbus"};
extern holdingRegisterInt *timeOutControlHR;  // tiempo para pasar a manual
extern holdingRegisterInt *ordenIdHR;         // Id modbus ordenador
extern holdingRegisterInt2Ext *ordenBaudHR;       // baudios ordenador
extern holdingRegisterInt *numFasesHR;        // #fases
extern holdingRegisterFloat *iMaxHR;            // I max (A) *100
extern holdingRegisterFloat *iMinHR;            // mA cuando no hay potencia (si es 0 abre contactor)
extern holdingRegisterInt *numContactoresHR;  // numero de contactores
extern holdingRegisterOpciones *controlContactHR;  // control de contactores (1 solo monofasico, 2: gestiona mono-tri, 3: trifasico)
extern holdingRegisterFloat *iSetPointManualHR;       // iSetpoint x100
extern holdingRegisterFloat *iSetPointModbusHR;       // iSetpoint x100
extern holdingRegisterInt *pSetPointModbusHR;       // pSetpoint modbus W


extern inputRegister *conexCocheIR; // 0: desconocido, 1: no hay coche, 2: conectado: 3: pidiendo, 4: ventilacion
extern inputRegister *medValidasIR;
extern inputRegister *IarealIR;
extern inputRegister *IbrealIR;
extern inputRegister *IcrealIR;
extern inputRegister *PrealIR;
extern inputRegister *kWhCargadosIR;  // kWh*100
extern inputRegister *kWhActualHiIR;  // kWh*100
extern inputRegister *kWhActualLoIR;  // kWh*100
extern inputRegister *numFasesRealIR;
extern inputRegister *IsetpointIR;    // *100
extern inputRegister *contactor1IR;
extern inputRegister *contactor2IR;
extern inputRegister *tLastMsgRxIR;


#endif /* MODBUS_EXTERNREGISTROS_H_ */
