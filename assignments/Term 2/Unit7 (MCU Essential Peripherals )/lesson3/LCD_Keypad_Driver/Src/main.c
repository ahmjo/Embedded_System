#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"

//Macros
#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x4C
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10

//INITs
void clock_init()
{
	//Enable clock GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clock GPIOB
	RCC_GPIOB_CLK_EN();
}

void GPIO_init()
{
	GPIO_PinConfig_t PinCfg;

	PinCfg.GPIO_PinNumber = GPIO_PIN_9;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_10;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_11;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_12;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PA13 input HighZ
	PinCfg.GPIO_PinNumber = GPIO_PIN_14;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	//PB13 output PP
	PinCfg.GPIO_PinNumber = GPIO_PIN_15;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);
}
void Wait(uint32_t time)
{
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

//main
int main(void)
{
	clock_init();
	LCD_INIT();
	GPIO_init();
	Keypad_init();

	unsigned char key_pressed;
	LCD_WRITE_STRING("HEY There");
	Wait(30);
	LCD_clear_screen();

	unsigned char LCD_DISPLAY [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	unsigned char DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
	for (unsigned char i = 0; i < 11; i++)
	{
		LCD_WRITE_CHAR(LCD_DISPLAY[i]);
		MCAL_GPIO_WritePort(GPIOB, DISPLAY[i] << 9);
		Wait(100);
	}
	LCD_clear_screen();

	LCD_WRITE_STRING("Keypad is ready");
	Wait(30);
	LCD_clear_screen();

	while (1)
	{
		key_pressed = Keypad_getkey();
		switch (key_pressed) {
		case 'A':
			break;
		case '?':
			LCD_clear_screen();
			break;
		default:
			LCD_WRITE_CHAR(key_pressed);
			break;
		}
	}
}

