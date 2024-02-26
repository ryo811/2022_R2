################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/can.c \
../Core/Src/can_com.c \
../Core/Src/control.c \
../Core/Src/control_main.c \
../Core/Src/controller.c \
../Core/Src/encoder.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/pid.c \
../Core/Src/servo.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f7xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/can.o \
./Core/Src/can_com.o \
./Core/Src/control.o \
./Core/Src/control_main.o \
./Core/Src/controller.o \
./Core/Src/encoder.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/pid.o \
./Core/Src/servo.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/can.d \
./Core/Src/can_com.d \
./Core/Src/control.d \
./Core/Src/control_main.d \
./Core/Src/controller.d \
./Core/Src/encoder.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/pid.d \
./Core/Src/servo.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f7xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:/Users/ryo/Desktop/robocon/program/ABU2022_R2_MAIN/Core/Inc" -I"C:/Users/ryo/Desktop/robocon/program/ABU2022_R2_MAIN/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/ryo/Desktop/robocon/program/ABU2022_R2_MAIN/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/ryo/Desktop/robocon/program/ABU2022_R2_MAIN/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/ryo/Desktop/robocon/program/ABU2022_R2_MAIN/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


