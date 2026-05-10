/*
 * colas.h
 *
 *  Created on: 5 may. 2018
 *      Author: joaquin
 */

#ifndef COLASRXTX_H_
#define COLASRXTX_H_

struct msgRx_t {
  time_t timet;
  uint8_t numBytes;
  int16_t rssi;
  uint8_t msg[30];
};

struct msgTx_t {
  uint8_t numBytes;
  uint8_t msg[30];
};



#endif /* COLASRXTX_H_ */
