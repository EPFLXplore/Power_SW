/*
 * INA239.cpp
 *
 *  Created on: Aug 13, 2025
 *      Author: pedro
 */

#include "INA239.h"
//#include "Console.h"

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
			// This sets bit 4 of the config register to 1
			// It sets the range of the shunt voltage to +-40.96$ mV meaning steps of 1.25 µV.
			// This is ok since the max current is 40A and the shunt resistor is 1000 µΩ maening a max voltage of 40 mV.
			bool status = set(INA239_CONFIG_REG, INA239_CONFIG_ADCRANGE);

			uint16_t adc_config = 0;
			adc_config |= INA239_ADCCONFIG_MODE & (0xF << INA239_ADCCONFIG_MODE_BIT);
			// Bus Voltage Conversion Time (VBUSCT) : For the voltage readings.
			//0h = 50 µs , 1h = 84 µs , 2h = 150 µs ,  3h = 280 µs , 4h = 540 µs
			//5h = 1052 µs , 6h = 2074 µs , 7h = 4120 µs
			adc_config |= INA239_ADCCONFIG_VBUSCT & (0x4 << INA239_ADCCONFIG_VBUSCT_BIT);
			// Shunt Voltage Conversion Time (VSHCT) : For the current readings.
			// Same values as VBUSCT
			adc_config |= INA239_ADCCONFIG_VSHCT & (0x4 << INA239_ADCCONFIG_VSHCT_BIT);
			adc_config |= INA239_ADCCONFIG_VTCT & (0x7 << INA239_ADCCONFIG_VTCT_BIT);
			// Averaging
			//0h = 1, 1h = 4, 2h = 16,  3h = 64, 4h = 128, 5h = 256 ,6h = 512 ,7h = 1024
			adc_config |= INA239_ADCCONFIG_AVG & (0x4 << INA239_ADCCONFIG_AVG_BIT);

			status |= set(INA239_ADC_CONFIG_REG, adc_config);

			//status |= set(INA239_SHUNT_CAL_REG, MAX_CURRENT * SHUNT_VALUE / 5);
			//SHUNT_CAL = 819.2 x 10^6 x CURRENT_LSB x R_SHUNT / 4 = 819.2 x 106 x MAX_CURRENT x R_SHUNT/(2^15 X 4) = 250
			// Remark : We divide by 4 because :  For ADCRANGE = 1, the value of SHUNT_CAL must be multiplied by 4
			status |= set(INA239_SHUNT_CAL_REG, 4000);
		}

	//timer->Instance->CR1 |= TIM_CR1_CEN;
}


uint16_t INA239::get(uint8_t reg) {
	uint16_t value = 0;
	read(reg, (uint8_t*) &value, 2);
	return value;
}

float INA239::getVoltage() {
	// Calibration average offset is approximately 0.353 V.
	return 1E-6f * 3125 * get(INA239_VBUS_REG);
	// Might need to add a voltage offset to get the voltage at the input
}

float INA239::getCurrent() {
	int16_t raw_current = (int16_t) get(INA239_CURRENT_REG);
	// Calculate the Current LSB: MAX_CURRENT / 2^15
	float current_lsb = MAX_CURRENT / 32768.0f;
	return raw_current * current_lsb* (-3.34);
	// To be changed depending on the board
}

float INA239::getShuntVoltage() {
    // Register 0x4 contains the raw shunt voltage.
    int16_t raw_vshunt = (int16_t) get(INA239_VSHUNT_REG);

    // Because ADCRANGE is set to 1, each bit represents 1.25 uV
    return raw_vshunt * 1.25E-6f;
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

	CS_low();
	HAL_StatusTypeDef status = HAL_SPI_Transmit(spi, tx_buffer, size+1, 10 ); // 10 / portTICK_PERIOD_MS
	CS_high();

	return status == HAL_OK;
}

bool INA239::read(uint8_t reg, uint8_t *data, uint8_t size) {
	uint8_t rx_buffer[4];
	rx_buffer[0] = (reg << 2) | 0b01;

	CS_low();
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(spi, rx_buffer, rx_buffer, size+1, 100 ); // 100 / portTICK_PERIOD_MS
	CS_high();

	for(uint8_t i = 0; i < size; i++) {
		data[i] = rx_buffer[size-i];
	}

	return status == HAL_OK;
}
