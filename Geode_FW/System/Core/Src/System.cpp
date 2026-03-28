/*
 * System->cpp
 *
 *  Created on: Feb 27, 2025
 *      Author: pcsal
 */


#include "System.h"
#include "spi.h"
#include "tim.h"
#include "adc.h"
#include "iwdg.h"

//Console* console = nullptr;
//Console* System::consoleThread = nullptr;
WatchdogThread* System::watchdogThread = nullptr;
TestTask* System::test = nullptr;

void System::init(){
    //Allocate memory for the watchdog thread
	watchdogThread = new WatchdogThread(&hiwdg);

    //Starting the watchdog thread
	watchdogThread->start();

    ////Allocate memory for the custom shell
    //consoleThread = new Console();
    //console = System::consoleThread;

	//Allocate memory for the test thread
	test = new TestTask();

	//Creating tasks
	//console->start();
	test->start();
}
/*void System::selectCallback(I2C_HandleTypeDef *pi2c){

    HAL_StatusTypeDef status;
    if (pi2c == &hi2c2){
        //status = pmbus2->module_problem = true; //TODO
    } else if (pi2c == &hi2c3){
        //status = pmbus3->module_problem = true;
    }
    if (status != HAL_OK){
    	//console->printf_error("Error: SMBUS stack error\r\n");
    }
}*/
