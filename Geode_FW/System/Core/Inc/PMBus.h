/*
 * PMBus.hpp
 *
 *  Created on: Feb 26, 2025
 *      Author: Pedro Conde
 */

#ifndef INC_PMBUS_H_
#define INC_PMBUS_H_


#include "i2c.h"
#include <stdint.h>
#include <stdio.h>
#include <array>
#include <type_traits>  // std::to_underlying in C++23 is in <utility>

#include "Console.h"
#include "PMBus_config.h"

#define DEFAULT_SR_BYTE 0x55U
#define GENERAL_ADDRESS 0x5BU //5A doesnt allow pages

#define ALL_REG_BYTES 0xFFFF

#define BUFFER_SIZE 3

#define NUM_PAGED_REG 55
#define NUM_NON_PAGED_REG 22


#define WRITE 1 //TODO
#define READ 0

// ---------- ENUMS ----------
enum class PageEnum : uint8_t {
    PAGE0    = 0x00,
    PAGE1    = 0x01,
    NOTPAGED = 0xFF
};

enum class FormatEnum : uint8_t {
    L11 = 0,
    L16 = 1,
    REG = 2
};

enum class SizeEnum : uint8_t {
    BYTE = 1U,
    WORD = 2U
};

// ---------- COMMAND STRUCT ----------
struct __attribute__((packed)) Cmd {
    uint16_t value;          // shadow (last read/write)
    uint8_t  code;           // PMBus command code
    FormatEnum format;       // encoding format
    SizeEnum size;           // byte/word
    PageEnum page;           // page (0,1, or NOTPAGED)
};


// ---------- DEVICE LEVEL REGISTERS ----------


