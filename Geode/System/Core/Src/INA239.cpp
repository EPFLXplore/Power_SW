/*
 * INA239.cpp
 *
 *  Created on: Aug 13, 2025
 *      Author: pedro
 */

#include "INA239.h"
#include "Console.h"

#define MAX_CURRENT 40   // A
#define SHUNT_VALUE	1000 // µΩ

#include <stdio.h>

INA239::INA239(SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin) : spi(spi), cs_port(port), cs_pin(pin) {

}

INA239::~INA239(){
}

inline void INA239::CS_low()  { HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET); }
inline void INA239::CS_high() { HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET); }

void INA239::initialize() {

	uint8_t attempts = 3;
		bool init_success = false;

		while(attempts-- > 0) {
			if(get(INA239_DEVICE_ID_REG) == INA239_DEV_ID) {
				init_success = true;
				break;
			}
		}

		if(init_success) {

			bool status = set(INA239_CONFIG_REG, INA239_CONFIG_ADCRANGE);

			uint16_t adc_config = 0;
			adc_config |= INA239_ADCCONFIG_MODE & (0xF << INA239_ADCCONFIG_MODE_BIT);
			adc_config |= INA239_ADCCONFIG_VBUSCT & (0x2 << INA239_ADCCONFIG_VBUSCT_BIT);
			adc_config |= INA239_ADCCONFIG_VSHCT & (0x2 << INA239_ADCCONFIG_VSHCT_BIT);
			adc_config |= INA239_ADCCONFIG_VTCT & (0x7 << INA239_ADCCONFIG_VTCT_BIT);
			adc_config |= INA239_ADCCONFIG_AVG & (0x3 << INA239_ADCCONFIG_AVG_BIT);

			status |= set(INA239_ADC_CONFIG_REG, adc_config);

			status |= set(INA239_SHUNT_CAL_REG, MAX_CURRENT * SHUNT_VALUE / 5);

		}

	//timer->Instance->CR1 |= TIM_CR1_CEN;
}

uint16_t INA239::get(uint8_t reg) {
	uint16_t value = 0;
	read(reg, (uint8_t*) &value, 2);
	return value;
}

float INA239::getVoltage() {
	return 1E-6f * 3125 * get(INA239_VBUS_REG);
}

float INA239::getTemperature() {
	return 1E-3f * 125 * ((int16_t) get(INA239_DIETEMP_REG) >> INA239_DIETEMP_BIT);
}

float INA239::getPower() {
	int32_t value = 0;
	read(INA239_POWER_REG, (uint8_t*) &value, 3);
	return 1E-3f * ((1000 * value * MAX_CURRENT / 5) >> 14);
}

/*float INA239::getEnergy() {
	return 1E-6f * energy / 3600;
}*/

bool INA239::set(uint8_t reg, uint16_t value) {
	return write(reg, (uint8_t*) &value, 2);
}

bool INA239::write(uint8_t reg, uint8_t *data, uint8_t size) {
	uint8_t tx_buffer[4];
	tx_buffer[0] = (reg << 2) | 0b00;

	for(uint8_t i = 0; i < size; i++) {
		tx_buffer[i+1] = data[size-i-1];
	}

	HAL_StatusTypeDef status = HAL_SPI_Transmit(spi, tx_buffer, size+1, 10 / portTICK_PERIOD_MS);


	return status == HAL_OK;
}

bool INA239::read(uint8_t reg, uint8_t *data, uint8_t size) {
	uint8_t rx_buffer[4];
	rx_buffer[0] = (reg << 2) | 0b01;

	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(spi, rx_buffer, rx_buffer, size+1, 100 / portTICK_PERIOD_MS);

	for(uint8_t i = 0; i < size; i++) {
		data[i] = rx_buffer[size-i];
	}

	return status == HAL_OK;
}
