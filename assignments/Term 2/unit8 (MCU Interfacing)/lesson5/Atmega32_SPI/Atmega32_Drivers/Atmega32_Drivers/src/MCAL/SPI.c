/*
 * SPI.c
 *
 * Created: 03/07/2025 02:07:43
 *  Author: AAMA
 */ 


#include "SPI.h"

void SPI_Init(void)
{
	#if (SPI_MODE == MASTER)
		SPCR |= (1<<MSTR);
		SPCR &= ~(1<<CPOL);
	
	#elif (SPI_MODE == SLAVE)
		SPCR &= ~(1<<MSTR);
	#endif
	
	SPCR |= (1<<SPE);
}

uint8_t SPI_Tx_Rx(uint8_t Data)
{
	SPDR = Data;
	while(!((SPSR>>SPIF)&1));
	return SPDR
}

/*
void SPI_Init(uint8_t state)
{
	switch(state)
	{
		case 'M':
		SPI_DDR |= (1<<MOSI)|(1<<SCK)|(1<<SS);
		SPI_DDR &= ~(1<<MISO);
		SPCR = (1<<MSTR)|(1<<SPE);
		break;
		
		case 'S':
		SPI_DDR &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));
		SPI_DDR |= (1<<MISO);
		SPCR = (1<<SPE);
		break;
	}
}


uint8_t SPI_Tx_Rx(uint8_t Data)
{
	SPDR = Data;
	while(!(SPSR & (1<<SPIF)));
	return SPI_DDR;
}
*/