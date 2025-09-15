################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_Drivers/Keypad_Driver/keypad.c 

OBJS += \
./STM32_F103C6_Drivers/Keypad_Driver/keypad.o 

C_DEPS += \
./STM32_F103C6_Drivers/Keypad_Driver/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_Drivers/Keypad_Driver/%.o STM32_F103C6_Drivers/Keypad_Driver/%.su STM32_F103C6_Drivers/Keypad_Driver/%.cyclo: ../STM32_F103C6_Drivers/Keypad_Driver/%.c STM32_F103C6_Drivers/Keypad_Driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit8 (MCU Interfacing)/07 lec7/I2C_Driver_STM32/I2C_Driver_STM32/STM32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32_F103C6_Drivers-2f-Keypad_Driver

clean-STM32_F103C6_Drivers-2f-Keypad_Driver:
	-$(RM) ./STM32_F103C6_Drivers/Keypad_Driver/keypad.cyclo ./STM32_F103C6_Drivers/Keypad_Driver/keypad.d ./STM32_F103C6_Drivers/Keypad_Driver/keypad.o ./STM32_F103C6_Drivers/Keypad_Driver/keypad.su

.PHONY: clean-STM32_F103C6_Drivers-2f-Keypad_Driver

