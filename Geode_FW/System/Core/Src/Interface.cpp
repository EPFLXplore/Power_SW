/*
 * Interface.cpp
 *
 *  Created on: Jul 8, 2025
 *      Author: pedro
 */

#include "System.h"

#ifdef __cplusplus
extern "C" {
#endif


void InterfaceSystemInit(){
	System::init();
}

void InterfaceUSBReceiveFromISR(uint8_t* Buf, uint32_t Len){
	//System::consoleThread->USBReceiveFromISR(Buf, Len);
}

void InterfaceNotifyTxCompleteFromISR(){
	//System::consoleThread->notifyTxCompleteFromISR();
}

#ifdef __cplusplus
}
#endif



