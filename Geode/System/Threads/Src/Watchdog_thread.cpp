/*
 * Watchdog_thread.cpp
 *
 *  Created on: Aug 10, 2023
 *      Author: Vincent Nguyen
 */


#include "Watchdog_thread.h"

#include <string.h>
#include "iwdg.h"

void WatchdogThread::init() {

}

void WatchdogThread::loop() {
	HAL_IWDG_Refresh(watchdog_handle);
}
