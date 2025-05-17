#include <../Utils.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef UART_H_
#define UART_H_


#define DefaultStop '\r'



void UART_Init(void);
void UART_Send(uint8_t data);
uint8_t UART_Receive(void);
void UART_Send_String(const char *str);
void UART_Send_Num(uint32_t num);
uint32_t UART_Receive_Num(void);
void UART_Receive_String(uint8_t *Buff);
uint8_t UART_Receive_PeriodicCheck(uint8_t *pdata);
void UART_SendNoBlock(uint8_t data);
uint8_t UART_ReceiveNoBlock(void);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_SendString_Asynch(uint8_t *Str);
void UART_ReceiveString_Asynch(uint8_t *Str);
uint8_t UART_ReceiveString_IsDone(void);



#endif /* UART_H_ */