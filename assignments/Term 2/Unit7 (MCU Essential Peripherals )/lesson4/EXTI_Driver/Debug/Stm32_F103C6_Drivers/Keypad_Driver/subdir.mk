################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Keypad_Driver/keypad.c 

OBJS += \
./Stm32_F103C6_Drivers/Keypad_Driver/keypad.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Keypad_Driver/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/Keypad_Driver/%.o Stm32_F103C6_Drivers/Keypad_Driver/%.su Stm32_F103C6_Drivers/Keypad_Driver/%.cyclo: ../Stm32_F103C6_Drivers/Keypad_Driver/%.c Stm32_F103C6_Drivers/Keypad_Driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/Inc" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/Keypad_Driver" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/LCD_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-Keypad_Driver

clean-Stm32_F103C6_Drivers-2f-Keypad_Driver:
	-$(RM) ./Stm32_F103C6_Drivers/Keypad_Driver/keypad.cyclo ./Stm32_F103C6_Drivers/Keypad_Driver/keypad.d ./Stm32_F103C6_Drivers/Keypad_Driver/keypad.o ./Stm32_F103C6_Drivers/Keypad_Driver/keypad.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-Keypad_Driver

