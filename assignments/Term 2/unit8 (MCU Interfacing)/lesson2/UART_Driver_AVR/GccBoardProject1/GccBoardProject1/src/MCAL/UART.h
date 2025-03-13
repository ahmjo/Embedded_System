#include <../Utils.h>
#include <stdint.h>
#include <avr/io.h>

#ifndef UART_H_
#define UART_H_



void UART_Init(void);
void UART_Send(uint8_t data);
uint8_t UART_Receive(void);
void UART_Send_String(const char *str);
void UART_Send_Num(uint32_t num);
void UART_Receive_Num();


#endif /* UART_H_ */