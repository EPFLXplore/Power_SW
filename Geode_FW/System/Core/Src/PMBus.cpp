/*
 * PMBus.cpp
 *
 *  Created on: Feb 26, 2025
 *      Author: pedro
 */

#include "PMBus.h"

PMBus::PMBus(I2C_HandleTypeDef* bus_handle, uint8_t address) : pi2c(bus_handle), module_address(address){
    page0.label = PageEnum::PAGE0;
    page1.label = PageEnum::PAGE1;
}

PMBus::~PMBus(){

}

float PMBus::decodeLinear16(uint16_t raw_value) {
    return (float)raw_value / 1024.0f;
}

uint16_t PMBus::encodeLinear16(float value) {
    // multiply first, then clamp and cast
    int32_t scaled = (int32_t)(value * 1024.0f);
    if (scaled < 0)       scaled = 0;
    else if (scaled > 0xFFFF) scaled = 0xFFFF;
    return (uint16_t)scaled;
}

uint16_t PMBus::encodeLinear11(float value) {
    if (value == 0.0f) return 0;

    // try exponents from -16..+15
    int chosen_e = 0;
    int32_t mant_i = 0;
    for (int e = -16; e <= 15; ++e) {
        // compute value / (2^e) without math.h
        float scaled;
        if (e < 0) {
            // multiply by 2^(-e)
            scaled = value * (1 << (-e));
        } else {
            // divide by 2^e
            scaled = value / (1 << e);
        }
        // round to nearest integer
        int32_t m = (int32_t)(scaled + (scaled >= 0.0f ? 0.5f : -0.5f));
        // check 11-bit signed range
        if (m >= -1024 && m <= 1023) {
            chosen_e = e;
            mant_i    = m;
            break;
        }
    }

    // pack exponent (5-bit two’s comp) and mantissa (11-bit two’s comp)
    uint16_t e5 = (uint16_t)(chosen_e & 0x1F) << 11;
    uint16_t m11 = (uint16_t)(mant_i & 0x07FF);
    return e5 | m11;
}

float PMBus::decodeLinear11(uint16_t raw) {
    // unpack 11-bit signed mantissa
    int16_t mant = raw & 0x07FF;
    if (mant & 0x0400) mant |= 0xF800;
    // unpack 5-bit signed exponent
    int8_t exp5 = (raw >> 11) & 0x1F;
    if (exp5 & 0x10) exp5 |= 0xE0;

    // apply
    float r;
    if (exp5 >= 0) {
        r = (float)mant * (1 << exp5);
    } else {
        r = (float)mant / (float)(1 << -exp5);
    }

    return r;
}


HAL_StatusTypeDef PMBus::reset(){
    //return set(); //Resetting device //TODO add cmd
}

HAL_StatusTypeDef PMBus::set(Cmd& cmd, float decoded_value) {
    uint16_t raw = 0;

    if (pi2c == nullptr) {
        console->printf_error("Error: I2C handle is null!\r\n");
        return HAL_ERROR;
    }

    if (selected_page == nullptr) {
        console->printf_error("Error: No rail selected!\r\n");
        return HAL_ERROR;
    }

       // --- security checks BEFORE encoding ---
    if (!securityCheck(cmd, decoded_value)) {
        console->printf_error("Security check failed for cmd 0x%02X\r\n", cmd.code);
        return HAL_ERROR;
    }

    // --- Encode according to format ---
    switch (cmd.format) {
        case FormatEnum::L11: raw = encodeLinear11(decoded_value); break;
        case FormatEnum::L16: raw = encodeLinear16(decoded_value); break;
        case FormatEnum::REG: raw = static_cast<uint16_t>(decoded_value); break;
        default:
            console->printf_error("Invalid format for cmd 0x%02X\r\n", cmd.code);
            return HAL_ERROR;
    }

    // --- Prepare buffer ---
    uint8_t buf[2];
    uint8_t size = (cmd.size == SizeEnum::WORD ? 2 : 1);
    buf[0] = static_cast<uint8_t>(raw & 0xFF);
    if (size == 2) buf[1] = static_cast<uint8_t>((raw >> 8) & 0xFF);

    // --- Perform I2C write ---
    HAL_StatusTypeDef  HAL_status = HAL_I2C_Mem_Write(
        pi2c,
        module_address << 1,
        cmd.code,
        I2C_MEMADD_SIZE_8BIT,
        buf,
        size,
        300
    );

    // --- Update shadow only if successful ---
    if (HAL_status == HAL_OK) {
        cmd.value = raw;
        console->printf_info("Wrote cmd 0x%02X = 0x%04X\r\n", cmd.code, raw);
    } else {
        console->printf_error("Error writing cmd 0x%02X\r\n", cmd.code);
    }

    return HAL_status;
}

