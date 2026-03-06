/*
 * System.hpp
 *
 *  Created on: Feb 27, 2025
 *      Author: pcsal
 */

#ifndef CORE_INC_SYSTEM_H_
#define CORE_INC_SYSTEM_H_

#include "Watchdog_thread.h"
#include "TestTask.h"
//#include "Console.h"

class System {
public:
	static void init();
	static void selectCallback(I2C_HandleTypeDef *pi2c);


	//static Console* consoleThread;
	static WatchdogThread* watchdogThread;
	static TestTask* test;
};

#endif /* CORE_INC_SYSTEM_H_ */