struct VinRegs {
	Cmd on 						{0xCB40, PMBC_VIN_ON, 					FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};	
	Cmd off 					{0xCB00, PMBC_VIN_OFF, 					FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd ov_fault_limit 			{0xE300, PMBC_VIN_OV_FAULT_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd uv_fault_limit 			{0xCB26, PMBC_VIN_UV_FAULT_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd ov_fault_response 		{0x0080, PMBC_VIN_OV_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
};

struct IinRegs {
	Cmd gain 					{0x0000, MFR_IIN_CAL_GAIN, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED}; //TODO update
	Cmd oc_warning_limit 		{0x0000, PMBC_IIN_OC_WARN_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED}; //TODO update
};

struct InputReadRegs {
	Cmd vin 					{0x0000, PMBC_READ_VIN,           		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd iin 					{0x0000, PMBC_READ_IIN,           		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd pin 					{0x0000, PMBC_READ_PIN,           		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd internaltemp 			{0x0000, PMBC_READ_TEMPERATURE_2, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED}; //recheck intermal temp if its 2 or 1
};

struct InputPeakRegs {
	Cmd vin						{0x00, MFR_VIN_PEAK,      				FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd iin						{0x00, MFR_READ_IIN_PEAK,      			FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd externaltemp			{0x00, MFR_TEMPERATURE_1_PEAK, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
};

struct InputStatusRegs {
	Cmd input					{0x0000, PMBC_STATUS_INPUT,       		FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
	Cmd cml 					{0x0000, PMBC_STATUS_CML,         		FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
};

struct InputConfigRegs {
	Cmd frequency      			{0xF3E8	, PMBC_FREQUENCY_SWITCH,       	FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
	Cmd config_all 				{0x0000, MFR_CONFIG_ALL_LTC3889,      	FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
	Cmd pwm_config 				{0x0010, MFR_PWM_CONFIG_LTC3889,      	FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
	Cmd adc_control 			{0x0000, MFR_ADC_CONTROL_LTC3889,     	FormatEnum::REG, SizeEnum::BYTE, PageEnum::NOTPAGED};
	Cmd rvin 					{0x0BE8, MFR_RVIN,      				FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};
};


//---------- RAIL LEVEL REGISTERS ----------


// ---------- GROUPS ----------

struct VoutRegs {
    Cmd command 				{0x1400, PMBC_VOUT_COMMAND, 			FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd max 					{0xA000, PMBC_VOUT_MAX, 				FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ov_fault_limit 			{0x1600, PMBC_VOUT_OV_FAULT_LIMIT, 		FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ov_warn_limit 			{0x1580, PMBC_VOUT_OV_WARN_LIMIT, 		FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd uv_fault_limit 			{0x1200, PMBC_VOUT_UV_FAULT_LIMIT, 		FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd uv_warn_limit 			{0x1280, PMBC_VOUT_UV_WARN_LIMIT, 		FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd transition_rate 		{0xAA00, PMBC_VOUT_TRANSITION_RATE, 	FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ov_fault_resp 			{0x00B8, PMBC_VOUT_OV_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd uv_fault_resp 			{0x00B8, PMBC_VOUT_UV_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
};

struct IoutRegs {
	Cmd gain 					{0x0000, PMBC_IOUT_CAL_GAIN, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd gain_tc 				{0x0000, MFR_IOUT_CAL_GAIN_TC, 			FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd oc_warn_limit       	{0xDA80, PMBC_IOUT_OC_WARN_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd oc_fault_limit 			{0xDBB8, PMBC_IOUT_OC_FAULT_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd oc_fault_response 		{0x0000, PMBC_IOUT_OC_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
};

struct TonRegs {
	Cmd delay					{0x8000, PMBC_TON_DELAY, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd rise    				{0xD200, PMBC_TON_RISE, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd max_fault_limit     	{0xD280, PMBC_TON_MAX_FAULT_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd max_fault_response 	 	{0x00B8, PMBC_TON_MAX_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
};

struct ToffRegs {
	Cmd delay 					{0x8000, PMBC_TOFF_DELAY, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd fall					{0xD200, PMBC_TOFF_FALL, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd max_warn_limit 			{0xF258, PMBC_TOFF_MAX_WARN_LIMIT, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
};

struct TimingRegs {
	TonRegs time_to_turn_on;
	ToffRegs time_to_turn_off;
};

struct TempRegs {
	Cmd ot_warn_limit			{0xEAA8, PMBC_OT_WARN_LIMIT, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ot_fault_limit 			{0xEB20, PMBC_OT_FAULT_LIMIT, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ut_fault_limit 			{0xE580, PMBC_UT_FAULT_LIMIT, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd ot_fault_response 		{0x00B8, PMBC_OT_FAULT_RESPONSE, 		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd ut_fault_response 		{0x00B8, PMBC_UT_FAULT_RESPONSE, 		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd temp_1_gain 			{0x4000, MFR_TEMP_1_GAIN, 				FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0}; //Is technically a custom format
	Cmd temp_1_offset 			{0x8000, MFR_TEMP_1_OFFSET, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
};

struct RailConfigRegs {
	Cmd channel_config 			{0x001D, MFR_CHAN_CONFIG_LTC3889, 		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd fault_propagate 		{0x6993, MFR_FAULT_PROPAGATE_LTC3889, 	FormatEnum::REG, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd pwm_mode 				{0x00C1, MFR_PWM_MODE_LTC3889, 			FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd pwm_comp 				{0x0070, MFR_PWM_COMP_LTC3889, 			FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd fault_response 			{0x00C0, MFR_FAULT_RESPONSE_LTC3889, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd retry_delay 			{0xFABC, MFR_RETRY_DELAY_LTC3889, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd restart_delay 			{0xFBE8, MFR_RESTART_DELAY_LTC3889, 	FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd hw_vout_max 			{0xA200, PMBC_MFR_VOUT_MAX, 			FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
};

struct OutputStatusRegs {
	Cmd byte 					{0x0000, PMBC_STATUS_BYTE, 				FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd word 					{0x0000, PMBC_STATUS_WORD, 				FormatEnum::REG, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd vout 					{0x0000, PMBC_STATUS_VOUT, 				FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd iout 					{0x0000, PMBC_STATUS_IOUT, 				FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd temp 					{0x0000, PMBC_STATUS_TEMPERATURE, 		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd mfr_specific 			{0x0000, PMBC_STATUS_MFR_SPECIFIC, 		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
};

struct OutputReadRegs {
	Cmd vout 					{0x00, PMBC_READ_VOUT, 					FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd iout					{0x00, PMBC_READ_IOUT, 					FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd temp					{0x00, PMBC_READ_TEMPERATURE_1, 		FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd freq					{0x00, PMBC_READ_FREQUENCY, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd pout					{0x00, PMBC_READ_POUT, 					FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
};

struct OutputPeakRegs {
	Cmd vout					{0x00, MFR_VOUT_PEAK, 					FormatEnum::L16, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd iout 					{0x00, MFR_READ_IIN_PEAK, 				FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
	Cmd externaltemp			{0x00, MFR_TEMPERATURE_1_PEAK, 			FormatEnum::L11, SizeEnum::WORD, PageEnum::PAGE0};
};

struct Rail {
    Cmd operation    			{0x0040, PMBC_OPERATION,          		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
    Cmd on_off_config 			{0x001E, PMBC_ON_OFF_CONFIG,      		FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};
	Cmd vin_ov_fault_response 	{0x0080, PMBC_VIN_OV_FAULT_RESPONSE, 	FormatEnum::REG, SizeEnum::BYTE, PageEnum::PAGE0};

	VoutRegs vout;
	IoutRegs iout;
	TimingRegs timing;
	RailConfigRegs config;
	OutputStatusRegs status;
	OutputReadRegs read;
	OutputPeakRegs peak;

	// Pin mapping
	PageEnum label = PageEnum::NOTPAGED;
	GPIO_TypeDef * port = nullptr;
	uint16_t pin = 0;

}; 




class PMBus {
public:
	PMBus(I2C_HandleTypeDef* bus_handle, uint8_t address);
	~PMBus();

	/**
	 * @brief Send the passed command to the module and update the register.
	 * @param cmd: The command to set.
	 * @param decoded_value: The value to set.
	 * @return HALstatus of the command.
	 */
	HAL_StatusTypeDef set(Cmd& cmd, float decoded_value);

	/**
	 * @brief Send the passed command to the module and get the value.
	 * @param cmd: The command to get.
	 * @param decoded_out: The value to get.
	 * @return HALstatus of the command.
	 */
	HAL_StatusTypeDef get(Cmd& cmd, float& decoded_out);
	
	/**
	 * @brief Resets the module.
	 * @return HALstatus of the command.
	 */
	HAL_StatusTypeDef reset();

	/**
	 * @brief Sets the RUN pin of the module.
	 * @param status: The register to get the status of.
	 */
	void setRUNpinState(Rail& rail, GPIO_PinState pin_state);

	/**
	 * @brief Gets the current registered status of a register/pin.
	 * @param status: The register to get the status of.
	 * @return status register value of the command.
	 */
	GPIO_PinState getRUNpinState(Rail& rail);


	/**
	 * @brief Selects the rail to be used.
	 * @param rail: The rail to be used.
	 * @return HAL status of the command.
	 */
	HAL_StatusTypeDef selectPage(Rail& page);	

	/**
	 * @brief Clears the fault values.
	 * @return HAL status of the command.
	 */
	HAL_StatusTypeDef clearFaults();

	/**
	 * @brief Clears the peak values.
	 * @return HAL status of the command.
	 */
	HAL_StatusTypeDef clearPeaks();

	/**
	 * @brief Gets the current status of  the fault pin of the module.
	 * @param status: The register to get the status of.
	 * @return status register value of the command.
	 */
	GPIO_PinState getFAULTpin(Rail& rail);

	 /**
     * @brief callback function to identify what caused the fault/alert
     * @return status of the command.
     */
    HAL_StatusTypeDef processCallback();




private:
	Cmd page_cmd 			{0x0000, PMBC_PAGE, 					FormatEnum::L11, SizeEnum::WORD, PageEnum::NOTPAGED};

	VinRegs vin;
	IinRegs iin;
	
	InputReadRegs read;
	InputPeakRegs peak;
	InputStatusRegs status;
	InputConfigRegs config;

    // Two paged rails
    Rail page0;
    Rail page1;
	Rail* selected_page;

	I2C_HandleTypeDef * pi2c;
	uint8_t module_address; //was 16?

	//----------FAULTS-MONITORING-------------

    bool fault_rail0 = false;
    bool fault_rail1 = false;


	/**
	 * @brief Decodes a custom L11 bit value to a float.
	 * Floating point 16-bit data: value = Y • 2^N, where N = b[15:11] and Y = b[10:0],
	 * both two’s compliment binary integers.
	 * @param raw_value: The raw value to decode.
	 * @return The decoded value.
	 */
	float decodeLinear11(uint16_t raw_value);

	/**
	 * @brief Encodes a float to a custom L11 bit value.
	 * Floating point 16-bit data: value = Y • 2^N, where N = b[15:11] and Y = b[10:0],
	 * both two’s compliment binary integers.
	 * @param value: The value to encode.
	 * @return The encoded value.
	 */
	uint16_t encodeLinear11(float value);

	/**
	 * @brief Decodes a linear 16 bit value to a float.
	 * Floating point 16-bit data: value = Y • 2^(–10),
	 * where Y = b[15:0], an unsigned integer.
	 * @param raw_value: The raw value to decode.
	 * @return The decoded value.
	 */
	float decodeLinear16(uint16_t raw_value);

	/**
	 * @brief Encodes a float to a linear 16 bit value.
	 * Floating point 16-bit data: value = Y • 2^(–10),
	 * where Y = b[15:0], an unsigned integer.
	 * @param raw_value: The value to encode.
	 * @return The encoded value.
	 */
	uint16_t encodeLinear16(float raw_value);


	/**
	* @brief functions that run security checks on the passed command
	* @param command_label: the label that represents the command to modify
	* @param decoded_value: the floating point value that needs to pass the checks
	* @return if it passed the checks //TODO change to bools
	*/
	HAL_StatusTypeDef securityCheck(Cmd& cmd, float decoded_value);

	inline HAL_StatusTypeDef MaximumOutputVoltageChecks(float decoded_value);
	inline HAL_StatusTypeDef InputVoltageWarningChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputVoltageChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputOverVoltageWarningChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputOverVoltageFaultChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputUnderVoltageWarningChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputUnderVoltageFaultChecks(float decoded_value);
	inline HAL_StatusTypeDef OutputOverCurrentWarningChecks(float decoded_value);
	inline HAL_StatusTypeDef ManufacturerSpecificPowerModeChecks(); //TODO use
	inline HAL_StatusTypeDef ManufacturerSpecificPowerConfigChecks(); //TODO use
	inline HAL_StatusTypeDef FrequencyChecks();



	/**
     * @brief callback function that comes from the status VOUT register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackVOUT();

    /**
     * @brief callback function that comes from the status IOUT register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackIOUT();

    /**
     * @brief callback function that comes from the status TEMP register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackTEMP();

    /**
     * @brief callback function that comes from the status INPUT register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackINPUT();

    /**
     * @brief callback function that comes from the status CML register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackCML();

    /**
     * @brief callback function that comes from the status MFR_SPECIFIC register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackMFRSpecific();

    /**
     * @brief callback function that comes from the status POWER_GOOD register
     * @return status of the command.
     */
    HAL_StatusTypeDef callbackPowerGood();


};


#endif /* INC_PMBUS_H_ */
