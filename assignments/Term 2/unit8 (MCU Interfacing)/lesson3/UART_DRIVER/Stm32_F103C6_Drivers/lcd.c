#include "lcd.h"

void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}


// Initialize GPIO for LCD
void LCD_GPIO_init() {
	GPIO_Config_t PinCfg;

    // Configure RS, RW, and EN as output
    PinCfg.GPIO_PinNumber = RS_SWITCH;
    PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
    PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_PinNumber = RW_SWITCH;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    PinCfg.GPIO_PinNumber = EN_SWITCH;
    MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

    // Configure data pins (D0 - D7) as output
    for (uint8_t pin = GPIO_PIN_0; pin <= GPIO_PIN_7; pin++) {
        PinCfg.GPIO_PinNumber = pin;
        MCAL_GPIO_Init(LCD_CTRL, &PinCfg);
    }

    // Set initial state: Disable all control signals
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
}


void LCD_lcd_kick() {
	MCAL_GPIO_WRITE_Pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
    delay_ms(2);
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
}


// Initialize LCD in 8-bit mode
void LCD_INIT() {
    delay_ms(20);
    LCD_GPIO_init();
    delay_ms(15);

    LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
    LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
    LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
    LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}


// Clear LCD screen
void LCD_clear_screen() {
    LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}


// Send a command to LCD
void LCD_WRITE_COMMAND(unsigned char command) {
    MCAL_GPIO_WRITE_Port(LCD_CTRL, command);
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
    MCAL_GPIO_WRITE_Pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
    LCD_lcd_kick();
}


// Write a single character to LCD
void LCD_WRITE_CHAR(unsigned char character) {
	MCAL_GPIO_WRITE_Port(LCD_CTRL, character);
	MCAL_GPIO_WRITE_Pin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WRITE_Pin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
    LCD_lcd_kick();
}


// Write a string to LCD
void LCD_WRITE_STRING(char* string) {
    while (*string) {
        LCD_WRITE_CHAR(*string++);
    }
}


// Move cursor to specified position
void LCD_GOTO_XY(unsigned char line, unsigned char position) {
    if (line == 1) {
        LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
    } else if (line == 2) {
        LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
    }
}
