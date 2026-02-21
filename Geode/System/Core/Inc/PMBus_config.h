/*
 * PMBus_config.h
 *
 *  Created on: April 12, 2025
 *      Author: Pedro Conde
 */

#ifndef INC_EXTRA_REG_H_
#define INC_EXTRA_REG_H_


//----------------------------CHOOSE CONFIGURATION--------------------------------

//There are extra non supported commands that are in the PMBus standard, but are not used by the LTC3889
/* ----------- PMBUS command codes definition -------- */
#define PMBC_PAGE                       ((uint8_t)0x00)
#define PMBC_OPERATION                  ((uint8_t)0x01)
#define PMBC_ON_OFF_CONFIG              ((uint8_t)0x02)
#define PMBC_CLEAR_FAULTS               ((uint8_t)0x03)
#define PMBC_PHASE                      ((uint8_t)0x04)
#define PMBC_PAGE_PLUS_WRITE            ((uint8_t)0x05)
#define PMBC_PAGE_PLUS_READ             ((uint8_t)0x06)
#define PMBC_ZONE_CONFIG                ((uint8_t)0x07)
#define PMBC_ZONE_ACTIVE                ((uint8_t)0x08)
#define PMBC_WRITE_PROTECT              ((uint8_t)0x10)
#define PMBC_STORE_DEFAULT_ALL          ((uint8_t)0x11)
#define PMBC_RESTORE_DEFAULT_ALL        ((uint8_t)0x12)
#define PMBC_STORE_DEFAULT_CODE         ((uint8_t)0x13)
#define PMBC_RESTORE_DEFAULT_CODE       ((uint8_t)0x14)
#define PMBC_STORE_USER_ALL             ((uint8_t)0x15)
#define PMBC_RESTORE_USER_ALL           ((uint8_t)0x16)
#define PMBC_STORE_USER_CODE            ((uint8_t)0x17)
#define PMBC_RESTORE_USER_CODE          ((uint8_t)0x18)
#define PMBC_CAPABILITY                 ((uint8_t)0x19)
#define PMBC_QUERY                      ((uint8_t)0x1A)
#define PMBC_SMBALERT_MASK              ((uint8_t)0x1B)
#define PMBC_VOUT_MODE                  ((uint8_t)0x20)
#define PMBC_VOUT_COMMAND               ((uint8_t)0x21)
#define PMBC_VOUT_TRIM                  ((uint8_t)0x22)
#define PMBC_VOUT_CAL_OFFSET            ((uint8_t)0x23)
#define PMBC_VOUT_MAX                   ((uint8_t)0x24)
#define PMBC_VOUT_MARGIN_HIGH           ((uint8_t)0x25)
#define PMBC_VOUT_MARGIN_LOW            ((uint8_t)0x26)
#define PMBC_VOUT_TRANSITION_RATE       ((uint8_t)0x27)
#define PMBC_VOUT_DROOP                 ((uint8_t)0x28)
#define PMBC_VOUT_SCALE_LOOP            ((uint8_t)0x29)
#define PMBC_VOUT_SCALE_MONITOR         ((uint8_t)0x2A)
#define PMBC_VOUT_MIN                   ((uint8_t)0x2B)
#define PMBC_COEFICIENTS                ((uint8_t)0x30)
#define PMBC_POUT_MAX                   ((uint8_t)0x31)
#define PMBC_MAX_DUTY                   ((uint8_t)0x32)
#define PMBC_FREQUENCY_SWITCH           ((uint8_t)0x33)
#define PMBC_POWER_MODE                 ((uint8_t)0x34)
#define PMBC_VIN_ON                     ((uint8_t)0x35)
#define PMBC_VIN_OFF                    ((uint8_t)0x36)
#define PMBC_INTERLEAVE                 ((uint8_t)0x37)
#define PMBC_IOUT_CAL_GAIN              ((uint8_t)0x38)
#define PMBC_IOUT_CAL_OFFSET            ((uint8_t)0x39)
#define PMBC_FAN_CONFIG_1_2             ((uint8_t)0x3A)
#define PMBC_FAN_COMMAND_1              ((uint8_t)0x3B)
#define PMBC_FAN_COMMAND_2              ((uint8_t)0x3C)
#define PMBC_FAN_CONFIG_3_4             ((uint8_t)0x3D)
#define PMBC_FAN_COMMAND_3              ((uint8_t)0x3E)
#define PMBC_FAN_COMMAND_4              ((uint8_t)0x3F)
#define PMBC_VOUT_OV_FAULT_LIMIT        ((uint8_t)0x40)
#define PMBC_VOUT_OV_FAULT_RESPONSE     ((uint8_t)0x41)
#define PMBC_VOUT_OV_WARN_LIMIT         ((uint8_t)0x42)
#define PMBC_VOUT_UV_WARN_LIMIT         ((uint8_t)0x43)
#define PMBC_VOUT_UV_FAULT_LIMIT        ((uint8_t)0x44)
#define PMBC_VOUT_UV_FAULT_RESPONSE     ((uint8_t)0x45)
#define PMBC_IOUT_OC_FAULT_LIMIT        ((uint8_t)0x46)
#define PMBC_IOUT_OC_FAULT_RESPONSE     ((uint8_t)0x47)
#define PMBC_IOUT_OC_LV_FAULT_LIMIT     ((uint8_t)0x48)
#define PMBC_IOUT_OC_LV_FAULT_RESPONSE  ((uint8_t)0x49)
#define PMBC_IOUT_OC_WARN_LIMIT         ((uint8_t)0x4A)
#define PMBC_IOUT_UC_FAULT_LIMIT        ((uint8_t)0x4B)
#define PMBC_IOUT_UC_FAULT_RESPONSE     ((uint8_t)0x4C)
#define PMBC_OT_FAULT_LIMIT             ((uint8_t)0x4F)
#define PMBC_OT_FAULT_RESPONSE          ((uint8_t)0x50)
#define PMBC_OT_WARN_LIMIT              ((uint8_t)0x51)
#define PMBC_UT_FAULT_LIMIT             ((uint8_t)0x53)
#define PMBC_UT_FAULT_RESPONSE          ((uint8_t)0x54)
#define PMBC_VIN_OV_FAULT_LIMIT         ((uint8_t)0x55)
#define PMBC_VIN_OV_FAULT_RESPONSE      ((uint8_t)0x56)
#define PMBC_VIN_UV_WARN_LIMIT          ((uint8_t)0x58)
#define PMBC_VIN_UV_FAULT_LIMIT         ((uint8_t)0x59)
#define PMBC_VIN_UV_FAULT_RESPONSE      ((uint8_t)0x5A)
#define PMBC_IIN_OC_FAULT_LIMIT         ((uint8_t)0x5B)
#define PMBC_IIN_OC_FAULT_RESPONSE      ((uint8_t)0x5C)
#define PMBC_IIN_OC_WARN_LIMIT          ((uint8_t)0x5D)
#define PMBC_POWER_GOOD_ON              ((uint8_t)0x5E)
#define PMBC_POWER_GOOD_OFF             ((uint8_t)0x5F)
#define PMBC_TON_DELAY                  ((uint8_t)0x60)
#define PMBC_TON_RISE                   ((uint8_t)0x61)
#define PMBC_TON_MAX_FAULT_LIMIT        ((uint8_t)0x62)
#define PMBC_TON_MAX_FAULT_RESPONSE     ((uint8_t)0x63)
#define PMBC_TOFF_DELAY                 ((uint8_t)0x64)
#define PMBC_TOFF_FALL                  ((uint8_t)0x65)
#define PMBC_TOFF_MAX_WARN_LIMIT        ((uint8_t)0x66)
#define PMBC_TOFF_MAX_FAULT_RESPONSE    ((uint8_t)0x67)  /* Removed in v1.1*/
#define PMBC_POUT_OP_FAULT_LIMIT        ((uint8_t)0x68)
#define PMBC_POUT_OP_FAULT_RESPONSE     ((uint8_t)0x69)
#define PMBC_POUT_OP_WARN_LIMIT         ((uint8_t)0x6A)
#define PMBC_PIN_OP_WARN_LIMIT          ((uint8_t)0x6B)
#define PMBC_STATUS_BYTE                ((uint8_t)0x78)
#define PMBC_STATUS_WORD                ((uint8_t)0x79)
#define PMBC_STATUS_VOUT                ((uint8_t)0x7A)
#define PMBC_STATUS_IOUT                ((uint8_t)0x7B)
#define PMBC_STATUS_INPUT               ((uint8_t)0x7C)
#define PMBC_STATUS_TEMPERATURE         ((uint8_t)0x7D)
#define PMBC_STATUS_CML                 ((uint8_t)0x7E)
#define PMBC_STATUS_OTHER               ((uint8_t)0x7F)
#define PMBC_STATUS_MFR_SPECIFIC        ((uint8_t)0x80)
#define PMBC_STATUS_FANS_1_2            ((uint8_t)0x81)
#define PMBC_STATUS_FANS_3_4            ((uint8_t)0x82)
#define PMBC_READ_KWH_IN                ((uint8_t)0x83)
#define PMBC_READ_KWH_OUT               ((uint8_t)0x84)
#define PMBC_READ_KWH_CONFIG            ((uint8_t)0x85)
#define PMBC_READ_EIN                   ((uint8_t)0x86)
#define PMBC_READ_EOUT                  ((uint8_t)0x87)
#define PMBC_READ_VIN                   ((uint8_t)0x88)
#define PMBC_READ_IIN                   ((uint8_t)0x89)
#define PMBC_READ_VCAP                  ((uint8_t)0x8A)
#define PMBC_READ_VOUT                  ((uint8_t)0x8B)
#define PMBC_READ_IOUT                  ((uint8_t)0x8C)
#define PMBC_READ_TEMPERATURE_1         ((uint8_t)0x8D)
#define PMBC_READ_TEMPERATURE_2         ((uint8_t)0x8E)
#define PMBC_READ_TEMPERATURE_3         ((uint8_t)0x8F)
#define PMBC_READ_FAN_SPEED_1           ((uint8_t)0x90)
#define PMBC_READ_FAN_SPEED_2           ((uint8_t)0x91)
#define PMBC_READ_FAN_SPEED_3           ((uint8_t)0x92)
#define PMBC_READ_FAN_SPEED_4           ((uint8_t)0x93)
#define PMBC_READ_DUTY_CYCLE            ((uint8_t)0x94)
#define PMBC_READ_FREQUENCY             ((uint8_t)0x95)
#define PMBC_READ_POUT                  ((uint8_t)0x96)
#define PMBC_READ_PIN                   ((uint8_t)0x97)
#define PMBC_PMBUS_REVISION             ((uint8_t)0x98)
#define PMBC_MFR_ID                     ((uint8_t)0x99)
#define PMBC_MFR_MODEL                  ((uint8_t)0x9A)
#define PMBC_MFR_REVISION               ((uint8_t)0x9B)
#define PMBC_MFR_LOCATION               ((uint8_t)0x9C)
#define PMBC_MFR_DATE                   ((uint8_t)0x9D)
#define PMBC_MFR_SERIAL                 ((uint8_t)0x9E)
#define PMBC_APP_PROFILE_SUPPORT        ((uint8_t)0x9F)
#define PMBC_MFR_VIN_MIN                ((uint8_t)0xA0)
#define PMBC_MFR_VIN_MAX                ((uint8_t)0xA1)
#define PMBC_MFR_IIN_MAX                ((uint8_t)0xA2)
#define PMBC_MFR_PIN_MAX                ((uint8_t)0xA3)
#define PMBC_MFR_VOUT_MIN               ((uint8_t)0xA4)
#define PMBC_MFR_VOUT_MAX               ((uint8_t)0xA5)
#define PMBC_MFR_IOUT_MAX               ((uint8_t)0xA6)
#define PMBC_MFR_POUT_MAX               ((uint8_t)0xA7)
#define PMBC_MFR_TAMBIENT_MAX           ((uint8_t)0xA8)
#define PMBC_MFR_TAMBIENT_MIN           ((uint8_t)0xA9)
#define PMBC_MFR_EFFICIENCY_LL          ((uint8_t)0xAA)
#define PMBC_MFR_EFFICIENCY_HL          ((uint8_t)0xAB)
#define PMBC_MFR_PIN_ACCURACY           ((uint8_t)0xAC)
#define PMBC_IC_DEVICE_ID               ((uint8_t)0xAD)
#define PMBC_IC_DEVICE_REV              ((uint8_t)0xAE)
#define PMBC_USER_DATA_00               ((uint8_t)0xB0)
#define PMBC_USER_DATA_01               ((uint8_t)0xB1)
#define PMBC_USER_DATA_02               ((uint8_t)0xB2)
#define PMBC_USER_DATA_03               ((uint8_t)0xB3)
#define PMBC_USER_DATA_04               ((uint8_t)0xB4)
#define PMBC_USER_DATA_05               ((uint8_t)0xB5)
#define PMBC_USER_DATA_06               ((uint8_t)0xB6)
#define PMBC_USER_DATA_07               ((uint8_t)0xB7)
#define PMBC_USER_DATA_08               ((uint8_t)0xB8)
#define PMBC_USER_DATA_09               ((uint8_t)0xB9)
#define PMBC_USER_DATA_10               ((uint8_t)0xBA)
#define PMBC_USER_DATA_11               ((uint8_t)0xBB)
#define PMBC_USER_DATA_12               ((uint8_t)0xBC)
#define PMBC_USER_DATA_13               ((uint8_t)0xBD)
#define PMBC_USER_DATA_14               ((uint8_t)0xBE)
#define PMBC_USER_DATA_15               ((uint8_t)0xBF)
#define PMBC_MFR_MAX_TEMP_1             ((uint8_t)0xC0)
#define PMBC_MFR_MAX_TEMP_2             ((uint8_t)0xC1)
#define PMBC_MFR_MAX_TEMP_3             ((uint8_t)0xC2)
/* MFR_SPECIFIC from v1.3.1 on */
#define PMBC_MFR_SPECIFIC_C4            ((uint8_t)0xC4)
#define PMBC_MFR_SPECIFIC_C5            ((uint8_t)0xC5)
#define PMBC_MFR_SPECIFIC_C6            ((uint8_t)0xC6)
#define PMBC_MFR_SPECIFIC_C7            ((uint8_t)0xC7)
#define PMBC_MFR_SPECIFIC_C8            ((uint8_t)0xC8)
#define PMBC_MFR_SPECIFIC_C9            ((uint8_t)0xC9)
#define PMBC_MFR_SPECIFIC_CA            ((uint8_t)0xCA)
#define PMBC_MFR_SPECIFIC_CB            ((uint8_t)0xCB)
#define PMBC_MFR_SPECIFIC_CC            ((uint8_t)0xCC)
#define PMBC_MFR_SPECIFIC_CD            ((uint8_t)0xCD)
#define PMBC_MFR_SPECIFIC_CE            ((uint8_t)0xCE)
#define PMBC_MFR_SPECIFIC_CF            ((uint8_t)0xCF)
#define PMBC_MFR_SPECIFIC_D0            ((uint8_t)0xD0)
#define PMBC_MFR_SPECIFIC_D1            ((uint8_t)0xD1)
#define PMBC_MFR_SPECIFIC_D2            ((uint8_t)0xD2)
#define PMBC_MFR_SPECIFIC_D3            ((uint8_t)0xD3)
#define PMBC_MFR_SPECIFIC_D4            ((uint8_t)0xD4)
#define PMBC_MFR_SPECIFIC_D5            ((uint8_t)0xD5)
#define PMBC_MFR_SPECIFIC_D6            ((uint8_t)0xD6)
#define PMBC_MFR_SPECIFIC_D7            ((uint8_t)0xD7)
#define PMBC_MFR_SPECIFIC_D8            ((uint8_t)0xD8)
#define PMBC_MFR_SPECIFIC_D9            ((uint8_t)0xD9)
#define PMBC_MFR_SPECIFIC_DA            ((uint8_t)0xDA)
#define PMBC_MFR_SPECIFIC_DB            ((uint8_t)0xDB)
#define PMBC_MFR_SPECIFIC_DC            ((uint8_t)0xDC)
#define PMBC_MFR_SPECIFIC_DD            ((uint8_t)0xDD)
#define PMBC_MFR_SPECIFIC_DE            ((uint8_t)0xDE)
#define PMBC_MFR_SPECIFIC_DF            ((uint8_t)0xDF)
#define PMBC_MFR_SPECIFIC_E0            ((uint8_t)0xE0)
#define PMBC_MFR_SPECIFIC_E1            ((uint8_t)0xE1)
#define PMBC_MFR_SPECIFIC_E2            ((uint8_t)0xE2)
#define PMBC_MFR_SPECIFIC_E3            ((uint8_t)0xE3)
#define PMBC_MFR_SPECIFIC_E4            ((uint8_t)0xE4)
#define PMBC_MFR_SPECIFIC_E5            ((uint8_t)0xE5)
#define PMBC_MFR_SPECIFIC_E6            ((uint8_t)0xE6)
#define PMBC_MFR_SPECIFIC_E7            ((uint8_t)0xE7)
#define PMBC_MFR_SPECIFIC_E8            ((uint8_t)0xE8)
#define PMBC_MFR_SPECIFIC_E9            ((uint8_t)0xE9)
#define PMBC_MFR_SPECIFIC_EA            ((uint8_t)0xEA)
#define PMBC_MFR_SPECIFIC_EB            ((uint8_t)0xEB)
#define PMBC_MFR_SPECIFIC_EC            ((uint8_t)0xEC)
#define PMBC_MFR_SPECIFIC_ED            ((uint8_t)0xED)
#define PMBC_MFR_SPECIFIC_EE            ((uint8_t)0xEE)
#define PMBC_MFR_SPECIFIC_EF            ((uint8_t)0xEF)
#define PMBC_MFR_SPECIFIC_F0            ((uint8_t)0xF0)
#define PMBC_MFR_SPECIFIC_F1            ((uint8_t)0xF1)
#define PMBC_MFR_SPECIFIC_F2            ((uint8_t)0xF2)
#define PMBC_MFR_SPECIFIC_F3            ((uint8_t)0xF3)
#define PMBC_MFR_SPECIFIC_F4            ((uint8_t)0xF4)
#define PMBC_MFR_SPECIFIC_F5            ((uint8_t)0xF5)
#define PMBC_MFR_SPECIFIC_F6            ((uint8_t)0xF6)
#define PMBC_MFR_SPECIFIC_F7            ((uint8_t)0xF7)
#define PMBC_MFR_SPECIFIC_F8            ((uint8_t)0xF8)
#define PMBC_MFR_SPECIFIC_F9            ((uint8_t)0xF9)
#define PMBC_MFR_SPECIFIC_FA            ((uint8_t)0xFA)
#define PMBC_MFR_SPECIFIC_FB            ((uint8_t)0xFB)
#define PMBC_MFR_SPECIFIC_FC            ((uint8_t)0xFC)
#define PMBC_MFR_SPECIFIC_FD            ((uint8_t)0xFD)
/* MFR_SPECIFIC up to v1.3 */
#define PMBC_MFR_SPECIFIC_00            ((uint8_t)0xD0)
#define PMBC_MFR_SPECIFIC_01            ((uint8_t)0xD1)
#define PMBC_MFR_SPECIFIC_02            ((uint8_t)0xD2)
#define PMBC_MFR_SPECIFIC_03            ((uint8_t)0xD3)
#define PMBC_MFR_SPECIFIC_04            ((uint8_t)0xD4)
#define PMBC_MFR_SPECIFIC_05            ((uint8_t)0xD5)
#define PMBC_MFR_SPECIFIC_06            ((uint8_t)0xD6)
#define PMBC_MFR_SPECIFIC_07            ((uint8_t)0xD7)
#define PMBC_MFR_SPECIFIC_08            ((uint8_t)0xD8)
#define PMBC_MFR_SPECIFIC_09            ((uint8_t)0xD9)
#define PMBC_MFR_SPECIFIC_10            ((uint8_t)0xDA)
#define PMBC_MFR_SPECIFIC_11            ((uint8_t)0xDB)
#define PMBC_MFR_SPECIFIC_12            ((uint8_t)0xDC)
#define PMBC_MFR_SPECIFIC_13            ((uint8_t)0xDD)
#define PMBC_MFR_SPECIFIC_14            ((uint8_t)0xDE)
#define PMBC_MFR_SPECIFIC_15            ((uint8_t)0xDF)
#define PMBC_MFR_SPECIFIC_16            ((uint8_t)0xE0)
#define PMBC_MFR_SPECIFIC_17            ((uint8_t)0xE1)
#define PMBC_MFR_SPECIFIC_18            ((uint8_t)0xE2)
#define PMBC_MFR_SPECIFIC_19            ((uint8_t)0xE3)
#define PMBC_MFR_SPECIFIC_20            ((uint8_t)0xE4)
#define PMBC_MFR_SPECIFIC_21            ((uint8_t)0xE5)
#define PMBC_MFR_SPECIFIC_22            ((uint8_t)0xE6)
#define PMBC_MFR_SPECIFIC_23            ((uint8_t)0xE7)
#define PMBC_MFR_SPECIFIC_24            ((uint8_t)0xE8)
#define PMBC_MFR_SPECIFIC_25            ((uint8_t)0xE9)
#define PMBC_MFR_SPECIFIC_26            ((uint8_t)0xEA)
#define PMBC_MFR_SPECIFIC_27            ((uint8_t)0xEB)
#define PMBC_MFR_SPECIFIC_28            ((uint8_t)0xEC)
#define PMBC_MFR_SPECIFIC_29            ((uint8_t)0xED)
#define PMBC_MFR_SPECIFIC_30            ((uint8_t)0xEE)
#define PMBC_MFR_SPECIFIC_31            ((uint8_t)0xEF)
#define PMBC_MFR_SPECIFIC_32            ((uint8_t)0xF0)
#define PMBC_MFR_SPECIFIC_33            ((uint8_t)0xF1)
#define PMBC_MFR_SPECIFIC_34            ((uint8_t)0xF2)
#define PMBC_MFR_SPECIFIC_35            ((uint8_t)0xF3)
#define PMBC_MFR_SPECIFIC_36            ((uint8_t)0xF4)
#define PMBC_MFR_SPECIFIC_37            ((uint8_t)0xF5)
#define PMBC_MFR_SPECIFIC_38            ((uint8_t)0xF6)
#define PMBC_MFR_SPECIFIC_39            ((uint8_t)0xF7)
#define PMBC_MFR_SPECIFIC_40            ((uint8_t)0xF8)
#define PMBC_MFR_SPECIFIC_41            ((uint8_t)0xF9)
#define PMBC_MFR_SPECIFIC_42            ((uint8_t)0xFA)
#define PMBC_MFR_SPECIFIC_43            ((uint8_t)0xFB)
#define PMBC_MFR_SPECIFIC_44            ((uint8_t)0xFC)
#define PMBC_MFR_SPECIFIC_45            ((uint8_t)0xFD)
/* End of v1.3 section */
#define PMBC_MFR_SPECIFIC_COMMAND_EXT   ((uint8_t)0xFE)
#define PMBC_PMBUS_COMMAND_EXT          ((uint8_t)0xFF)

