################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Debugging/Src/Console.cpp \
../System/Debugging/Src/Monitor.cpp \
../System/Debugging/Src/Terminal.cpp 

OBJS += \
./System/Debugging/Src/Console.o \
./System/Debugging/Src/Monitor.o \
./System/Debugging/Src/Terminal.o 

CPP_DEPS += \
./System/Debugging/Src/Console.d \
./System/Debugging/Src/Monitor.d \
./System/Debugging/Src/Terminal.d 


# Each subdirectory must supply rules for building sources it contributes
System/Debugging/Src/%.o System/Debugging/Src/%.su System/Debugging/Src/%.cyclo: ../System/Debugging/Src/%.cpp System/Debugging/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G483xx -c -I../Core/Inc -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Power_SW/Geode_FW/System/Core/Inc" -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Power_SW/Geode_FW/System/Debugging/Inc" -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Power_SW/Geode_FW/System/Threads/Inc" -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Power_SW/Geode_FW/System/Utils/Inc" -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System-2f-Debugging-2f-Src

clean-System-2f-Debugging-2f-Src:
	-$(RM) ./System/Debugging/Src/Console.cyclo ./System/Debugging/Src/Console.d ./System/Debugging/Src/Console.o ./System/Debugging/Src/Console.su ./System/Debugging/Src/Monitor.cyclo ./System/Debugging/Src/Monitor.d ./System/Debugging/Src/Monitor.o ./System/Debugging/Src/Monitor.su ./System/Debugging/Src/Terminal.cyclo ./System/Debugging/Src/Terminal.d ./System/Debugging/Src/Terminal.o ./System/Debugging/Src/Terminal.su

.PHONY: clean-System-2f-Debugging-2f-Src

