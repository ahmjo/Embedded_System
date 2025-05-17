#include <HAL/LCD_Driver/LCD.h>
#include <MCAL/UART.h>
#include <./Utils.h>
#include <stdint.h>
#include <avr/io.h>

int main(void)
{
	LCD_INIT();
	UART_Init();
	
	LCD_GOTO_XY(1,0);
	LCD_WRITE_STRING("UART Tx");
	UART_Send('x');
	UART_Send('y');
	LCD_GOTO_XY(2,0);
	while(1)
	{
		char x = UART_Receive();
		LCD_WRITE_CHAR(x);
	}
}