/*
 * Note: On top of that there are commands without command code - quick command,
 *       send byte, alert response and receive byte that all need special treatment.
 */


#define MFR_CHAN_CONFIG_LTC3889 	PMBC_MFR_SPECIFIC_D0
#define MFR_CONFIG_ALL_LTC3889 		PMBC_MFR_SPECIFIC_D1
#define MFR_FAULT_PROPAGATE_LTC3889 PMBC_MFR_SPECIFIC_D2
#define MFR_PWM_COMP_LTC3889		PMBC_MFR_SPECIFIC_D3
#define MFR_PWM_MODE_LTC3889 		PMBC_MFR_SPECIFIC_D4
#define MFR_FAULT_RESPONSE_LTC3889 	PMBC_MFR_SPECIFIC_D5
#define MFR_OT_FAULT_RESPONSE 		PMBC_MFR_SPECIFIC_D6
#define MFR_IOUT_PEAK 				PMBC_MFR_SPECIFIC_D7
#define MFR_ADC_CONTROL_LTC3889 	PMBC_MFR_SPECIFIC_D8
#define MFR_RETRY_DELAY_LTC3889 	PMBC_MFR_SPECIFIC_DB
#define MFR_RESTART_DELAY_LTC3889 	PMBC_MFR_SPECIFIC_DC
#define MFR_VOUT_PEAK 				PMBC_MFR_SPECIFIC_DD
#define MFR_VIN_PEAK 				PMBC_MFR_SPECIFIC_DE
#define MFR_TEMPERATURE_1_PEAK 		PMBC_MFR_SPECIFIC_DF
#define MFR_READ_IIN_PEAK 			PMBC_MFR_SPECIFIC_E1
#define MFR_CLEAR_PEAKS 			PMBC_MFR_SPECIFIC_E3
#define MFR_READ_ICHIP 				PMBC_MFR_SPECIFIC_E4
#define MFR_PADS 					PMBC_MFR_SPECIFIC_E5
#define MFR_ADDRESS 				PMBC_MFR_SPECIFIC_E6
#define MFR_SPECIAL_ID 				PMBC_MFR_SPECIFIC_E7
#define MFR_IIN_CAL_GAIN 			PMBC_MFR_SPECIFIC_E8
#define MFR_FAULT_LOG_STORE 		PMBC_MFR_SPECIFIC_E9
#define MFR_FAULT_LOG_CLEAR 		PMBC_MFR_SPECIFIC_EA
#define MFR_FAULT_LOG 				PMBC_MFR_SPECIFIC_EE
#define MFR_COMMON 					PMBC_MFR_SPECIFIC_EF
#define MFR_COMPARE_USER_ALL 		PMBC_MFR_SPECIFIC_F0
#define MFR_TEMPERATURE_2_PEAK 		PMBC_MFR_SPECIFIC_F4
#define MFR_PWM_CONFIG_LTC3889 		PMBC_MFR_SPECIFIC_F5
#define MFR_IOUT_CAL_GAIN_TC 		PMBC_MFR_SPECIFIC_F6
#define MFR_RVIN 					PMBC_MFR_SPECIFIC_F7
#define MFR_TEMP_1_GAIN 			PMBC_MFR_SPECIFIC_F8
#define MFR_TEMP_1_OFFSET 			PMBC_MFR_SPECIFIC_F9
#define MFR_RAIL_ADDRESS 			PMBC_MFR_SPECIFIC_FA
#define MFR_RESET 					PMBC_MFR_SPECIFIC_FD
#define MFR_TEMPERATURE_3_PEAK 		PMBC_MFR_SPECIFIC_FC


