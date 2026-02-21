/*
 * console.h
 *
 *  Created on: 11 Feb 2020
 *      Author: AV Team 2020
 */

#ifndef APPLICATION_HOSTBOARD_INC_DEBUG_CONSOLE_H_
#define APPLICATION_HOSTBOARD_INC_DEBUG_CONSOLE_H_



#include <stdio.h>

#include <stm32g4xx_hal.h>
#include <cmsis_os.h>
#include <semphr.h>

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "Thread.h"


#define CONSOLE_BUFFER_SIZE 512
#define USB_MSG_SIZE 64
#define USB_TX_QUEUE_SIZE 10
#define USB_RX_QUEUE_SIZE 10

extern USBD_HandleTypeDef hUsbDeviceFS;

static inline bool UsbConfigured(void) {
    return (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) &&
           (hUsbDeviceFS.pClassData != NULL);
}

static inline bool UsbNotBusy(void) {
    if (!UsbConfigured()) return false;
    USBD_CDC_HandleTypeDef *hcdc =
        (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    return hcdc->TxState == 0;
}



typedef struct {
    uint8_t data[USB_MSG_SIZE];
    size_t len;
} UsbMsg_t;


class Console : public Thread {
public:
	Console();
	~Console();
	BaseType_t lock();
	BaseType_t unlock();
	void loop();
	void init();
	void initialText();
	void enqueueTx(const uint8_t *msg, uint32_t len);
	void enqueueRx(const uint8_t *msg, uint32_t len);
	void resetTxBuffer();
	void resetRxBuffer();
	void USBReceiveFromISR(uint8_t* buf, uint32_t len);
	void notifyTxCompleteFromISR();
	void print(const char* buffer);
	void printf(const char* format, ...);
	void printf_error(const char* format, ...);
	void printf_info(const char* format, ...);
	void printf_success(const char* format, ...);

	QueueHandle_t console_semaphore;

private:

	UsbMsg_t txQueueBuffer{};
	UsbMsg_t rxQueueBuffer{};

	uint8_t rxBuffer[USB_MSG_SIZE];

	char buffer[USB_MSG_SIZE];
	volatile bool msg_sent = true;
	QueueHandle_t txQueue;
	QueueHandle_t rxQueue;


};

extern Console* console;


#endif /* APPLICATION_HOSTBOARD_INC_DEBUG_CONSOLE_H_ */
