################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/LCD_Driver/lcd.c 

OBJS += \
./Stm32_F103C6_Drivers/LCD_Driver/lcd.o 

C_DEPS += \
./Stm32_F103C6_Drivers/LCD_Driver/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/LCD_Driver/%.o Stm32_F103C6_Drivers/LCD_Driver/%.su Stm32_F103C6_Drivers/LCD_Driver/%.cyclo: ../Stm32_F103C6_Drivers/LCD_Driver/%.c Stm32_F103C6_Drivers/LCD_Driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/03 sec3/LAB/LCD_Keypad_Driver/Stm32_F103C6_Drivers/Inc" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/03 sec3/LAB/LCD_Keypad_Driver/Stm32_F103C6_Drivers/Keypad_Driver" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/03 sec3/LAB/LCD_Keypad_Driver/Stm32_F103C6_Drivers/LCD_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-LCD_Driver

clean-Stm32_F103C6_Drivers-2f-LCD_Driver:
	-$(RM) ./Stm32_F103C6_Drivers/LCD_Driver/lcd.cyclo ./Stm32_F103C6_Drivers/LCD_Driver/lcd.d ./Stm32_F103C6_Drivers/LCD_Driver/lcd.o ./Stm32_F103C6_Drivers/LCD_Driver/lcd.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-LCD_Driver

