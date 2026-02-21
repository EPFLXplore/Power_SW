/*
 * terminal.c
 *
 *  Created on: 6 Sep 2020
 *      Authors: Arion Zimmermann, Vincent Nguyen
 */

#include "Terminal.h"

#include <stm32g4xx_hal.h>
#include <stdlib.h>
#include "Monitor.h"


#define EQUALS(index, str) (cmd->num_components > (index) && cmd->components[(index)].matches((str)))

Terminal::Terminal(Console* console, Monitor* monitor) : console_(console), monitor_(monitor){
	resetParser();
}

void Terminal::execute(ShellCommand* cmd, Console* feedback) {
	if(cmd->num_components > 0) {
		if(EQUALS(0, "help")) {
			feedback->printf("> Geode available commands:\r\n");
			feedback->printf("> clear: clears the screen\r\n");
			feedback->printf("> help: shows this help page\r\n");
			feedback->printf("> time: prints the current system time\r\n");
			feedback->printf("> monitor: enables or disables a specific monitor\r\n");
			feedback->printf("> profiler: enables or disables the embedded profiler\r\n");
			feedback->printf("> reset: performs a software reset of the avionics\r\n");
			feedback->printf("> version: displays the current terminal version\r\n");
			feedback->printf("> info: prints system info\r\n");

			/*feedback->printf_info("> Geode available commands:\r\n");
			feedback->printf_info("> clear: clears the screen\r\n");
			feedback->printf_info("> help: shows this help page\r\n");
			feedback->printf_info("> time: prints the current system time\r\n");
			feedback->printf_info("> monitor: enables or disables a specific monitor\r\n");
			feedback->printf_info("> profiler: enables or disables the embedded profiler\r\n");
			feedback->printf_info("> reset: performs a software reset of the avionics\r\n");
			feedback->printf_info("> version: displays the current terminal version\r\n");
			feedback->printf_info("> info: prints system info\r\n");*/
		} else if(EQUALS(0, "version")) {
			feedback->printf("> Xplore Geode Terminal v1.0 \r\n");
			//feedback->printf_info("> Xplore Geode Terminal v1.0 \r\n");
		} else if(EQUALS(0, "reset")) {
			HAL_NVIC_SystemReset();
		} else if(EQUALS(0, "time")) {
			feedback->printf("%d\r\n", HAL_GetTick());
			feedback->printf("%d\r\n", HAL_GetTick());
		} else if(EQUALS(0, "clear")) {
			feedback->printf("\x1b[2J\x1b[H\e7");
			feedback->printf("\x1b[%u;0H", location);

		} else if (EQUALS(0, "info")) {
			feedback->printf("> System: \t Geode version 1.0\r\n");
			feedback->printf("> Hardware by Federico Bise \r\n");
			feedback->printf("> Firmware by Pedro Conde\r\n");
			feedback->printf("> Special mention: Threads, Shell, Console and Monitors base classes by Arion Zimmermann and Vincent Nguyen\r\n");

			/*feedback->printf_info("> System: \t Geode version 1.0\r\n");
			feedback->printf_info("> Hardware by Federico Bise \r\n");
			feedback->printf_info("> Firmware by Pedro Conde\r\n");
			feedback->printf_info("> Special mention: Threads, Shell, Console and Monitors base classes by Arion Zimmermann and Vincent Nguyen\r\n");*/
		} else if(EQUALS(0, "monitor")) {
			if(EQUALS(1, "list")) {
				feedback->printf("> Currently available monitor IDs: \r\n");
				feedback->printf("> moduleA0 \r\n");
				feedback->printf("> moduleA1 \r\n");
				feedback->printf("> moduleB0 \r\n");
				feedback->printf("> moduleB1 \r\n");
				feedback->printf("> battery \r\n");

				/*feedback->printf_info("> Currently available monitor IDs: \r\n");
				feedback->printf_success("> moduleA0 \r\n");
				feedback->printf_success("> moduleA1 \r\n");
				feedback->printf_success("> moduleB0 \r\n");
				feedback->printf_success("> moduleB1 \r\n");
				feedback->printf_success("> battery \r\n");*/
			}
			else if(EQUALS(1, "enable") && cmd->num_components >= 3) {
				uint8_t refresh_rate = 10;
				uint8_t custom_loc = 1;

				if(cmd->num_components > 3) {
					custom_loc = atoi(cmd->components[3].component);
				}

				if(cmd->num_components > 4) {
					refresh_rate = atoi(cmd->components[4].component);
				}

				if(EQUALS(2, "moduleA0")) {
					if (!monitor_->is_enabled(MODULEA_RAIL0_MONITOR)) {
							uint8_t chosen_loc;
							if(cmd->num_components == 3) {
								chosen_loc = location;
							} else {
								chosen_loc = custom_loc;
							}
							location++;
							monitor_->enable(MODULEA_RAIL0_MONITOR, chosen_loc, refresh_rate);
							feedback->printf("\x1b[2J");
						} else {
							feedback->printf("> Module A Rail 0 monitor already enabled\r\n");
							//feedback->printf_error("> Module A Rail 0 monitor already enabled\r\n");
						}
				}
				if(EQUALS(2, "moduleA1")) {
					if (!monitor_->is_enabled(MODULEA_RAIL1_MONITOR)) {
							uint8_t chosen_loc;
							if(cmd->num_components == 3) {
								chosen_loc = location;
							} else {
								chosen_loc = custom_loc;
							}
							location++;
							monitor_->enable(MODULEA_RAIL1_MONITOR, chosen_loc, refresh_rate);
							feedback->printf("\x1b[2J");
						} else {
							feedback->printf("> Module A Rail 1 monitor already enabled\r\n");
							//feedback->printf_error("> Module A Rail 1 monitor already enabled\r\n");
						}
				}
				if(EQUALS(2, "moduleB0")) {
					if (!monitor_->is_enabled(MODULEB_RAIL0_MONITOR)) {
							uint8_t chosen_loc;
							if(cmd->num_components == 3) {
								chosen_loc = location;
							} else {
								chosen_loc = custom_loc;
							}
							location++;
							monitor_->enable(MODULEB_RAIL0_MONITOR, chosen_loc, refresh_rate);
							feedback->printf("\x1b[2J");
						} else {
							feedback->printf("> Module B Rail 0 monitor already enabled\r\n");
							//feedback->printf_error("> Module B Rail 0 monitor already enabled\r\n");
						}
				}
				if(EQUALS(2, "moduleB1")) {
					if (!monitor_->is_enabled(MODULEB_RAIL1_MONITOR)) {
							uint8_t chosen_loc;
							if(cmd->num_components == 3) {
								chosen_loc = location;
							} else {
								chosen_loc = custom_loc;
							}
							location++;
							monitor_->enable(MODULEB_RAIL1_MONITOR, chosen_loc, refresh_rate);
							feedback->printf("\x1b[2J");
						} else {
							feedback->printf("> Module B Rail 1 monitor already enabled\r\n");
							//feedback->printf_error("> Module B Rail 1 monitor already enabled\r\n");
						}
				}
				if(EQUALS(2, "battery")) {
					if (!monitor_->is_enabled(BATTERY)) {
							uint8_t chosen_loc;
							if(cmd->num_components == 3) {
								chosen_loc = location;
							} else {
								chosen_loc = custom_loc;
							}
							location++;
							monitor_->enable(BATTERY, chosen_loc, refresh_rate);
							feedback->printf("\x1b[2J");
						} else {
							feedback->printf("> Battery monitor already enabled\r\n");
							//feedback->printf_error("> Battery monitor already enabled\r\n");
						}
				}
				else {
					feedback->printf("> %.*s: Invalid monitor ID\r\n", cmd->components[2].length, cmd->components[2].component);
					//feedback->printf_error("> %.*s: Invalid monitor ID\r\n", cmd->components[2].length, cmd->components[2].component);
				}
				feedback->printf("\x1b[%u;0H", location); // Move cursor to end of monitors

			} else if(EQUALS(1, "enable") && cmd->num_components == 2) {
				uint8_t refresh_rate = 10;
				if (!monitor_->is_enabled(MODULEA_RAIL0_MONITOR)) {
						monitor_->enable(MODULEA_RAIL0_MONITOR, location, refresh_rate);
						feedback->printf("\x1b[2J");
						location++;
					}
				if (!monitor_->is_enabled(MODULEA_RAIL1_MONITOR)) {
						monitor_->enable(MODULEA_RAIL1_MONITOR, location, refresh_rate);
						feedback->printf("\x1b[2J");
						location++;
					}
				if (!monitor_->is_enabled(MODULEB_RAIL0_MONITOR)) {
						monitor_->enable(MODULEB_RAIL0_MONITOR, location, refresh_rate);
						feedback->printf("\x1b[2J");
						location++;
					}
				if (!monitor_->is_enabled(MODULEB_RAIL0_MONITOR)) {
						monitor_->enable(MODULEB_RAIL0_MONITOR, location, refresh_rate);
						feedback->printf("\x1b[2J");
						location++;
					}

				if (!monitor_->is_enabled(BATTERY)) {
						monitor_->enable(BATTERY, location, refresh_rate);
						feedback->printf("\x1b[2J");
						location++;
					}

				osDelay(150); // Wait a bit for monitors to appear
				feedback->printf("\x1b[2J");
				feedback->printf("\x1b[%u;0H", location); // Move cursor to end of monitors

			} else if(EQUALS(1, "disable") && cmd->num_components == 3) {
				if(EQUALS(2, "moduleA0")) {
					monitor_->disable(MODULEA_RAIL0_MONITOR);
						update_monitors(monitor_->get_location(MODULEA_RAIL0_MONITOR));
						location--;
				}
				else if(EQUALS(2, "moduleA1")) {
					monitor_->disable(MODULEA_RAIL1_MONITOR);
						update_monitors(monitor_->get_location(MODULEA_RAIL1_MONITOR));
						location--;
				}
				else if(EQUALS(2, "moduleB0")) {
					monitor_->disable(MODULEB_RAIL0_MONITOR);
						update_monitors(monitor_->get_location(MODULEB_RAIL0_MONITOR));
						location--;
				}
				else if(EQUALS(2, "moduleB1")) {
					monitor_->disable(MODULEB_RAIL1_MONITOR);
						update_monitors(monitor_->get_location(MODULEB_RAIL1_MONITOR));
						location--;
				}
				else if(EQUALS(2, "battery")) {
					monitor_->disable(BATTERY);
						update_monitors(monitor_->get_location(BATTERY));
						location--;
				}
				else {
					feedback->printf("> %.*s: Invalid monitor ID\r\n", cmd->components[2].length, cmd->components[2].component);
					//feedback->printf_error("> %.*s: Invalid monitor ID\r\n", cmd->components[2].length, cmd->components[2].component);
				}
				feedback->printf("\x1b[%u;0H", location); // Move cursor to end of monitors
				feedback->printf("\x1b[2J");
			} else if(EQUALS(1, "disable") && cmd->num_components == 2) {
				location = 0;
				disable_monitors(feedback);
			}
			else {
				feedback->printf("> Usage:\r\n");
				feedback->printf("> monitor { enable | disable } device_id [location] [refresh rate; default: 10]\r\n");
				feedback->printf("> monitor list\r\n");

				//feedback->printf_info("> Usage:\r\n");
				//feedback->printf_info("> monitor { enable | disable } device_id [location] [refresh rate; default: 10]\r\n");
				//feedback->printf_info("> monitor list\r\n");
			}
		} else {
			//feedback->printf_error("> %.*s: command not found\r\n", cmd->components[0].length, cmd->components[0].component);
			feedback->printf("> %.*s: command not found\r\n", cmd->components[0].length, cmd->components[0].component);
		}
	}
}

