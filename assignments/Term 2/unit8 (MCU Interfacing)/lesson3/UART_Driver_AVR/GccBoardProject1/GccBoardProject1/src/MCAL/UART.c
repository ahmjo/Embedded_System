#include "UART.h"
#include <avr/interrupt.h>

static uint8_t flag_send = 1;
uint8_t *Tx_Str = 0;

static uint8_t *Rx_Str = 0;
static uint8_t Rx_AsyncIndex = 0;
static uint8_t Rx_AsyncBusy = 0;
static uint8_t Rx_AsyncDone = 0;

void UART_Init(void)
{
	UBRRL = 51;
	CLR_Bit(UCSRA, U2X);
	Set_Bit(UCSRB, TXEN);
	Set_Bit(UCSRB, RXEN);
	UART_RX_InterruptEnable();
}

void UART_Send(uint8_t data)
{
	while (!Read_Bit(UCSRA, UDRE));
	UDR = data;
}

uint8_t UART_Receive(void)
{
	while (!Read_Bit(UCSRA, RXC));
	return UDR;
}

void UART_Send_String(const char *str)
{
	while (*str)
	{
		UART_Send(*str++);
	}
	UART_Send(DefaultStop);
}

void UART_Receive_String(uint8_t *Buff)
{
	uint8_t i = 0;
	Buff[i] = UART_Receive();
	while (Buff[i] != DefaultStop)
	{
		i++;
		Buff[i] = UART_Receive();
	}
	Buff[i] = '\0';
}

void UART_Send_Num(uint32_t num)
{
	uint8_t *N = (uint8_t *)&num;
	UART_Send(N[0]);
	UART_Send(N[1]);
	UART_Send(N[2]);
	UART_Send(N[3]);
}

uint32_t UART_Receive_Num(void)
{
	uint32_t num;
	uint8_t *N = (uint8_t *)&num;
	N[0] = UART_Receive();
	N[1] = UART_Receive();
	N[2] = UART_Receive();
	N[3] = UART_Receive();
	return num;
}

uint8_t UART_Receive_PeriodicCheck(uint8_t *pdata)
{
	if (Read_Bit(UCSRA, RXC))
	{
		*pdata = UDR;
		return 1;
	}
	return 0;
}

void UART_SendNoBlock(uint8_t data)
{
	UDR = data;
}

uint8_t UART_ReceiveNoBlock(void)
{
	return UDR;
}

void UART_RX_InterruptEnable(void)
{
	Set_Bit(UCSRB, RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_Bit(UCSRB, RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	Set_Bit(UCSRB, TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_Bit(UCSRB, TXCIE);
}

void UART_SendString_Asynch(uint8_t *Str)
{
	if (flag_send == 1)
	{
		UART_TX_InterruptEnable();
		UART_SendNoBlock(Str[0]);
		Tx_Str = Str;
		flag_send = 0;
	}
}

void UART_ReceiveString_Asynch(uint8_t *Str)
{
	if (!Rx_AsyncBusy)
	{
		Rx_Str = Str;
		Rx_AsyncIndex = 0;
		Rx_AsyncBusy = 1;
		Rx_AsyncDone = 0;
		UART_RX_InterruptEnable();
	}
}

uint8_t UART_ReceiveString_IsDone(void)
{
	if (Rx_AsyncDone)
	{
		Rx_AsyncDone = 0;
		return 1;
	}
	return 0;
}

ISR(UART_TX_Vect)
{
	static uint8_t i = 1;
	if (Tx_Str[i] != '\0')
	{
		UART_SendNoBlock(Tx_Str[i]);
		i++;
	}
	else
	{
		i = 1;
		flag_send = 1;
		UART_TX_InterruptDisable();
	}
}

ISR(UART_RX_Vect)
{
	uint8_t data = UART_ReceiveNoBlock();

	if (Rx_Str != 0 && Rx_AsyncBusy)
	{
		if (data != DefaultStop)
		{
			Rx_Str[Rx_AsyncIndex++] = data;
		}
		else
		{
			Rx_Str[Rx_AsyncIndex] = '\0';
			Rx_AsyncBusy = 0;
			Rx_AsyncDone = 1;
			Rx_Str = 0;
		}
	}
}