//-------------OPERATION-------------------

#define TURN_ON							0x80
#define TURN_OFF						0x00
#define TURN_OFF_SOFT					0x40

// I have named the pmbus as 2 and 3 because they use the lines i2c 2 and 3 but the modules in the kicad are called A and B


//-------------------------------------CONFIGURATION-VALUES-----------------------------------------

//-------------------------------------VIN-----------------------------------------

#define BATTERY_MIN_WARNING_LEVEL 		24.5f //Input supply undervoltage warning limit
#define START_CONVERSION_LEVEL			25.5f //Input voltage at which the unit should start power conversion in above.
#define STOP_CONVERSION_LEVEL			24.0f //Input voltage at which the unit should stop power conversion if below.
#define BATTERY_MAX_WARNING_LEVEL 		29.0f //Input supply overvoltage warning limit
#define BATTERY_MAX_FAULT_LEVEL 		30.0f //Input supply overvoltage fault limit

//-------------------------------------VOUT-----------------------------------------

#define VOUT_MAX_MA0			6.0f //Maximum output voltage module A rail 0
#define VOUT_MAX_MA1			13.0f //Maximum output voltage module A rail 1
#define VOUT_MAX_MB0			16.0f //Maximum output voltage module A rail 0
#define VOUT_MAX_MB1			25.0f //Maximum output voltage module B rail 1

