################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_Drivers/I2C_Slave_EEPROM.c \
../STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c \
../STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.c \
../STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.c \
../STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.c \
../STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.c \
../STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c 

OBJS += \
./STM32_F103C6_Drivers/I2C_Slave_EEPROM.o \
./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o \
./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.o \
./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.o \
./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.o \
./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.o \
./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./STM32_F103C6_Drivers/I2C_Slave_EEPROM.d \
./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d \
./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.d \
./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.d \
./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.d \
./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.d \
./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_Drivers/%.o STM32_F103C6_Drivers/%.su STM32_F103C6_Drivers/%.cyclo: ../STM32_F103C6_Drivers/%.c STM32_F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 -g "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"F:/courses/embedded system diplom/content/Term 2/Unit8 (MCU Interfacing)/07 lec7/I2C_Driver_STM32/I2C_Driver_STM32/STM32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32_F103C6_Drivers

clean-STM32_F103C6_Drivers:
	-$(RM) ./STM32_F103C6_Drivers/I2C_Slave_EEPROM.cyclo ./STM32_F103C6_Drivers/I2C_Slave_EEPROM.d ./STM32_F103C6_Drivers/I2C_Slave_EEPROM.o ./STM32_F103C6_Drivers/I2C_Slave_EEPROM.su ./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.su ./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_I2C_driver.su ./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_RCC_driver.su ./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_SPI_driver.su ./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_USART_driver.su ./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.cyclo ./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d ./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o ./STM32_F103C6_Drivers/Stm32_F103C6_gpio_driver.su

.PHONY: clean-STM32_F103C6_Drivers

