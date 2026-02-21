################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SMBus_PMBus_Stack/Target/smbus.c 

C_DEPS += \
./SMBus_PMBus_Stack/Target/smbus.d 

OBJS += \
./SMBus_PMBus_Stack/Target/smbus.o 


# Each subdirectory must supply rules for building sources it contributes
SMBus_PMBus_Stack/Target/%.o SMBus_PMBus_Stack/Target/%.su SMBus_PMBus_Stack/Target/%.cyclo: ../SMBus_PMBus_Stack/Target/%.c SMBus_PMBus_Stack/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G483xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_Device/App -I../USB_Device/Target -I../SMBus_PMBus_Stack/Target -I../Middlewares/ST/STM32_SMBus_Stack/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SMBus_PMBus_Stack-2f-Target

clean-SMBus_PMBus_Stack-2f-Target:
	-$(RM) ./SMBus_PMBus_Stack/Target/smbus.cyclo ./SMBus_PMBus_Stack/Target/smbus.d ./SMBus_PMBus_Stack/Target/smbus.o ./SMBus_PMBus_Stack/Target/smbus.su

.PHONY: clean-SMBus_PMBus_Stack-2f-Target