#define VOUT_MA0							5.0f //Output voltage module A rail 0
#define VOUT_MA1							12.0f //Output voltage module A rail 1
#define VOUT_MB0							15.0f //Output voltage module B rail 0
#define VOUT_MB1							24.0f //Output voltage module B rail 1


//--------------------SECURITY-THRESHOLDS-VALUES------------------------------------


//-------------IIN-------------

#define IIN_OC_WARN_LEVEL 		40.0f //Current sense overcurrent warning limit

//-------------VOUT-------------

#define VOUT_OV_WARN_LEVEL_MA0 5.5f
#define VOUT_OV_WARN_LEVEL_MA1 12.5f
#define VOUT_OV_WARN_LEVEL_MB0 15.5f
#define VOUT_OV_WARN_LEVEL_MB1 24.5f

#define VOUT_OV_FAULT_LEVEL_MA0 6.0f
#define VOUT_OV_FAULT_LEVEL_MA1 13.0f
#define VOUT_OV_FAULT_LEVEL_MB0 16.0f
#define VOUT_OV_FAULT_LEVEL_MB1 25.0f

#define VOUT_UV_WARN_LEVEL_MA0 4.5f
#define VOUT_UV_WARN_LEVEL_MA1 11.5f
#define VOUT_UV_WARN_LEVEL_MB0 14.5f
#define VOUT_UV_WARN_LEVEL_MB1 23.5f

