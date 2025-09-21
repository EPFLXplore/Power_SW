/*
 * console.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Arion Zimmermann, Vincent Nguyen, Pedro Conde
 */


#include <stdarg.h>
#include <string.h>
#include "Monitor.h"
#include "Terminal.h"
#include "Console.h"
#include "queue.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

Monitor* monitor = nullptr;
Terminal* terminal = nullptr;

Console::Console() : Thread("Console", (osPriority)osPriorityHigh, 8192){
	monitor = new Monitor(this);

	if (monitor) {
		terminal = new Terminal(this, monitor);
	}

	console_semaphore = xSemaphoreCreateMutex();
	txQueue = xQueueCreate(10, sizeof(UsbMsg_t));
	rxQueue = xQueueCreate(10, sizeof(UsbMsg_t));

	configASSERT(txQueue);
	configASSERT(rxQueue);

	vQueueAddToRegistry(txQueue, "txQ");
	vQueueAddToRegistry(rxQueue, "rxQ");

}

Console::~Console(){
	if (monitor){
		delete monitor;
		monitor = nullptr;
	}

	if (terminal){
		delete terminal;
		terminal = nullptr;
	}
}

void Console::init(){
	this->initialText();
}

void Console::loop(){

	if (!msg_sent && UsbNotBusy()) {
		if (CDC_Transmit_FS(txQueueBuffer.data, txQueueBuffer.len) == USBD_OK) {}
	}

	// 2) If slot free AND USB configured, pull next message
	if (msg_sent && UsbConfigured()) {
		UsbMsg_t m;
	    if (xQueueReceive(txQueue, &txQueueBuffer, 0) == pdPASS) {
	    	msg_sent = false;
	    	if (UsbNotBusy()) {
	    		(void)CDC_Transmit_FS(txQueueBuffer.data, txQueueBuffer.len);
	    	}
	    }
	}

	while (xQueueReceive(rxQueue, &rxQueueBuffer, 0) == pdPASS) {
	    for (uint8_t i = 0; i < rxQueueBuffer.len; i++){
	    	terminal->receiveByte((char)rxQueueBuffer.data[i]);
	    }
	    resetRxBuffer();
	}
}

void Console::initialText(){
	this->printf("\x1b[2J\x1b[H");
	this->printf("----- EPFL Xplore Geode Shell -----\r\n");
	this->printf("Type 'help' for a list of commands\r\n");
}

void Console::enqueueTx(const uint8_t *msg, uint32_t len) {
	UsbMsg_t m;
	if (len >= sizeof(m.data)) len = sizeof(m.data) - 1;
	memcpy(m.data, msg, len);
	m.len = len;
	xQueueSend(txQueue, &m, portMAX_DELAY);
}

void Console::resetTxBuffer(){
	memset(txQueueBuffer.data, 0,txQueueBuffer.len);
	txQueueBuffer.len = 0;
}

void Console::resetRxBuffer(){
	memset(rxBuffer, 0, (size_t)USB_MSG_SIZE);
	memset(rxQueueBuffer.data, 0,rxQueueBuffer.len);
	rxQueueBuffer.len = 0;
}

void Console::enqueueRx(const uint8_t *msg, uint32_t len) {
	UsbMsg_t m;
	if (len >= sizeof(m.data)) len = sizeof(m.data) - 1;
	memcpy(m.data, msg, len);
	m.len = len;
	BaseType_t hpw = pdFALSE;
	xQueueSendFromISR(rxQueue, &m, &hpw);
	portYIELD_FROM_ISR(hpw);
}

BaseType_t Console::lock() {
    return xSemaphoreTake(console_semaphore, portMAX_DELAY);
}

BaseType_t Console::unlock() {
    return xSemaphoreGive(console_semaphore);
}

void Console::USBReceiveFromISR(uint8_t* buf, uint32_t len){
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, rxBuffer);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	this->enqueueRx(buf, len);
}

void Console::notifyTxCompleteFromISR() {
	msg_sent = true;
	BaseType_t hpw = pdFALSE;
	portYIELD_FROM_ISR(hpw);
}

void Console::print(const char* buffer) {
	this->enqueueTx((uint8_t*)buffer, strlen(buffer));
}

void Console::printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (n < 0) return;                  // format error
    if (n >= (int)sizeof(buffer)) n = sizeof(buffer) - 1; // clamp

    const char *resetColor = "\x1B[39;49m";
    //print(resetColor);
    print(buffer);
}

void Console::printf_error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (n < 0) return;                  // format error
    if (n >= (int)sizeof(buffer)) n = sizeof(buffer) - 1; // clamp
        // Apply red color formatting using ANSI escape codes
    const char *colorStart = "\x1B[31m"; // Red text color
    const char *colorEnd = "\x1B[39;49m";   // Reset text color

    print(colorStart);
    print(buffer);
    print(colorEnd);


}

void Console::printf_info(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (n < 0) return;                  // format error
    if (n >= (int)sizeof(buffer)) n = sizeof(buffer) - 1; // clamp
        // Apply red color formatting using ANSI escape codes
    const char *colorStart = "\x1B[33m"; // Yellow text color
    const char *colorEnd = "\x1B[39;49m";   // Reset text color

    print(colorStart);
    print(buffer);
    print(colorEnd);
}

void Console::printf_success(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (n < 0) return;                  // format error
    if (n >= (int)sizeof(buffer)) n = sizeof(buffer) - 1; // clamp
        // Apply red color formatting using ANSI escape codes
    const char *colorStart = "\x1B[32m"; // Yellow text color
    const char *colorEnd = "\x1B[39;49m";   // Reset text color

    print(colorStart);
    print(buffer);
    print(colorEnd);
}


