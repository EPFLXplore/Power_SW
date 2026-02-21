/*
 * Interface.h
 *
 *  Created on: Jul 8, 2025
 *      Author: pedro
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_


void InterfaceSystemInit();

void InterfaceUSBReceiveFromISR(uint8_t* Buf, uint32_t Len);

void InterfaceNotifyTxCompleteFromISR();


#endif /* INTERFACE_H_ */
