#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

void SPI_SlaveInit(void)
{
	DDRB |= (1<<MISO);
	DDRB &= ~(1<<MOSI) & ~(1<<SCK) & ~(1<<SS);
	SPCR |= (1<<SPE);
}

uint8_t SPI_SlaveReceive(uint8_t cdata)
{
	SPDR = cdata;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

int main(void)
{
	SPI_SlaveInit();
	DDRA = 0xFF;
	uint8_t data = 0;
	for(data = 255 ; data >= 0 ; data--)
	{
		_delay_ms(1000);
		PORTA = SPI_SlaveReceive(data);
	}
	return 0;
}