void Terminal::update_monitors(uint8_t loc, uint8_t num_lines) {
	for (uint8_t i = 0; i < MAX_MONITORS; ++i) {
		if (monitor_->is_enabled(i) && monitor_->get_location(i) >= loc) {
			monitor_->enable(i, monitor_->get_location(i)-num_lines, monitor_->get_refresh_rate(i));
		}
	}
}

void Terminal::disable_monitors(Console* feedback) {
	location = 1;
	monitor_->disable(MODULEA_RAIL0_MONITOR);
	feedback->printf("\x1b[2J");
	monitor_->disable(MODULEA_RAIL0_MONITOR);
	feedback->printf("\x1b[2J");
	monitor_->disable(MODULEA_RAIL0_MONITOR);
	feedback->printf("\x1b[2J");
	monitor_->disable(MODULEA_RAIL0_MONITOR);
	feedback->printf("\x1b[2J");
	monitor_->disable(BATTERY);
	feedback->printf("\x1b[2J");
	monitor_->disable(MOTORS);
	feedback->printf("\x1b[2J");
	feedback->printf("\x1b[2J\x1b[H\e7");
}

inline void Terminal::resetParser() {
    command_index = 0;
    cmd.num_components = 0;
    cmd.components[0].length = 0;
    cmd.components[0].component = command_buffer;   // critical
}

