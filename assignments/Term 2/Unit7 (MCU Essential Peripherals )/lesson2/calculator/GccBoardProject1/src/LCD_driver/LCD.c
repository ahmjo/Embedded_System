#include "lcd.h"

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void lcd_kick(){
	LCD_CTRL |= (1 << EN_SWITCH);
	_delay_ms(50);
	LCD_CTRL &= ~(1 << EN_SWITCH);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_INIT(){
	_delay_ms(20);
	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	LCD_CTRL &= ~ (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	DataDir_LCD_PORT = 0xFF;
	_delay_ms(15);
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);	
}

void lcd_isbusy(){
	DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	LCD_CTRL |= (1 << RW_SWITCH);
	LCD_CTRL &= ~(1 << RS_SWITCH);
	lcd_kick();
	DataDir_LCD_PORT |= (0xFF<<DATA_shift);
	LCD_CTRL &= ~(1 << RW_SWITCH);	
}


void LCD_WRITE_COMMAND(unsigned char command){
	lcd_isbusy();
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command;
		LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH)); 
		lcd_kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_PORT= (LCD_PORT & 0x0f) | (command & 0xf0);
		LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
		lcd_kick();
		LCD_PORT= (LCD_PORT & 0x0f) | (command << 4);
		LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
		lcd_kick();
	#endif
}

void LCD_WRITE_CHAR(unsigned char character){
	lcd_isbusy();
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = character;
		LCD_CTRL &= ~(1 << RW_SWITCH);
		LCD_CTRL |= (1 << RS_SWITCH);
		lcd_kick();
	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_PORT= (LCD_PORT & 0x0f) | (character & 0xf0);
		LCD_CTRL &= ~(1 << RW_SWITCH);
		LCD_CTRL |= (1 << RS_SWITCH);
		lcd_kick();
		LCD_PORT= (LCD_PORT & 0x0f) | (character << 4);
		LCD_CTRL &= ~(1 << RW_SWITCH);
		LCD_CTRL |= (1 << RS_SWITCH);
		lcd_kick();
	#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	int l=1;
	int pos=0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		LCD_GOTO_XY(l,pos);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
			l=2;
			pos=0;
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
			l=1;
			pos=0;
		}
	}
}