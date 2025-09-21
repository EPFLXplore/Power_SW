/*
 * monitor.c
 *
 *  Created on: 5 Sep 2020
 *      Author: AV Team 2020
 */

#include "Monitor.h"
#include <stm32g4xx_hal.h>

Monitor::Monitor(Console* console) : console_(console){

}

bool Monitor::enter(uint8_t id) {
	uint32_t time = HAL_GetTick();

	if(monitor_refresh_rate[id] == 0 || time - last_update[id] < 1000 / monitor_refresh_rate[id]) {
		return false;
	}

	last_update[id] = time;

	console_->lock();

	console_->printf("\e7"); // Save cursor
	console_->printf("\x1b[%u;0H", locations[id]); // Move cursor to monitor location

	return true;
}

bool Monitor::exit(uint8_t id) {
	if(!monitor_refresh_rate[id]) {
		return false;
	}

	console_->printf("\e8"); // Restore cursor

	console_->unlock();

	return true;
}

void Monitor::enable(uint8_t id, uint8_t location, uint8_t refresh_rate) {
	locations[id] = location;
	monitor_refresh_rate[id] = refresh_rate;
}

void Monitor::disable(uint8_t id) {
	monitor_refresh_rate[id] = 0;
}

bool Monitor::is_enabled(uint8_t id) {
	return monitor_refresh_rate[id] != 0;
}

uint8_t Monitor::get_location(uint8_t id) {
	return locations[id];
}

uint8_t Monitor::get_refresh_rate(uint8_t id) {
	return monitor_refresh_rate[id];
}
