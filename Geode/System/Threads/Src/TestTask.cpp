/*
 * TestTask.cpp
 *
 *  Created on: Jul 9, 2025
 *      Author: pedro
 */

#include <TestTask.h>
#include "System.h"

#include "spi.h"
#include "tim.h"

TestTask::TestTask() : Thread("TestingTask", (osPriority)osPriorityNormal5){

}

void TestTask::init(){

}

void TestTask::loop(){

}

