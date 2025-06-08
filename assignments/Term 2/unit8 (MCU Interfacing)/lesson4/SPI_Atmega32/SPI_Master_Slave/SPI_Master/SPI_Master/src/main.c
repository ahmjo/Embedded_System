#include <avr/io.h>

# define F_CPU 1000000UL
#include <util/delay.h>


#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

void SPI_MasterInit(void)
{
	DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCK);
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

uint8_t SPI_MasterTransmit(uint8_t cdata)
{
	SPDR = cdata;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

int main(void)
{
	SPI_MasterInit();
	DDRA = 0xFF;
	uint8_t data = 0;
	for(data = 0 ; data <= 255 ; data++)
	{
		_delay_ms(1000);
		PORTA = SPI_MasterTransmit(data);
	}
	return 0;
}