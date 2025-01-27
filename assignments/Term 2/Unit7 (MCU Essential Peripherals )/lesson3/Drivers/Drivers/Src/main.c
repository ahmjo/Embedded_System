//Includes
#include "STM32F103X6.h"
#include "STM32F103C6_GPIO_drivers.h"

//INITs
void Clock_Init()
{
	RCC_GPIOA_CLK_EN();//enable clock for GPIOA

	RCC_GPIOB_CLK_EN();//enable clock for GPIOB
}

void Gpio_Init()
{
	GPIO_Config_t pin_config;

	//PA1 Input Highz
	pin_config.GPIO_PinNumber = GPIO_PIN_1;
	pin_config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pin_config);

	//PB1 Output PP
	pin_config.GPIO_PinNumber = GPIO_PIN_1;
	pin_config.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pin_config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOB, &pin_config);

	//PA13 Input Highz
	pin_config.GPIO_PinNumber = GPIO_PIN_13;
	pin_config.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pin_config);

	//PB1 Output PP
	pin_config.GPIO_PinNumber = GPIO_PIN_13;
	pin_config.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	pin_config.GPIO_PinSpeed = GPIO_SPEED_10MHz;
	MCAL_GPIO_Init(GPIOB, &pin_config);
}

void delay_ms_(int x){

	unsigned int i,j;
	for (i=0; i<x;i++)
	{
		for(j=0;j<255;j++);
	}
}

//Main
int main(void)
{
	Clock_Init();
	Gpio_Init();

    while(1)
    {
    	if(MCAL_GPIO_READ_Pin(GPIOA, GPIO_PIN_1) == 0)
    	{
    		MCAL_GPIO_TOGGLE_Pin(GPIOB,GPIO_PIN_1);
    		while(MCAL_GPIO_READ_Pin(GPIOA, GPIO_PIN_1) == 0);
    	}
    	if(MCAL_GPIO_READ_Pin(GPIOA, GPIO_PIN_13) == 1)
    	{
    		MCAL_GPIO_TOGGLE_Pin(GPIOB,GPIO_PIN_13);
    		delay_ms_(20);
    	}
    	delay_ms_(1);
    }
    return 0;
}