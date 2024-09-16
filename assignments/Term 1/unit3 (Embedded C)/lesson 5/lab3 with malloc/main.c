#include "stdint.h"
#include "stdlib.h"
typedef volatile unsigned int   vuint32;

#define RCC_BASE    0x40021000
#define PortA_BASE  0x40010800

#define RCC_APB2ENR *(vuint32*)(RCC_BASE+0X18)
#define GPIO_CHR    *(vuint32*)(PortA_BASE+0X04)
#define GPIO_ODR    *(vuint32*)(PortA_BASE+0X0C)

#define RCC_IOPAEN  (1<<2)
#define GPIOA13      (1UL<<13)

typedef union{
	vuint32 all;
	struct {
		vuint32 reserved :13;
		vuint32 p_13 :1;
	}pin;
}RO;

volatile RO * R_ODR=(volatile RO*)(PortA_BASE+0X0C);

void* _sbrk (int incr){
	static unsigned char* heap_ptr = NULL ;
	static unsigned char* prev_heap_ptr = NULL ;
	extern unsigned int _E_bss ;
	extern unsigned int _E_heap ;

	if(heap_ptr==NULL){
		heap_ptr = (unsigned char*) &_E_bss;
	}
	prev_heap_ptr = heap_ptr;

	if ((heap_ptr + incr)>(&_E_heap)){
		return (void*) NULL;
	}

	heap_ptr += incr;

	return (void*) prev_heap_ptr;
}

int main(void)
{
	int* p = (int*)malloc(4);
	RCC_APB2ENR |=RCC_IOPAEN;
	GPIO_CHR &=0xff0fffff;
	GPIO_CHR |=0x00200000;
	while(1)
	{
		R_ODR ->pin.p_13=1;
		for(int i=0;i<500;i++);
		R_ODR ->pin.p_13=0;
		for(int i=0;i<500;i++);
	}
	free(p);
}