void Terminal::receiveByte(char c) {
    if (c == '\0') return;

    if (c != '\n' && c != '\r' && command_index < CMD_BUFFER_SIZE) {
        command_buffer[command_index++] = c;

        if (c == ' ') {
            if (cmd.num_components + 1 < CMD_MAX_COMPONENTS) {
                size_t start =
                    static_cast<size_t>(cmd.components[cmd.num_components].component - command_buffer);
                cmd.components[cmd.num_components].length =
                    (command_index - 1 > start) ? (command_index - 1 - start) : 0;
                cmd.num_components++;
                cmd.components[cmd.num_components].component = &command_buffer[command_index];
                cmd.components[cmd.num_components].length = 0;
            }
        }
        return;
    }

    size_t start =
    	static_cast<size_t>(cmd.components[cmd.num_components].component - command_buffer);
    cmd.components[cmd.num_components].length =
    	(command_index > start) ? (command_index - start) : 0;
    if (cmd.components[cmd.num_components].length > 0 &&
    	cmd.num_components + 1 <= CMD_MAX_COMPONENTS) {
    	cmd.num_components++;
    }

    // optional NUL
    if (command_index < CMD_BUFFER_SIZE) command_buffer[command_index] = '\0';

    this->execute(&cmd, console_);
    console_->printf("\n");
    resetParser();   // always
}


#undef EQUALS

