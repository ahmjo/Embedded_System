typedef volatile unsigned int   vuint32;
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#define RCC_BASE     0x40021000
#define RCC_APB2ENR  *(vuint32*)(RCC_BASE+0X18)
#define RCC_IOPAEN   (1<<2)
#define RCC_IOPBEN   (1<<3)

#define PortA_BASE   0x40010800
#define GPIOA_CRH     *(vuint32*)(PortA_BASE+0X04)
#define GPIOA_CRL     *(vuint32*)(PortA_BASE+0x00)
#define GPIOA_ODR     *(vuint32*)(PortA_BASE+0X0C)
#define GPIOA_IDR     *(vuint32*)(PortA_BASE+ 0x08)
#define GPIOA13      (1UL<<13)

#define PortB_BASE    0x40010C00
#define GPIOB_CRH     *(vuint32*)(PortB_BASE+0X04)
#define GPIOB_CRL     *(vuint32*)(PortB_BASE+0x00)
#define GPIOB_ODR     *(vuint32*)(PortB_BASE+0X0C)
#define GPIOB_IDR     *(vuint32*)(PortB_BASE+ 0x08)


void clock_init()
{
	RCC_APB2ENR |=RCC_IOPAEN;
	RCC_APB2ENR |=RCC_IOPBEN;
}

void GPIO_init()
{
	GPIOA_CRL=0;
	GPIOB_CRL=0;
	GPIOA_CRH=0;
	GPIOB_CRH=0;
	GPIOB_ODR=0;

	//pA1 input h_Z
	GPIOA_CRL |= 1<<6;

	//pB1 output push pull mode
	GPIOB_CRL &= ~(0b11 << 4);
	GPIOB_CRL |= (0b01 << 4);

	//pA13 input h_Z
	GPIOA_CRH &= ~(0b11 << 20);
	GPIOA_CRH |=  (0b01 << 22);
	//pB output push pull mode
	GPIOB_CRH |=  (0b01 << 20);
	GPIOB_CRH &= ~(0b11 << 22);
}

void wait(uint32_t time){
	for(uint32_t i=0 ; i<time ; i++){
		for(uint32_t j=0 ; j<255 ; j++);
	}
}

int main(void)
{
	clock_init();
	GPIO_init();

	while(1)
	{
		if(((GPIOA_IDR & (1<<1))>>1) == 0){ //single pressing
			GPIOB_ODR ^= 1<<1;
			while(((GPIOA_IDR & (1<<1))>>1) == 0);
		}
		if(((GPIOA_IDR & (1<<13))>>13) == 1){ //muti pressing
			GPIOB_ODR ^= 1<<13;
		}
		wait(1);
	}
}
