/*
 * TestTask.h
 *
 *  Created on: Jul 9, 2025
 *      Author: pedro
 */

#ifndef THREADS_INC_TESTTASK_H_
#define THREADS_INC_TESTTASK_H_

#include "Thread.h"
#include "INA239.h"
#include "PMBus.h"


class TestTask : public Thread {
public:
	TestTask();

	void init();
	void loop();
	void ClearFaultsOnce();
	void LTC3889_Recover();
private:
	INA239 * inaSens;
	PMBus * pmbus;
	bool cleared = false;
};

#endif /* THREADS_INC_TESTTASK_H_ */
