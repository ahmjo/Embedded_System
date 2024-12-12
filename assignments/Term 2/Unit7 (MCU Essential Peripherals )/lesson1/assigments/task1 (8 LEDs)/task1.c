typedef volatile unsigned int   vuint32;
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <MemoryMap.h>
#define D_CPU 8000000UL

void wait(uint32_t time);

int main(void)
{
	DDRA=0b11111111;

	while(1)
	{
		PORTA=0x1;
		wait(1);
		PORTA=0x3;
		wait(1);
		PORTA=0x7;
		wait(1);
		PORTA=0xf;
		wait(1);
		PORTA=0x1f;
		wait(1);
		PORTA=0x3f;
		wait(1);
		PORTA=0x7f;
		wait(1);
		PORTA=0xff;
		wait(1);
		
		PORTA=0x7f;
		wait(1);
		PORTA=0x3f;
		wait(1);
		PORTA=0x1f;
		wait(1);
		PORTA=0xf;
		wait(1);
		PORTA=0x7;
		wait(1);
		PORTA=0x3;
		wait(1);
		PORTA=0x1;
		wait(1);
		PORTA=0;
		wait(1);
	}
}

void wait(uint32_t time){
	for(uint32_t i=0 ; i<time ; i++){
		for(uint32_t j=0 ; j<500000 ; j++);
	}
}