#define VOUT_UV_FAULT_LEVEL_MA0 4.0f
#define VOUT_UV_FAULT_LEVEL_MA1 11.0f
#define VOUT_UV_FAULT_LEVEL_MB0 14.0f
#define VOUT_UV_FAULT_LEVEL_MB1 23.0f

//-------------IOUT-------------

#define SHUNT_RESISTOR_INPUT_MOHMS		2.0f //Current sense calibration gain for all rails in all modules in mOhms
#define SHUNT_RESISTOR_OUTPUT_MOHMS		3.0f //Current sense calibration gain for all rails in all modules in mOhms

#define IOUT_OC_WARN_LEVEL			40.0f //Current sense overcurrent warning limit
#define IOUT_OC_FAULT_LEVEL 		50.0f //Current sense overcurrent fault limit

//-------------TEMP-------------

#define OT_WARN_LEVEL 			60.0f //Overtemperature warning limit
#define OT_FAULT_LEVEL 			90.0f //Overtemperature fault limit
#define UT_FAULT_LEVEL 			-40.0f //Undertemperature fault limit

#define TEMP_SENSOR_SLOPE 		1.0f //Temperature sensor slope
#define TEMP_SENSOR_OFFSET 		0.0f //Temperature sensor offset

//-------------TON/TOFF-------------

