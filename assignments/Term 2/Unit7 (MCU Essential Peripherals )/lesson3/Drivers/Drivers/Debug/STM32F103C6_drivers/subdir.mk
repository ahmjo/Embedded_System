################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_drivers/STM32F103C6_GPIO_drivers.c 

OBJS += \
./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.o 

C_DEPS += \
./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_drivers/%.o STM32F103C6_drivers/%.su STM32F103C6_drivers/%.cyclo: ../STM32F103C6_drivers/%.c STM32F103C6_drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/03 lec3/My_Drivers/Drivers/STM32F103C6_drivers" -I"F:/courses/embedded system diplom/content/Term 2/Unit7 (MCU Essential Peripherals )/03 lec3/My_Drivers/Drivers/STM32F103C6_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32F103C6_drivers

clean-STM32F103C6_drivers:
	-$(RM) ./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.cyclo ./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.d ./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.o ./STM32F103C6_drivers/STM32F103C6_GPIO_drivers.su

.PHONY: clean-STM32F103C6_drivers