HAL_StatusTypeDef PMBus::get(Cmd& cmd, float& decoded_out) {
    if (pi2c == nullptr) {
        console->printf_error("Error: I2C handle is null!\r\n");
        return HAL_ERROR;
    }

    if (selected_page == nullptr) {
        console->printf_error("Error: No rail selected!\r\n");
        return HAL_ERROR;
    }

    uint8_t buf[2] = {0};
    uint16_t len = (cmd.size == SizeEnum::WORD) ? 2 : 1;

    HAL_StatusTypeDef  HAL_status = HAL_I2C_Mem_Read(
        pi2c,
        (module_address << 1),
        cmd.code,
        I2C_MEMADD_SIZE_8BIT,
        buf,
        len,
        300
    );

    if (HAL_status == HAL_OK) {
        const uint16_t raw = (len == 2) ? (uint16_t)(buf[0] | (buf[1] << 8)) : (uint16_t)buf[0];
        cmd.value = raw;  // shadow mirrors device only on success
        switch (cmd.format) {
            case FormatEnum::L11: decoded_out = decodeLinear11(cmd.value);
            case FormatEnum::L16: decoded_out = decodeLinear16(cmd.value);
            case FormatEnum::REG: decoded_out = static_cast<float>(cmd.value);
                default:              return HAL_ERROR;
        }
        console->printf_info("Read  0x%02X = 0x%04X (%.6f)\r\n", cmd.code, raw, decoded_out);
    } else {
        console->printf_error("I2C read failed for 0x%02X (status=%d)\r\n", cmd.code, (int)HAL_status);
    }
    return HAL_status;
}


HAL_StatusTypeDef PMBus::securityCheck(Cmd& cmd, float decoded_value) {

    switch (cmd.code) {
        case PMBC_VOUT_MAX:
            return MaximumOutputVoltageChecks(decoded_value);
        case PMBC_VOUT_COMMAND:
            return OutputVoltageChecks(decoded_value);
        case PMBC_VOUT_OV_WARN_LIMIT:
            return OutputOverVoltageWarningChecks(decoded_value);
        case PMBC_VOUT_OV_FAULT_LIMIT:
            return OutputOverVoltageFaultChecks(decoded_value);
        case PMBC_VOUT_UV_WARN_LIMIT:
            return OutputUnderVoltageWarningChecks(decoded_value);
        case PMBC_VOUT_UV_FAULT_LIMIT:
            return OutputUnderVoltageFaultChecks(decoded_value);
        case PMBC_IOUT_OC_WARN_LIMIT:
            return OutputOverCurrentWarningChecks(decoded_value);
        default:
            break;

    }
} 



//----------------------------------------------------Security Cheks----------------------------------------------------

inline HAL_StatusTypeDef PMBus::MaximumOutputVoltageChecks(float decoded_value){

    float hardware_limit = 0;
    
	HAL_StatusTypeDef  HAL_status = get(selected_page->config.hw_vout_max, hardware_limit);

        if (decoded_value > hardware_limit){
            console->printf_error("Maximum voltage out of range! Manufacturer limit is %f V\r\n", hardware_limit);
            HAL_status = HAL_ERROR;
        } else if (decoded_value < 0.0f) {
            console->printf_error("Error: Maximum voltage cannot be negative!\r\n");
            HAL_status = HAL_ERROR;
        } else if (decoded_value < decodeLinear16(selected_page->vout.command.value)){
            console->printf_error("Error: Maximum voltage cannot be lower than the selected output voltage level!\r\n");
            HAL_status = HAL_ERROR;
        } else {
        	HAL_status = HAL_OK;
        }
        return HAL_status;
}

