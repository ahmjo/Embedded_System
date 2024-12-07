#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0X18)
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_CR *(volatile uint32_t *)(RCC_BASE + 0x0)

int main(void){
	RCC_APB2ENR	|= 1<<2;
	RCC_CFGR |= (0b10<<0);
	RCC_CFGR |= (0b101<<11);
	RCC_CFGR |= (0b100<<8);
	RCC_CFGR |= (0b0110<<18);
	RCC_CR |= 1<<24;

	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while(1){
		GPIOA_ODR |= 1<<13 ;
		for (int i = 0; i < 5000; i++);
		GPIOA_ODR &= ~(1<<13) ;
		for (int i = 0; i < 5000; i++);
	}
}
