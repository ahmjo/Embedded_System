typedef volatile unsigned int vuint32;
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <MemoryMap.h>
#include <Utils.h>
#define D_CPU 8000000UL

void wait(uint32_t time);

int main(void)
{
	unsigned int flag = 0;
	DDRA = 0xFF;
	resetbit(DDRC, 0);
	setbit(PORTC, 0);

	while (1)
	{
		if (readbit(PINC, 0) == 0)
		{
			toggle(PORTA, flag);
			flag++;
			if (flag > 7) flag = 0;

			while (readbit(PINC, 0) == 0);
			wait(50);
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
