typedef volatile unsigned int vuint32;
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <MemoryMap.h>
#include <Utils.h>
#define F_CPU 8000000UL

void wait(uint32_t time);

static unsigned char seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main(void)
{
	unsigned int flag = 0;
	DDRA = 0xFF;
	resetbit(DDRC, 0);
	setbit(PORTC, 0);

	while (1)
	{
		for (flag = 0; flag < 10; flag++)
		{
			PORTA = seg[flag];
			wait(50000000);
		}
	}
}

void wait(uint32_t time)
{
	for (uint32_t i = 0; i < time; i++)
	{
		for (uint32_t j = 0; j < 500; j++);
	}
}
