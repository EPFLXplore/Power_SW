/*
 * monitor.h
 *
 *  Created on: 5 Sep 2020
 *      Author: AV Team 2020
 */

#ifndef APPLICATION_HOSTBOARD_INC_DEBUG_MONITOR_H_
#define APPLICATION_HOSTBOARD_INC_DEBUG_MONITOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "Console.h"

#define MAX_MONITORS 36

typedef enum {
	MODULEA_RAIL0_MONITOR = 1,
	MODULEA_RAIL1_MONITOR,
	MODULEB_RAIL0_MONITOR,
	MODULEB_RAIL1_MONITOR,
	BATTERY,
	MOTORS,
} PowerMonitor;

class Monitor {
public:
	Monitor(Console* console);
	bool enter(uint8_t id);
	bool exit(uint8_t id);

	void enable(uint8_t id, uint8_t location, uint8_t refresh_rate);
	void disable(uint8_t id);

	bool is_enabled(uint8_t id);
	uint8_t get_location(uint8_t id);
	uint8_t get_refresh_rate(uint8_t id);
private:

	Console* console_;

	uint8_t locations[MAX_MONITORS];
	uint8_t monitor_refresh_rate[MAX_MONITORS];
	uint32_t last_update[MAX_MONITORS];
};


#endif /* APPLICATION_HOSTBOARD_INC_DEBUG_MONITOR_H_ */
