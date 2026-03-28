################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../System/Threads/Src/TestTask.cpp \
../System/Threads/Src/Thread.cpp \
../System/Threads/Src/Watchdog_thread.cpp 

OBJS += \
./System/Threads/Src/TestTask.o \
./System/Threads/Src/Thread.o \
./System/Threads/Src/Watchdog_thread.o 

CPP_DEPS += \
./System/Threads/Src/TestTask.d \
./System/Threads/Src/Thread.d \
./System/Threads/Src/Watchdog_thread.d 


# Each subdirectory must supply rules for building sources it contributes
System/Threads/Src/%.o System/Threads/Src/%.su System/Threads/Src/%.cyclo: ../System/Threads/Src/%.cpp System/Threads/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G483xx -c -I../Core/Inc -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Cloned/Power_SW/Geode_FW/System/Core/Inc" -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Cloned/Power_SW/Geode_FW/System/Threads/Inc" -I"C:/Users/Ennouri/local disc D/Etudes Hsan (Fianal project Final,Final)/EPFL/Master/Xplore_MAKE/Cloned/Power_SW/Geode_FW/System/Utils/Inc" -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System-2f-Threads-2f-Src

clean-System-2f-Threads-2f-Src:
	-$(RM) ./System/Threads/Src/TestTask.cyclo ./System/Threads/Src/TestTask.d ./System/Threads/Src/TestTask.o ./System/Threads/Src/TestTask.su ./System/Threads/Src/Thread.cyclo ./System/Threads/Src/Thread.d ./System/Threads/Src/Thread.o ./System/Threads/Src/Thread.su ./System/Threads/Src/Watchdog_thread.cyclo ./System/Threads/Src/Watchdog_thread.d ./System/Threads/Src/Watchdog_thread.o ./System/Threads/Src/Watchdog_thread.su

.PHONY: clean-System-2f-Threads-2f-Src

