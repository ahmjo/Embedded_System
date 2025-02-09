//Includes
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "lcd.h"
#include "keypad.h"


unsigned int IRQ_Flag = 0;

void Wait(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void EXTI9_CallBack(void)
{
	IRQ_Flag = 1;
	LCD_WRITE_CHAR("I");
	Wait(1000);
}

//INITs
void clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
}

void EXTI_init()
{
	EXTI_Config_t EXTI_CFG;
	EXTI_CFG.EXTI_PIN = EXTI9PB9;
	EXTI_CFG.Trigger_Case = EXTI_Trigger_Rising;
	EXTI_CFG.P_IRQ_CallBack = EXTI9_CallBack;
	EXTI_CFG.IRQ_EN =EXTI_IRQ_EN;
	MCAL_EXTI_GPIO_Init(&EXTI_CFG);
}

void GPIO_init()
{
	//GPIO_PinConfig_t PinCfg;
}


//main
int main(void)
{
	//Enable Clock
	clock_init();

	LCD_INIT();
	LCD_clear_screen();

	EXTI_init();

	//GPIO_init();
	//Keypad_init();

	IRQ_Flag = 1;
	while(1)
	{
		if(IRQ_Flag)
		{
			LCD_clear_screen();
			IRQ_Flag = 0;
		}
	}
}