#define TON_DELAY_LEVEL 				0.0f //ms
#define TON_RISE_LEVEL 					8.0f //ms
#define TON_MAX_FAULT_LEVEL 			10.0f //ms
#define VOUT_RATE_LEVEL 				0.25f //V/ms

#define TOFF_DELAY_LEVEL 				0.0f //ms
#define TOFF_FALL_LEVEL 				8.0f //ms
#define TOFF_MAX_WARN_LEVEL 			150.0f //ms

//-------------FREQUENCY-------------

#define TRASNSISTOR_FREQUENCY 			250.0f //kHz //from datasheet

//-------------MFR-CONFIG-REGS-------------

#define GM_PWM_CHANNEL_ERROR_AMPLIFIER 	0b0110
#define INTERNAL_RESISTORS_ITH 			0b0110


#define MFR_RETRY_DELAY_VALUE 				350.0f //ms
#define MFR_RESTART_DELAY_VALUE 			500.0f //ms
#define MFR_RVIN_VALUE						2.0f //mOhms


//-------------VIN_MASKS-------------

/**
 * Strictest option from datasheet.
 * Shuts down rail if voltage is above the limit and tries to restart every x time it if it is below the limit.
 * Limit set by MFR_RETRY_DELAY register.
 */

//Currently applied to rail 0 and rail 1 of both modules

#define INITIAL_VIN_OV_FAULT			0b10111000

//-------------VOUT_MASKS-------------

/**
 * Strictest option from datasheet.
 * Shuts down rail if voltage is above the limit and tries to restart every x time it if it is below the limit.
 * Limit set by MFR_RETRY_DELAY register.
 */

//Currently applied to rail 0 and rail 1 of both modules

#define INITIAL_VOUT_OV_FAULT			0b10111000
#define INITIAL_VOUT_UV_FAULT			0b10111000

#define MFR_VOUT_MAX_VALUE					40.5f //Manufacturer limit

//-------------IOUT_MASKS-------------

//Currently applied to rail 0 and rail 1 of both modules

#define INITIAL_IOUT_OC_FAULT			0b11111000

//-------------TON/TOFF_MASKS-------------

#define INITIAL_TON_FAULT_RESPONSE		0b10111000

//-------------MFR_CHAN_CONFIG_MASKS-------------

#define MFR_CHAN_CONFIG_DISABLE_RUN_LOW_MASK				(1 << 4) //1: Pulse run pin low when commanded off. 0: Run pin still high when commanded off.
#define MFR_CHAN_CONFIG_SHORT_CYCLE_MASK					(1 << 3) //0: Short cycle disabled, 1: Short cycle enabled. Short cycle: the output will immediate off if commanded ON while waiting for TOFF_DELAY or TOFF_FALL.
#define MFR_CHAN_CONFIG_SHARED_CLK_CONTROL_MASK 			(1 << 2) //0: Shared clock control disabled, 1: Shared clock control enabled.
#define MFR_CHAN_CONFIG_DISABLE_ALERT_PULLING_MASK 			(1 << 1) //0: Alert pulled down if fault pin pulled down externally, 1: Alert NOT pulled down if fault pin pulled down externally.
#define MFR_CHAN_CONFIG_DISABLE_VOUT_DECAY_REQUIREMENT_MASK (1 << 0) //1: Vout decay requirement disabled, 0: Vout decay requirement enabled.

//-------------MFR_CONFIG_ALL_MASKS-------------

#define MFR_CONFIG_ALL_ENABLE_FAULT_LOG_MASK				(1 << 7) //1: Fault log enabled, 0: Fault log disabled.
#define MFR_CONFIG_ALL_IGNORE_RESISTORS_MASK				(1 << 6) //1: Resistors ignored, 0: Resistors not ignored.
#define MFR_CONFIG_ALL_DISABLE_CML_FAULT_QUICK_CMD_MASK		(1 << 5) //1: CML quick command disabled, 0: CML quick command enabled.
#define MFR_CONFIG_ALL_DISABLE_SYNC_OUTPUT_MASK				(1 << 4) //1: Sync output disabled, 0: Sync output enabled.
#define MFR_CONFIG_ALL_ENABLE_255_MS_TIMEOUT_MASK			(1 << 3) //1: 255 ms timeout enabled, 0: 255 ms timeout disabled.
#define MFR_CONFIG_ALL_ENABLE_PEC_MASK						(1 << 2) //1: PEC enabled, 0: PEC disabled.
#define MFR_CONFIG_ALL_CLOCK_STRETCHING_MASK				(1 << 1) //1: Clock stretching enabled, 0: Clock stretching disabled.
#define MFR_CONFIG_ALL_CLEAR_FAULTS_ON_RUN_MASK				(1 << 0) //1: Clear faults on a rising edge on EITHER RUN pin enabled, 0: Clear faults disabled.

