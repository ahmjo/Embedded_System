#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define SS		4
#define MOSI	5
#define SCK		7

void SPI_MasterInit(void)
{
	DDRB |= (1<<MOSI) | (1<<SS) | (1<<SCK);
	SPCR |= (1<<MSTR) | (1<<SPE) | (1<<SPR0);
}

void Execute(uint8_t COM, uint8_t data)
{
	PORTB &= ~(1<<SS);
	
	SPDR = COM;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	
	PORTB |= (1<<SS);
}


int main(void)
{
	SPI_MasterInit();
	Execute(0x09, 0xFF);
	Execute(0x0A, 0xFF);
	Execute(0x0B, 0xF7);
	Execute(0x0C, 0x01);
	
	uint8_t count = 0;
	while(1)
	{
		for(uint8_t iDisplay=1 ; iDisplay <9 ; iDisplay++)
			Execute(iDisplay, count++);
		_delay_ms(1000);
	}
}