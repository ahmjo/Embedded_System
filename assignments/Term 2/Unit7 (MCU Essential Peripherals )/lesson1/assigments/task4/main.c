#define F_CPU 80000000UL
#include "util/delay.h"
#include "Utils.h"
#include "MemoryMap.h"

GPIO_init()
{
	DDRD=0xf0;
	Set_bit(PORTD,0);
	Set_bit(PORTD,1);
	Set_bit(PORTD,2);
}

GPIO_SET()
{
	Set_bit(PORTD,5);
	_delay_ms(100);
	Set_bit(PORTD,6);
	_delay_ms(100);
	Set_bit(PORTD,7);
	_delay_ms(100);
}

GPIO_RESET()
{
	Clear_bit(PORTD,7);
	_delay_ms(100);
	Clear_bit(PORTD,6);
	_delay_ms(100);
	Clear_bit(PORTD,5);
	_delay_ms(100);
}


int main(void)
{
	GPIO_init();
	unsigned int i=4;

    while (1)
    {
    	if(Read_bit(PIND,0)==1)
    	{
			Clear_bit(PORTD,i);
			i++;
			if(i>7)i=4;
			Set_bit(PORTD,i);
			_delay_ms(100);
			while(Read_bit(PIND,0)==1);
    	}
    	else if(Read_bit(PIND,1)==1)
    	{
    		GPIO_SET();
    		GPIO_RESET();
			while(Read_bit(PIND,1)==1);
    	}
    	else if(Read_bit(PIND,2)==1)
    	{
    		Set_bit(PORTD,4);
			_delay_ms(100);
    		Clear_bit(PORTD,4);
			while(Read_bit(PIND,2)==1);
    	}
    	Clear_bit(PORTD,5);
    	Clear_bit(PORTD,6);
    	Clear_bit(PORTD,7);
    }
}