//-------------MFR_FAULT_PROPAGATE_MASKS-------------

#define MFR_FAULT_VOUT_MUST_DECAY_MASK						(1 << 15) //1: Vout must decay 12.5% if RUN pin asserted down and then high if MFR_CHAN_CONFIG[0] is set, 0: Vout does not need to decay.
#define MFR_FAULT_SHORT_CYCLING_REACTION_MASK				(1 << 14) //1: Short cycling reaction enabled, 0: Short cycling reaction disabled.
#define MFR_FAULT_TON_MAX_REACTION_MASK						(1 << 13) //1: Ton max reaction enabled, 0: Ton max reaction disabled.
//bit 12 is reserved, must be 0
#define MFR_FAULT_MFR_OT_REACTION_MASK 						(1 << 11) //1: MFR OT reaction enabled, 0: MFR OT reaction disabled.
//bit 10 is reserved, must be 0
//bit 9 is reserved, must be 0
#define MFR_FAULT_UT_REACTION_MASK							(1 << 8) //1: MFR UT fault enabled, 0: MFR UT fault disabled.
#define MFR_FAULT_OT_REACTION_MASK							(1 << 7) //1: MFR OT fault enabled, 0: MFR OT fault disabled.
//bit 6 is reserved
//bit 5 is reserved
#define MFR_FAULT_VIN_OV_REACTION_MASK						(1 << 4) //1: MFR Vin OV fault enabled, 0: MFR Vin OV fault disabled.
//bit 3 is reserved
#define MFR_FAULT_IOUT_OC_REACTION_MASK						(1 << 2) //1: MFR IOUT OC fault enabled, 0: MFR IOUT OC fault disabled.
#define MFR_FAULT_VOUT_UV_REACTION_MASK						(1 << 1) //1: MFR Vout UV fault enabled, 0: MFR Vout UV fault disabled.
#define MFR_FAULT_VOUT_OV_REACTION_MASK						(1 << 0) //1: MFR Vout OV fault enabled, 0: MFR Vout OV fault disabled.

//-------------MFR_PWM_MODE_MASKS-------------

// Bit masks
#define MFR_PWM_MODE_ILIMIT_HIGH_RANGE_MASK     			(1 << 7)  // 0: Low Current, 1: High Current
#define MFR_PWM_MODE_SERVO_ENABLE_MASK     					(1 << 6)  // 1: Enable Digital Servo Mode
#define MFR_PWM_MODE_EXT_TEMP_MASK         					(1 << 5)  // 0: ΔVBE sense, 1: Direct VBE sense
#define MFR_PWM_MODE_VOUT_RANGE_MASK       					(1 << 1)  // 0: 40V max, 1: 8V max
#define MFR_PWM_MODE_MODE_MASK         						(1 << 0)  // 0: Discontinuous, 1: Forced Continuous

// DRVSET values (bits [3:2]) //ASKFEDE
#define MFR_PWM_MODE_DRVSET_6V3_5V3        (0x00)    // 00b: DRVCC = 6.3V, EXTVCC = 5.3V
#define MFR_PWM_MODE_DRVSET_7V4_7V7        (0x04)    // 01b: DRVCC = 7.4V, EXTVCC = 7.7V
#define MFR_PWM_MODE_DRVSET_9V0_7V7        (0x08)    // 10b: DRVCC = 9.0V, EXTVCC = 7.7V
// 11b is reserved on Page 0 and undefined on Page 1

//-------------MFR_PWM_CONFIG_MASKS-------------

#define MFR_PWM_CONFIG_INPUT_ISENSE_GAIN_4X_MASK		0x20
#define MFR_PWM_CONFIG_INPUT_ISENSE_GAIN_8X_MASK		0x40
#define MFR_PWM_CONFIG_INPUT_ISENSE_NOT_SUPP_MASK  		0x60

#ifdef POLYPHASE
#define MFR_PWM_CONFIG_USE_SHARED_FEEDBACK_MASK 		(1 << 7) //1: Use shared feedback, 0: Use separate feedback

#define MFR_PWM_CONFIG_SHARED_CLK_ENABLE_MASK			(1 << 4) //1: Enable shared clock, 0: Disable shared clock
//No info on datasheet about bit 3, looks like it is reserved
#define MFR_PWM_CONFIG_CH0_0_CH1_180_MASK 			    0x00
#define MFR_PWM_CONFIG_CH0_90_CH1_270_MASK			    0x01
#define MFR_PWM_CONFIG_CH0_0_CH1_240_MASK			    0x02
#define MFR_PWM_CONFIG_CH0_0_CH1_120_MASK			    0x03
#define MFR_PWM_CONFIG_CH0_120_CH1_240_MASK			    0x04
#define MFR_PWM_CONFIG_CH0_60_CH1_240_MASK			    0x05
#define MFR_PWM_CONFIG_CH0_120_CH1_300_MASK			    0x06
#endif

//-------------MFR_FAULT_RESPONSE-------------

#define MFR_FAULT_RESPONSE_INHIBIT					0xC0 //Shut down rail if fault pin pulled down externally
#define MFR_FAULT_RESPONSE_IGNORE					0x00 //Ignore and do nothing if fault pin pulled down externally

//-------------MFR_ADC_CONTROL_MASKS-------------

