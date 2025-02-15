#define F_CPU 8000000UL

#include <avr/io.h>
#include "LCD_driver/LCD.h"

void GPIO_Init() {
	DDRA |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
	DDRB |= (1 << RS_SWITCH) | (1 << RW_SWITCH) | (1 << EN_SWITCH);
}

int main(void) {
	GPIO_Init();
	LCD_INIT();
	 _delay_ms(10);
	LCD_WRITE_STRING("Learn in depth...");

	while (1) {
	}
}