#include "LCD.h"

void LCD_clear_screen() {
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
	_delay_ms(2);
}

void lcd_kick() {
	LCD_CTRL |= (1 << EN_SWITCH);
	_delay_ms(1);
	LCD_CTRL &= ~(1 << EN_SWITCH);
	_delay_ms(1);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position) {
	if (line == 1) {
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
	} else if (line == 2) {
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
	}
}

void LCD_INIT() {
	_delay_ms(50);
	DataDir_LCD_CTRL |= (1 << EN_SWITCH) | (1 << RS_SWITCH) | (1 << RW_SWITCH);
	LCD_CTRL &= ~((1 << EN_SWITCH) | (1 << RS_SWITCH) | (1 << RW_SWITCH));
	DataDir_LCD_PORT |= 0xF0;
	_delay_ms(15);

	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	LCD_clear_screen();
}

void LCD_WRITE_COMMAND(unsigned char command) {
	LCD_CTRL &= ~(1 << RS_SWITCH);
	LCD_CTRL &= ~(1 << RW_SWITCH);

	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	lcd_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	lcd_kick();
	#endif
}

void LCD_WRITE_CHAR(unsigned char character) {
	LCD_CTRL |= (1 << RS_SWITCH);
	LCD_CTRL &= ~(1 << RW_SWITCH);

	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	lcd_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	lcd_kick();
	#endif
}

void LCD_WRITE_STRING(char* string) {
	while (*string) {
		LCD_WRITE_CHAR(*string++);
	}
}