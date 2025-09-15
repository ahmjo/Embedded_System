#include <stdint.h>
#include "stm32f103x6.h"
#include "Stm32_F103C6_USART_driver.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "Stm32_F103C6_RCC_driver.h"
#include "Stm32_F103C6_I2C_driver.h"
#include "I2C_Slave_EEPROM.h"


void simple_delay(volatile uint32_t count)
{
    while(count--);
}

int main(void)
{
	//enable Clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_GPIOC_CLK_EN();

	//test case1
	unsigned char ch1[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	unsigned char ch2[7] = {0};

	eeprom_init();
	eeprom_write_Nbytes(0xAF, ch1, 7);
	eeprom_read_byte(0xAF, ch2, 7);

    simple_delay(100000);

	//test case2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;
	eeprom_write_Nbytes(0xFFF, ch1, 4);
	eeprom_read_byte(0xFFF, ch2, 4);



	//loop forever
    while(1)
    {

    }
}