#define MFR_ADC_CONTROL_ROUND_ROBIN					0x00 //Set round robin standard telemetry mode RECOMMENDED
//0x0F, 0x0E, 0x0D are reserved
#define MFR_ADC_CONTROL_ONLY_READ_TEMP1_CH1			0x0C //Only read external temperature rail 1. DEACTIVATES OTHER FAULTS.
//0x0B is reserved
#define MFR_ADC_CONTROL_ONLY_READ_IOUT_CH1			0x0A //Only read current sense rail 1. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_VOUT_CH1			0x09 //Only read voltage sense rail 1. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_TEMP1_CH0			0x08 //Only read external temperature rail 0. DEACTIVATES OTHER FAULTS.
//0x07 is reserved
#define MFR_ADC_CONTROL_ONLY_READ_IOUT_CH0			0x06 //Only read current sense rail 0. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_VOUT_CH0			0x05 //Only read voltage sense rail 0. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_TEMP2				0x04 //Only read internal temperature (which is temp 2). DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_IIN				0x03 //Only read measured input supply current. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_ICHIP				0x02 //Only read chip input current. DEACTIVATES OTHER FAULTS.
#define MFR_ADC_CONTROL_ONLY_READ_VIN				0x01 //Only read measured input supply voltage. DEACTIVATES OTHER FAULTS.


#define STATUS_WORD_VOUT              (1 << 15)
#define STATUS_WORD_IOUT              (1 << 14)
#define STATUS_WORD_INPUT             (1 << 13)
#define STATUS_WORD_MFR_SPECIFIC      (1 << 12)
#define STATUS_WORD_POWER_GOOD        (1 << 11)

#define STATUS_BYTE_BUSY              (1 << 7)
#define STATUS_BYTE_OFF               (1 << 6)
#define STATUS_BYTE_VOUT_OV           (1 << 5)
#define STATUS_BYTE_IOUT_OC           (1 << 4)
#define STATUS_BYTE_TEMPERATURE       (1 << 2)
#define STATUS_BYTE_CML               (1 << 1)
#define STATUS_BYTE_NONE_OF_THE_ABOVE (1 << 0)

#define STATUS_VOUT_OV_FAULT          (1 << 7)
#define STATUS_VOUT_OV_WARNING        (1 << 6)
#define STATUS_VOUT_UV_WARNING        (1 << 5)
#define STATUS_VOUT_UV_FAULT          (1 << 4)
#define STATUS_VOUT_MAX_WARNING       (1 << 3)
#define STATUS_VOUT_TON_MAX_FAULT     (1 << 2)
#define STATUS_VOUT_TOFF_MAX_WARNING  (1 << 1)

#define STATUS_IOUT_OC_FAULT          (1 << 7)
#define STATUS_IOUT_OC_WARNING        (1 << 5)

#define STATUS_TEMP_OT_FAULT          (1 << 7)
#define STATUS_TEMP_OT_WARNING        (1 << 6)
#define STATUS_TEMP_UT_FAULT          (1 << 4)

#define STATUS_CML_INVALID_COMMAND        (1 << 7)
#define STATUS_CML_INVALID_DATA           (1 << 6)
#define STATUS_CML_PEC_ERROR              (1 << 5)
#define STATUS_CML_MEMORY_FAULT           (1 << 4)
#define STATUS_CML_PROCESSOR_FAULT        (1 << 3)
#define STATUS_CML_OTHER_COMM_FAULT       (1 << 1)
#define STATUS_CML_OTHER_MEMORY_LOGIC     (1 << 0)

#define STATUS_INPUT_VIN_OV_FAULT         (1 << 7)
#define STATUS_INPUT_VIN_UV_WARNING       (1 << 5)
#define STATUS_INPUT_UNIT_OFF_FOR_VIN     (1 << 3)
#define STATUS_INPUT_IIN_OC_WARNING       (1 << 1)

#define STATUS_MFR_INTERNAL_TEMP_FAULT    (1 << 7)
#define STATUS_MFR_INTERNAL_TEMP_WARN     (1 << 6)
#define STATUS_MFR_EEPROM_CRC_ERROR       (1 << 5)
#define STATUS_MFR_PLL_UNLOCKED           (1 << 4)
#define STATUS_MFR_FAULT_LOG_PRESENT      (1 << 3)
#define STATUS_MFR_VDD33_UV_OV_FAULT      (1 << 2)
#define STATUS_MFR_EXTERNAL_FAULT         (1 << 0)

#define MFR_COMMON_ALERT_NOT_DRIVING      (1 << 7)
#define MFR_COMMON_CHIP_NOT_BUSY          (1 << 6)
#define MFR_COMMON_CALC_NOT_PENDING       (1 << 5)
#define MFR_COMMON_OUTPUT_NOT_TRANSITION  (1 << 4)
#define MFR_COMMON_EEPROM_INITIALIZED     (1 << 3)
#define MFR_COMMON_SHARE_CLK_LOW          (1 << 1)
#define MFR_COMMON_WP_PIN_HIGH            (1 << 0)

#define MFR_INFO_EEPROM_ECC_STATUS        (1 << 4)

#define MFR_PADS_VDD33_OV_FAULT           (1 << 15)
#define MFR_PADS_VDD33_UV_FAULT           (1 << 14)
#define MFR_PADS_INVALID_ADC_RESULTS      (1 << 11)
#define MFR_PADS_SYNC_BY_EXTERNAL         (1 << 10)
#define MFR_PADS_CH1_POWER_GOOD           (1 << 9)
#define MFR_PADS_CH0_POWER_GOOD           (1 << 8)
#define MFR_PADS_FORCE_RUN1_LOW           (1 << 7)
#define MFR_PADS_FORCE_RUN0_LOW           (1 << 6)
#define MFR_PADS_RUN1_PIN_STATE           (1 << 5)
#define MFR_PADS_RUN0_PIN_STATE           (1 << 4)
#define MFR_PADS_FORCE_FAULT1_LOW         (1 << 3)
#define MFR_PADS_FORCE_FAULT0_LOW         (1 << 2)
#define MFR_PADS_FAULT1_PIN_STATE         (1 << 1)
#define MFR_PADS_FAULT0_PIN_STATE         (1 << 0)



#endif /* INC_EXTRA_REG_H_*/
