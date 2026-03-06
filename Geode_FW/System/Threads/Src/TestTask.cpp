/*
 * TestTask.cpp
 *
 *  Created on: Jul 9, 2025
 *      Author: pedro
 */

#include <TestTask.h>
#include <cstdio>
#include <string.h>
#include "System.h"
#include "spi.h"
#include "tim.h"
#include "usbd_cdc_if.h"

TestTask::TestTask() : Thread("TestingTask", (osPriority)osPriorityNormal5){

}

void TestTask::init(){
	inaSens = new INA239(&hspi1, GPIOA, GPIO_PIN_4);
	inaSens->initialize();

	//pmbus = new PMBus(&hi2c2, 0x7C);
}

void TestTask::loop(){
	//printf("Testing SWO output...\n");
	//fflush(stdout);
	//char my_message[] = "Hello from STM32!\r\n";
	//CDC_Transmit_FS((uint8_t*)my_message, strlen(my_message));

	uint16_t shunt_cal = inaSens->getShuntCal();
	uint16_t config    = inaSens->getConfig();
	char dbg[128];
	uint16_t dbg_len = snprintf(dbg, sizeof(dbg),
		"SHUNT_CAL: %u (exp 4000), CONFIG: 0x%04X (exp bit4=1)\r\n",shunt_cal, config);
	CDC_Transmit_FS((uint8_t*)dbg, dbg_len);
	// Read the values from the sensor
	float current = inaSens->getCurrent();
	float voltage = inaSens->getVoltage();
	//float temp = inaSens->getTemperature();
	//float power = inaSens->getPower();
	//float shuntvoltage = inaSens->getShuntVoltage();


	// Create a buffer large enough to hold the formatted string
	char buffer[512];

	// Format the floats into the buffer (using 3 decimal places for V/W, 2 for Temp)
	//uint16_t len = snprintf(buffer, sizeof(buffer),
	//						"Voltage: %.3f V, current: %.3f A, ShuntVoltage %.3f V, power: %.3f W, Temp: %.2f C\r\n",
	//						voltage, current, power,shuntvoltage, temp);
	uint16_t len = snprintf(buffer, sizeof(buffer),
								"current: %.3f A ,Voltage: %.3f V",
								current, voltage);

	// Transmit the buffer over USB
	CDC_Transmit_FS((uint8_t*)buffer, len);

	// Wait 2 seconds before the next reading
	osDelay(2000);
	//console->printf("Power: %f \r\n", inaSens->getPower());
	//console->printf("Temperature: %f \r\n", inaSens->getTemperature());
	//console->printf("Voltage: %f \r\n", inaSens->getVoltage());
	//osDelay(2000);

	//HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c2, (0x7C<<1), 5, 1000);
	//console->printf("Device Ready: %d \r\n", status);
	//uint16_t value = 3;
	//status = HAL_I2C_Mem_Read(&hi2c2, (0x5A<<1), 0x88, I2C_MEMADD_SIZE_8BIT, reinterpret_cast<uint8_t*>(&value), sizeof(value), 300);
	//osDelay(100);
	//console->printf("Status: %d, Raw VIN: 0x%04X\r\n", status, value);
	//ClearFaultsOnce();
	//osDelay(10000);
	//if (HAL_I2C_IsDeviceReady(&hi2c2, (0x7C << 1), 2, 10) == HAL_OK) {
	//	console->printf("I2C device found at 0x7C\r\n");
	//}
	/*
	uint8_t val;
	uint8_t cmd = CMD_STATUS_BYTE;
	HAL_StatusTypeDef status;
	status = HAL_I2C_Master_Transmit(&hi2c2, (0x7C << 1), &cmd, 1, 100);
	console->printf("STATUS_HAL = %d\r\n", status);
	status = HAL_I2C_Master_Receive(&hi2c2, (0x7C << 1), &val, 1, 100);
	console->printf("STATUS_HAL = %d\r\n", status);
	console->printf("STATUS_BYTE = 0x%02X\r\n", val);
	*/

	//uint8_t fault0 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
	//uint8_t fault1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	//uint8_t alert = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);

	//console->printf("FAULT0 = %d, FAULT1 = %d, ALERT = %d \r\n", fault0, fault1, alert);
	//LTC3889_Diag_WP();
	//osDelay(10000);
	//osDelay(10000);
}