inline HAL_StatusTypeDef PMBus::InputVoltageWarningChecks(float decoded_value){

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if ((vin.on.value == 0xCB40) || (vin.off.value == 0xCB00)){ //double check values
        console->printf_error("Error: Cannot set undervoltage warning level before setting input voltage thresholds!\r\n");
        HAL_status = HAL_ERROR;
    } else if (decoded_value < vin.on.value){
        console->printf_error("Error: Undervoltage warning level cannot be lower than input voltage lower threshold!\r\n");
        HAL_status = HAL_ERROR;
    } else if (decoded_value > vin.off.value){
        console->printf_error("Error: Undervoltage warning level cannot be higher than input voltage higher threshold!\r\n");
        HAL_status = HAL_ERROR;
    }
    return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputVoltageChecks(float decoded_value){


	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (selected_page->vout.max.value == 0){
        HAL_status = HAL_ERROR;
        console->printf_info("Maximum voltage not set! Please set it first\r\n");
    } else if (decoded_value > decodeLinear16(selected_page->vout.max.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Voltage out of range! Maximum voltage is %f V\r\n", decodeLinear16(selected_page->vout.max.value));
    } else if (decoded_value < 0.0f) {
        HAL_status = HAL_ERROR;
        console->printf_info("Error: Output voltage cannot be negative!\r\n");
    } else {
        HAL_status = HAL_OK;
    }

   return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputOverVoltageWarningChecks(float decoded_value){

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (decodeLinear16(selected_page->vout.max.value) == 0){
        HAL_status = HAL_ERROR;
        console->printf_info("Maximum voltage not set! Please set it first\r\n");
    } else if (decoded_value > decodeLinear16(selected_page->config.hw_vout_max.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Overvoltage warning cannot be higher than mfr limit of %f\r\n", decodeLinear16(selected_page->config.hw_vout_max.value));

    } else {
       HAL_status = HAL_OK;
    }
   return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputOverVoltageFaultChecks(float decoded_value){

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (decodeLinear16(selected_page->vout.max.value) == 0){
        HAL_status = HAL_ERROR;
        console->printf_info("Maximum voltage not set! Please set it first\r\n");
    } else if (decoded_value > decodeLinear16(selected_page->config.hw_vout_max.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Overvoltage fault cannot be higher than mfr limit of %f\r\n", decodeLinear16(selected_page->config.hw_vout_max.value));
    } else if (decoded_value < decodeLinear16(selected_page->vout.ov_warn_limit.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Overvoltage fault cannot be lower than warning limit of %f\r\n", decodeLinear16(selected_page->vout.ov_warn_limit.value));
    } else {
        HAL_status = HAL_OK;
    }

   return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputUnderVoltageWarningChecks(float decoded_value){

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (decodeLinear16(selected_page->vout.max.value) == 0){
        HAL_status = HAL_ERROR;
        console->printf_info("Maximum voltage not set! Please set it first\r\n");
    } else if (decoded_value > decodeLinear16(selected_page->config.hw_vout_max.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Undervoltage warning cannot be higher than mfr limit of %f\r\n", decodeLinear16(selected_page->config.hw_vout_max.value));

    } else {
       HAL_status = HAL_OK;
    }
   return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputUnderVoltageFaultChecks(float decoded_value){

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (decodeLinear16(selected_page->vout.max.value) == 0){
        HAL_status = HAL_ERROR;
        console->printf_info("Maximum voltage not set! Please set it first\r\n");
    } else if (decoded_value > decodeLinear16(selected_page->config.hw_vout_max.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Undervoltage fault cannot be higher than mfr limit of %f\r\n", decodeLinear16(selected_page->config.hw_vout_max.value));
    } else if (decoded_value > decodeLinear16(selected_page->vout.uv_warn_limit.value)){
        HAL_status = HAL_ERROR;
        console->printf_info("Warning voltage out of range! Undervoltage fault cannot be higher than warning limit of %f\r\n", decodeLinear16(selected_page->vout.uv_warn_limit.value));
    } else {
        HAL_status = HAL_OK;
    }

   return HAL_status;
}

inline HAL_StatusTypeDef PMBus::OutputOverCurrentWarningChecks(float decoded_value){ //TODO: REVISE

	HAL_StatusTypeDef  HAL_status = HAL_OK;

    if (decoded_value >= 25.0f/decodeLinear11(selected_page->iout.gain.value) && decoded_value <= 50.0f/decodeLinear11(selected_page->iout.gain.value)){
        if (selected_page->operation.value == TURN_OFF){
            set(selected_page->config.pwm_mode, selected_page->config.pwm_mode.value &= ~MFR_PWM_MODE_ILIMIT_HIGH_RANGE_MASK);
        } else {
            console->printf_error("Error: Output overcurrent fault cannot be changed while the module is on!\r\n");
            HAL_status = HAL_ERROR;
        }
    } else {
        set(selected_page->config.pwm_mode, selected_page->config.pwm_mode.value |= MFR_PWM_MODE_ILIMIT_HIGH_RANGE_MASK);
        console->printf_info("Power mode set to high current %f A\r\n", decoded_value);
    }
    return HAL_status;
}

inline HAL_StatusTypeDef PMBus::ManufacturerSpecificPowerModeChecks(){
    if (selected_page->operation.value == TURN_ON){
        console->printf_error("Error: PWM mode cannot be set while the module is on!\r\n");
        return HAL_ERROR;
    } else {
        return HAL_OK;
    }
}
//then remove the functions except for the HW intial functions

inline HAL_StatusTypeDef PMBus::ManufacturerSpecificPowerConfigChecks(){
    if (selected_page->operation.value == TURN_ON){ //include run pin check
        console->printf_error("Error: Manufacturer specific register cannot be set while the module is on!\r\n");
        return HAL_ERROR;
    } else {
        return HAL_OK;
    }
}

inline HAL_StatusTypeDef PMBus::FrequencyChecks(){
	if (selected_page->operation.value == TURN_ON){ //include run pin check
		console->printf_error("Error: Frequency register cannot be set while the module is on!\r\n");
		return HAL_ERROR;
	} else {
		return HAL_OK;
	}
}

HAL_StatusTypeDef PMBus::selectPage(Rail& page_to_select){
    HAL_StatusTypeDef  HAL_status = HAL_OK;

    selected_page = &page_to_select;
    HAL_status = set(page_cmd, static_cast<std::uint16_t>(page_to_select.label));

    return HAL_status;
}

void PMBus::setRUNpinState(Rail& rail, GPIO_PinState pin_state){

    switch(rail.label){
        case PageEnum::PAGE0:
            if (pi2c == &hi2c2){
                HAL_GPIO_WritePin(RUN0_A_GPIO_Port, RUN0_A_Pin, pin_state);
                console->printf("RUN0 module A pin set\r\n");
            }
            if (pi2c == &hi2c3){
                HAL_GPIO_WritePin(RUN0_B_GPIO_Port, RUN0_B_Pin, pin_state);
                console->printf("RUN0 module B pin set\r\n");
            }
            break;
        case PageEnum::PAGE1:
            if (pi2c == &hi2c2){
                HAL_GPIO_WritePin(RUN1_A_GPIO_Port, RUN1_A_Pin, pin_state);
                console->printf("RUN1 module A pin set\r\n");
            }
            if (pi2c == &hi2c3){
                HAL_GPIO_WritePin(RUN1_B_GPIO_Port, RUN1_B_Pin, pin_state);
                console->printf("RUN1 module B pin set\r\n");
            }
            break;
        default:
            break;
        }
    }


GPIO_PinState PMBus::getRUNpinState(Rail& rail){ //TODO: double check how are the pins configured

	GPIO_PinState state = GPIO_PIN_RESET;

    switch(rail.label){
        case PageEnum::PAGE0:
            if (pi2c == &hi2c2){
            	state = HAL_GPIO_ReadPin(RUN0_A_GPIO_Port, RUN0_A_Pin);
            }
            if (pi2c == &hi2c3){
            	state = HAL_GPIO_ReadPin(RUN0_B_GPIO_Port, RUN0_B_Pin);
            }
            break;
        case PageEnum::PAGE1:
            if (pi2c == &hi2c2){
            	state = HAL_GPIO_ReadPin(RUN1_A_GPIO_Port, RUN1_A_Pin);
            }
            if (pi2c == &hi2c3){
            	state = HAL_GPIO_ReadPin(RUN1_B_GPIO_Port, RUN1_B_Pin);
            }
            break;
        default:
            console->printf_error("Error: Invalid rail!\r\n");
            break;
    }
    return state;
}



HAL_StatusTypeDef PMBus::clearPeaks(){
    HAL_StatusTypeDef  HAL_status = HAL_OK;
 //   HAL_status = set(selected_page->); //TODO add cmd
    console->printf_info("Peak values cleared\r\n");
    return HAL_status;
}

HAL_StatusTypeDef PMBus::clearFaults(){
    HAL_StatusTypeDef HAL_status = HAL_OK;
//   HAL_status = set(selected_page->); //TODO add cmd
    console->printf_info("Fault values cleared\r\n");
    return HAL_status;
}

GPIO_PinState PMBus::getFAULTpin(Rail& rail){

	GPIO_PinState state = GPIO_PIN_RESET;

    switch(rail.label){
        case PageEnum::PAGE0:
            if (pi2c == &hi2c2){
            	state = HAL_GPIO_ReadPin(FAULT0_A_GPIO_Port, FAULT0_A_Pin);
            }
            if (pi2c == &hi2c3){
            	state = HAL_GPIO_ReadPin(FAULT0_B_GPIO_Port, FAULT0_B_Pin);
            }
            break;
        case PageEnum::PAGE1:
            if (pi2c == &hi2c2){
            	state = HAL_GPIO_ReadPin(FAULT1_A_GPIO_Port, FAULT1_A_Pin);
            }
            if (pi2c == &hi2c3){
            	state = HAL_GPIO_ReadPin(FAULT1_B_GPIO_Port, FAULT1_B_Pin);
            }
            break;
        default:
            console->printf_error("Error: Invalid rail!\r\n");
            break;
    }
    return state;
}




HAL_StatusTypeDef PMBus::processCallback(){

    fault_rail0 = false;
    fault_rail1 = false;

    if (getFAULTpin(page0) == GPIO_PIN_SET){
        console->printf_error("Error: Fault on rail 0\r\n");
        fault_rail0 = true;
        selectPage(page0);
    } else if (getFAULTpin(page1) == GPIO_PIN_SET){
        console->printf_error("Error: Fault on rail 1\r\n");
        fault_rail1 = true;
        selectPage(page1);
    }

    float out;

    HAL_StatusTypeDef  HAL_status = get(selected_page->status.byte, out);

    if (HAL_status != HAL_OK){
        return HAL_status;
    }

    if ( selected_page->status.byte.value & STATUS_BYTE_NONE_OF_THE_ABOVE){

        //Error is in status word upper bits
        float out;
        HAL_status = get(selected_page->status.word, out);

        if (selected_page->status.word.value & STATUS_WORD_VOUT){
            HAL_status = callbackVOUT();
        } else if (selected_page->status.word.value & STATUS_WORD_IOUT){
            HAL_status = callbackIOUT();
        } else if (selected_page->status.word.value & STATUS_WORD_INPUT){
            HAL_status = callbackINPUT();
        } else if (selected_page->status.word.value & STATUS_WORD_MFR_SPECIFIC){
            HAL_status = callbackMFRSpecific();
        } else if (selected_page->status.word.value & STATUS_WORD_POWER_GOOD){
            HAL_status = callbackPowerGood();
        }
    } else if (selected_page->status.byte.value & STATUS_BYTE_BUSY){
        console->printf_error("Error: Addressed module is busy\r\n");
    } else if (selected_page->status.byte.value & STATUS_BYTE_OFF){
        console->printf_error("Error: Addressed module is not providing any power\r\n");
    } else if (selected_page->status.byte.value & STATUS_BYTE_VOUT_OV){
        console->printf_error("Error: Voltage output is over the maximum value\r\n");
        HAL_status = callbackVOUT();
    } else if (selected_page->status.byte.value & STATUS_BYTE_IOUT_OC){
        console->printf_error("Error: Current output is over the maximum value\r\n");
        HAL_status = callbackIOUT();
    } else if (selected_page->status.byte.value & STATUS_BYTE_TEMPERATURE){
        console->printf_error("Error: Temperature fault or warning has occurred\r\n");
        HAL_status = callbackTEMP();
    } else if (selected_page->status.byte.value & STATUS_BYTE_CML){
        console->printf_error("Error: A communications, memory or logic fault has occurred\r\n");
        HAL_status = callbackCML();
    } else {
        if (fault_rail0 == false || fault_rail1 == false){
            console->printf_info("Status OK\r\n");
        } else {
            console->printf_error("No known problem\r\n");
        }
    }

    return HAL_status;
}


HAL_StatusTypeDef PMBus::callbackVOUT() {
    HAL_StatusTypeDef HAL_status = HAL_OK;

    float out;

    HAL_status = get(selected_page->status.vout, out);

    uint16_t status_vout = selected_page->status.vout.value;


    if (status_vout & STATUS_VOUT_OV_FAULT) {
        console->printf_error("Error: Overvoltage fault\r\n");
    }
    if (status_vout & STATUS_VOUT_OV_WARNING) {
        console->printf_error("Warning: Overvoltage warning\r\n");
    }
    if (status_vout & STATUS_VOUT_UV_WARNING) {
        console->printf_error("Warning: Undervoltage warning\r\n");
    }
    if (status_vout & STATUS_VOUT_UV_FAULT) {
        console->printf_error("Error: Undervoltage fault\r\n");
    }
    if (status_vout & STATUS_VOUT_MAX_WARNING) {
        console->printf_error("Warning: Max warning\r\n");
    }
    if (status_vout & STATUS_VOUT_TON_MAX_FAULT) {
        console->printf_error("Error: Maximum turning on time exceeded\r\n");
    }
    if (status_vout & STATUS_VOUT_TOFF_MAX_WARNING) {
        console->printf_error("Warning: Maximum turning off time exceeded\r\n");
    }

    HAL_status = set(selected_page->status.vout, out); //rewrite to clear

    return HAL_status;

}



HAL_StatusTypeDef PMBus::callbackIOUT() {

    HAL_StatusTypeDef HAL_status = HAL_OK;

    float out;

    HAL_status = get(selected_page->status.iout, out);

    uint16_t status_iout = selected_page->status.iout.value;


    if (status_iout & STATUS_IOUT_OC_FAULT) {
        console->printf_error("Error: Overcurrent fault\r\n");
    }
    if (status_iout & STATUS_IOUT_OC_WARNING) {
        console->printf_error("Warning: Overcurrent warning\r\n");
    }

    HAL_status = set(selected_page->status.iout, out);

    return HAL_status;
}



HAL_StatusTypeDef PMBus::callbackTEMP() {

    HAL_StatusTypeDef HAL_status = HAL_OK;

    float out;

    HAL_status = get(selected_page->status.temp, out);

    uint16_t status_temp = selected_page->status.temp.value;

    if (status_temp & STATUS_TEMP_OT_FAULT) {
        console->printf_error("Error: Overtemperature fault\r\n");
    }
    if (status_temp & STATUS_TEMP_OT_WARNING) {
        console->printf_error("Warning: Overtemperature warning\r\n");
    }
    if (status_temp & STATUS_TEMP_UT_FAULT) {
        console->printf_error("Error: Undertemperature fault\r\n");
    }

    HAL_status = set(selected_page->status.temp, out);


    return HAL_status;

}



HAL_StatusTypeDef PMBus::callbackINPUT() {

    HAL_StatusTypeDef HAL_status = HAL_OK;

    float out;

    HAL_status = get(status.input, out);

    if (status.input.value & STATUS_INPUT_VIN_OV_FAULT) {
        console->printf_error("Error: Input overvoltage fault\r\n");
    }
    if (status.input.value & STATUS_INPUT_VIN_UV_WARNING) {
        console->printf_error("Warning: Input undervoltage warning\r\n");
    }
    if (status.input.value & STATUS_INPUT_UNIT_OFF_FOR_VIN) {
        console->printf_error("Error: Unit off for insifficient input voltage\r\n");
    }
    if (status.input.value & STATUS_INPUT_IIN_OC_WARNING) {
        console->printf_error("Warning: Input overcurrent warning\r\n");
    }
    HAL_status = set(status.input, out);

    return HAL_status;

}



HAL_StatusTypeDef PMBus::callbackCML() {

    HAL_StatusTypeDef HAL_status = HAL_OK;
    float out;

    HAL_status = get(status.cml, out);

    if (status.cml.value & STATUS_CML_INVALID_COMMAND) {
        console->printf_error("Error: Invalid command\r\n");
    }
    if (status.cml.value & STATUS_CML_INVALID_DATA) {
        console->printf_error("Error: Invalid data\r\n");
    }
    if (status.cml.value & STATUS_CML_PEC_ERROR) {
        console->printf_error("Error: PEC error\r\n");
    }
    if (status.cml.value & STATUS_CML_MEMORY_FAULT) {
        console->printf_error("Error: Memory fault\r\n");
    }
    if (status.cml.value & STATUS_CML_PROCESSOR_FAULT) {
        console->printf_error("Error: Processor fault\r\n");
    }
    if (status.cml.value & STATUS_CML_OTHER_COMM_FAULT) {
        console->printf_error("Error: Other communication fault\r\n");
    }
    if (status.cml.value & STATUS_CML_OTHER_MEMORY_LOGIC) {
        console->printf_error("Error: Other memory/logic fault\r\n");
    }
    HAL_status = set(status.cml, out);

    return HAL_status;


}

HAL_StatusTypeDef PMBus::callbackMFRSpecific() {

    HAL_StatusTypeDef HAL_status = HAL_OK;
    float out;

    HAL_status = get(selected_page->status.mfr_specific, out);

    uint16_t status_mfr = selected_page->status.mfr_specific.value;

    if (status_mfr & STATUS_MFR_INTERNAL_TEMP_FAULT) {
        console->printf("Internal temperature fault limit exceeded\n");
    }
    if (status_mfr & STATUS_MFR_INTERNAL_TEMP_WARN) {
        console->printf("Internal temperature warning limit exceeded\n");
    }
    if (status_mfr & STATUS_MFR_EEPROM_CRC_ERROR) {
        console->printf("Factory Trim Area EEPROM CRC Fault\n");
    }
    if (status_mfr & STATUS_MFR_PLL_UNLOCKED) {
        console->printf("PLL unlocked\n");
    }
    if (status_mfr & STATUS_MFR_FAULT_LOG_PRESENT) {
        console->printf("Fault log present\n");
    }
    if (status_mfr & STATUS_MFR_VDD33_UV_OV_FAULT) {
        console->printf("VDD33 UV/OV fault\n");
    }
    if (status_mfr & STATUS_MFR_EXTERNAL_FAULT) {
        console->printf("Fault pin asserted externally\n");
    }

   HAL_status = set(selected_page->status.mfr_specific, out);

    return HAL_status;

}

HAL_StatusTypeDef PMBus::callbackPowerGood() {
    console->printf_info("Power good low\r\n");
    HAL_StatusTypeDef  HAL_status = HAL_OK; //TODO finish
    return HAL_status;
}


