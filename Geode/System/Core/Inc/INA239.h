/*
 * INA239.h
 *
 *  Created on: Aug 13, 2025
 *      Author: pedro
 */

#ifndef CORE_INC_INA239_H_
#define CORE_INC_INA239_H_

#include "Monitor.h"

#include <spi.h>
#include <tim.h>


#define INA239_CONFIG_REG 			0x0
#define INA239_ADC_CONFIG_REG 		0x1
#define INA239_SHUNT_CAL_REG		0x2
#define INA239_VSHUNT_REG			0x4
#define INA239_VBUS_REG				0x5
#define INA239_DIETEMP_REG			0x6
#define INA239_CURRENT_REG			0x7
#define INA239_POWER_REG			0x8
#define INA239_DIAG_ALRT_REG		0xB
#define INA239_SOVL_REG				0xC
#define INA239_SUVL_REG				0xD
#define INA239_BOVL_REG				0xE
#define INA239_BUVL_REG				0xF
#define INA239_TEMP_LIMIT_REG		0x10
#define INA239_PWR_LIMIT_REG		0x11
#define INA239_MANUFACTURER_ID_REG	0x3E
#define INA239_DEVICE_ID_REG		0x3F


#define INA239_CONFIG_RST			0b1000000000000000
#define INA239_CONFIG_CONVDLY		0b0011111111000000
#define INA239_CONFIG_ADCRANGE		0b0000000000010000
#define INA239_CONFIG_RST_BIT		15
#define INA239_CONFIG_CONVDLY_BIT	6
#define INA239_CONFIG_ADCRANGE_BIT	4

#define INA239_ADCCONFIG_MODE		0b1111000000000000
#define INA239_ADCCONFIG_VBUSCT		0b0000111000000000
#define INA239_ADCCONFIG_VSHCT		0b0000000111000000
#define INA239_ADCCONFIG_VTCT		0b0000000000111000
#define INA239_ADCCONFIG_AVG		0b0000000000000111
#define INA239_ADCCONFIG_MODE_BIT	12
#define INA239_ADCCONFIG_VBUSCT_BIT	9
#define INA239_ADCCONFIG_VSHCT_BIT	6
#define INA239_ADCCONFIG_VTCT_BIT	3
#define INA239_ADCCONFIG_AVG_BIT	0

#define INA239_DIETEMP_BIT	 		4

#define INA239_MANUFACTURER_ID 		0x5449
#define INA239_DEV_ID 				0x2391


class INA239{
public:
	INA239(SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin);
	~INA239();

	void initialize();
	float getPower();
	//float getEnergy();
	float getVoltage();
	float getTemperature();

    //TIM_HandleTypeDef * getTimerHandle() { return timer; };

    //float energy = 0.0f;
    //uint32_t last_time = 0;

private:
	SPI_HandleTypeDef* spi;
	//TIM_HandleTypeDef* timer;

	GPIO_TypeDef* cs_port;
	uint16_t cs_pin;

	inline void CS_low();
	inline void CS_high();

	uint16_t get(uint8_t reg);
	bool set(uint8_t reg, uint16_t value);

	bool write(uint8_t reg, uint8_t *data, uint8_t size);
	bool read(uint8_t reg, uint8_t *data, uint8_t size);
};


#endif /* CORE_INC_INA239_H_ */