/*
void I2C_Scan(void) {
	console->printf("Scanning I2C bus...\r\n");

    for (uint8_t addr = 1; addr < 128; addr++) {
        // Shifted left by 1 because HAL expects 8-bit address
        if (HAL_I2C_IsDeviceReady(&hi2c2, (addr << 1), 2, 10) == HAL_OK) {
        	console->printf("I2C device found at 0x%02X\r\n", addr);
        }
    }

    console->printf("Scan done.\r\n");
}

void TestTask::ClearFaultsOnce(){
	if (cleared == false){
		uint8_t cmd = 0x03;
		cleared = true;
		HAL_I2C_Master_Transmit(&hi2c2, (0x5B << 1), &cmd, 1, 100); // or device address
	}
	console->printf("Faults cleared\r\n");
}

#define CMD_STATUS_MFR_SPEC  0x80
#define CMD_STATUS_BYTE  0x78


#define ADDR_GLOBAL_PAGED   (0x5B << 1)   // paged global address
#define ADDR_7C   (0x7C << 1)   // paged global address
#define CMD_MFR_EE_UNLOCK   0xBD
#define CMD_STORE_USER_ALL  0x15
#define CMD_CLEAR_FAULTS    0x03
#define CMD_MFR_RESET       0xFD
#define CMD_WRITE_PROTECT   0x10
#define CMD_MFR_COMMON      0xEF



HAL_StatusTypeDef LTC3889_ReadStatusMfrSpecific(uint8_t devAddr7, uint8_t *status)
{
    HAL_StatusTypeDef ret;
    uint8_t cmd = CMD_STATUS_MFR_SPEC;

    // Write command code
    ret = HAL_I2C_Master_Transmit(&hi2c3, (0x7C << 1), &cmd, 1, HAL_MAX_DELAY);
    if (ret != HAL_OK) return ret;

    // Read 1-byte response
    ret = HAL_I2C_Master_Receive(&hi2c3, (0x7C << 1), status, 1, HAL_MAX_DELAY);
    return ret;
}


// SMBus PEC (CRC-8 polynomial 0x07, initial 0x00)
static uint8_t pec_crc8(const uint8_t *data, int len) {
    uint8_t crc = 0;
    for (int i = 0; i < len; i++) {
        crc ^= data[i];
        for (int b = 0; b < 8; b++) {
            if (crc & 0x80) crc = (crc << 1) ^ 0x07;
            else crc <<= 1;
        }
    }
    return crc;
}

void LTC3889_RecoverPEC(void) {
    HAL_StatusTypeDef ret;
    uint8_t addr_w = (0x5B << 1);   // 8-bit write address for 0x5B
/*
    // ---------------------------
    // 1) Unlock EEPROM step 1 (0x2B)
    uint8_t tmp1[3] = { CMD_MFR_EE_UNLOCK, 0x2B, 0 };
    uint8_t pec1_buf[3] = { addr_w, CMD_MFR_EE_UNLOCK, 0x2B };
    tmp1[2] = pec_crc8(pec1_buf, 3);
    ret = HAL_I2C_Master_Transmit(&hi2c2, addr_w, tmp1, 3, 10000);
    console->printf("Unlock EEPROM step1 status: %d\r\n", ret);
    HAL_Delay(10);

    // 1b) Unlock EEPROM step 2 (0xC4)
    uint8_t tmp2[3] = { CMD_MFR_EE_UNLOCK, 0xC4, 0 };
    uint8_t pec2_buf[3] = { addr_w, CMD_MFR_EE_UNLOCK, 0xC4 };
    tmp2[2] = pec_crc8(pec2_buf, 3);
    ret = HAL_I2C_Master_Transmit(&hi2c2, addr_w, tmp2, 3, 10000);
    console->printf("Unlock EEPROM step2 status: %d\r\n", ret);
    HAL_Delay(10);

    // ---------------------------
    // 2) STORE_USER_ALL (send-byte with PEC)
    uint8_t tmp3[2] = { CMD_STORE_USER_ALL, 0 };
    uint8_t pec3_buf[2] = { addr_w, CMD_STORE_USER_ALL };
    tmp3[1] = pec_crc8(pec3_buf, 2);
    ret = HAL_I2C_Master_Transmit(&hi2c2, addr_w, tmp3, 2, 10000);
    console->printf("Store RAM in NVM (PEC) status: %d\r\n", ret);
    HAL_Delay(1500); // EEPROM write may take up to a few seconds

    // ---------------------------
    // 3) CLEAR_FAULTS (send-byte with PEC)
    uint8_t tmp4[2] = { CMD_CLEAR_FAULTS, 0 };
    uint8_t pec4_buf[2] = { addr_w, CMD_CLEAR_FAULTS };
    tmp4[1] = pec_crc8(pec4_buf, 2);
    ret = HAL_I2C_Master_Transmit(&hi2c2, addr_w, tmp4, 2, 10000);
    console->printf("Clear faults (PEC) status: %d\r\n", ret);
    HAL_Delay(20);
*/
    // ---------------------------
    // 4) MFR_RESET (send-byte with PEC)
    /*
	uint8_t tmp5[2] = { CMD_MFR_RESET, 0 };
    uint8_t pec5_buf[2] = { addr_w, CMD_MFR_RESET };
    tmp5[1] = pec_crc8(pec5_buf, 2);
    ret = HAL_I2C_Master_Transmit(&hi2c2, addr_w, tmp5, 2, 10000);
    console->printf("Soft reset (PEC) status: %d\r\n", ret);
    HAL_Delay(200);

}


void LTC3889_Diag_WP(void)
{
    HAL_StatusTypeDef ret;
    uint8_t cmd;
    uint8_t val;

    // ---- Read MFR_COMMON (bit0 = WP pin status) from 0x7C ----
    cmd = CMD_MFR_COMMON;
    ret = HAL_I2C_Master_Transmit(&hi2c2, ADDR_7C, &cmd, 1, 200);
    if (ret == HAL_OK) {
        ret = HAL_I2C_Master_Receive(&hi2c2, ADDR_7C, &val, 1, 200);
        if (ret == HAL_OK) {
        	console->printf("MFR_COMMON = 0x%02X (bit0 = WP pin)\r\n", val);
        } else {
        	console->printf("MFR_COMMON read receive failed\r\n");
        }
    } else {
    	console->printf("MFR_COMMON transmit failed\r\n");
    }

    // ---- Read WRITE_PROTECT (0x10) from 0x5B ----
    cmd = CMD_WRITE_PROTECT;
    ret = HAL_I2C_Master_Transmit(&hi2c2, ADDR_GLOBAL_PAGED , &cmd, 1, 200);
    if (ret == HAL_OK) {
        ret = HAL_I2C_Master_Receive(&hi2c2, ADDR_GLOBAL_PAGED, &val, 1, 200);
        if (ret == HAL_OK) {
        	console->printf("WRITE_PROTECT = 0x%02X\r\n", val);
        } else {
        	console->printf("WRITE_PROTECT read receive failed\r\n");
        }
    } else {
    	console->printf("WRITE_PROTECT transmit failed\r\n");
    }
}


void TestTask::LTC3889_Recover(void) {

		HAL_StatusTypeDef ret;
		uint8_t u;

		// 1) Unlock EEPROM
		u = 0x2B;
		ret = HAL_I2C_Mem_Write(&hi2c2, ADDR_GLOBAL_PAGED,
								CMD_MFR_EE_UNLOCK,
								I2C_MEMADD_SIZE_8BIT, &u, 1, 100);
		osDelay(10);
		console->printf("Unlock EEPROM read status: %d\r\n", ret);

		u = 0xC4;
		ret = HAL_I2C_Mem_Write(&hi2c2, ADDR_GLOBAL_PAGED,
								CMD_MFR_EE_UNLOCK,
								I2C_MEMADD_SIZE_8BIT, &u, 1, 100);
		osDelay(10);
		console->printf("Unlock EEPROM write status: %d\r\n", ret);

		if (HAL_I2C_IsDeviceReady(&hi2c2, (0x7C << 1), 2, 10) == HAL_OK) {
			console->printf("I2C device found at 0x7C\r\n");
		}

		// 2) Store current RAM config into EEPROM user space
		uint8_t cmd = CMD_STORE_USER_ALL;
		ret = HAL_I2C_Master_Transmit(&hi2c2, ADDR_GLOBAL_PAGED, &cmd, 1, 100);
		osDelay(500); // EEPROM write can take time (datasheet worst case seconds)
		console->printf("Store RAM in NVM status: %d\r\n", ret);

		// 3) Clear faults
		cmd = CMD_CLEAR_FAULTS;
		ret = HAL_I2C_Master_Transmit(&hi2c2, ADDR_GLOBAL_PAGED, &cmd, 1, 100);
		osDelay(10);
		console->printf("Clear faults status: %d\r\n", ret);

		// 4) Soft reset (like a power cycle)
		cmd = CMD_MFR_RESET;
		ret = HAL_I2C_Master_Transmit(&hi2c2, ADDR_GLOBAL_PAGED, &cmd, 1, 100);
		osDelay(100);
		console->printf("Soft reset: %d\r\n", ret);


}




//CDC_Transmit_FS((uint8_t*)"Hello from STM32G4\r\n", 21);
*/
