#include "./UART.h"

void UART_Init()
{
	//Baud rate
	UBRRL = 51;
	//normal mode
	CLR_Bit(UCSRA,U2X);
	//Frame


	//Enable
	Set_Bit(UCSRB,TXEN);
	Set_Bit(UCSRB,RXEN);
}


void UART_Send(uint8_t data)
{
	while(!Read_Bit(UCSRA,UDRE));
	UDR = data;
}

uint8_t UART_Receive()
{
	while(!Read_Bit(UCSRA,RXC));
	return UDR;
}

void UART_Send_String(const char *str)
{
	while (*str)
	{
		UART_Send(*str++);
	}
}

void UART_Send_Num(uint32_t num)
{
	uint8_t *N = &num;
	UART_Send(N[0]);
	UART_Send(N[1]);
	UART_Send(N[2]);
	UART_Send(N[3]);
	//we can do it with shifting
}

void UART_Receive_Num()
{
	uint32_t num;
	uint8_t *N=&num;
	
	N[0]=UART_Receive();
	N[1]=UART_Receive();
	N[2]=UART_Receive();
	N[3]=UART_Receive();
	
	return num;
}