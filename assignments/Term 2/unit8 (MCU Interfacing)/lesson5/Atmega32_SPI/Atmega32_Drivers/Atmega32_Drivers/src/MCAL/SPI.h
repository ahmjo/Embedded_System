/*
 * SPI.h
 *
 * Created: 03/07/2025 02:07:30
 *  Author: AAMA
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MASTER_MODE
//#define SLAVE_MODE
#include <avr/io.h>


#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define MOSI		5
#define SS			4
#define MISO		6
#define SCK			7

#define Slave_Enable()	(SPI_PORT &= ~(1<<SS))
#define Slave_Disable()	(SPISPI_PORT |= (1<<SS))

void SPI_Init(void);
uint8_t SPI_Tx_Rx(uint8_t Data);


#endif /* SPI_H_ */