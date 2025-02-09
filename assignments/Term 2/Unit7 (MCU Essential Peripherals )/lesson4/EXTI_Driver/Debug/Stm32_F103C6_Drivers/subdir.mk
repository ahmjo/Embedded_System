################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/%.o Stm32_F103C6_Drivers/%.su Stm32_F103C6_Drivers/%.cyclo: ../Stm32_F103C6_Drivers/%.c Stm32_F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/Inc" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/Keypad_Driver" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/04 lec4/LAB/EXTI_Driver/Stm32_F103C6_Drivers/LCD_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers

clean-Stm32_F103C6_Drivers:
	-$(RM) ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.cyclo ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o ./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.su ./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.cyclo ./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d ./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o ./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.su

.PHONY: clean-Stm32_F103C6_Drivers

