/*
 * System->cpp
 *
 *  Created on: Feb 27, 2025
 *      Author: pcsal
 */


#include "System.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "adc.h"
#include "iwdg.h"

Console* console = nullptr;
Console* System::consoleThread = nullptr;
WatchdogThread* System::watchdogThread = nullptr;
TestTask* System::test = nullptr;

void System::init(){
    //Allocate memory for the watchdog thread
	watchdogThread = new WatchdogThread(&hiwdg);

    //Starting the watchdog thread
	watchdogThread->start();

    ////Allocate memory for the custom shell
    consoleThread = new Console();
    console = System::consoleThread;

	//Allocate memory for the test thread
	test = new TestTask();

	//Creating tasks
	console->start();
	test->start();
}

