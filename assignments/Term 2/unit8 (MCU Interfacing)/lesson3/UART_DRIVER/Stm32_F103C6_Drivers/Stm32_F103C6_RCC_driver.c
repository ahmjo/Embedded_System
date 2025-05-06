#include "Stm32_F103C6_RCC_driver.h"


// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
// Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
// Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
// 0xx: HCLK not divided
// 100: HCLK divided by 2
// 101: HCLK divided by 4
// 110: HCLK divided by 8
// 111: HCLK divided by 16
const uint8_t APBprescTable[8U] = {0, 0, 0, 0, 1, 2, 3};

//Bits 7:4HPRE: AHB prescaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBprescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};



uint32_t MCAL_RCC_GetSYS_CLKFreq(void)
{
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_Clk;
		break;
	case 1:
		//to do need to calculate  it //HSE User Should Specify it
		return HSE_Clock;
		break;
	case 2:
		//to do need to calculate  it PLLCLK and PLLMUL & PLL Source MUX
		return 16000000;
		break;
	}
	return 0;
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	// Bits 7:4HPRE: AHB prescaler
	return (MCAL_RCC_GetSYS_CLKFreq() >> AHBprescTable[(RCC->CFGR >> 4) & 0xf]);
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	return (MCAL_RCC_GetHCLKFreq() >> APBprescTable[(RCC->CFGR >> 8) & 0b111]);
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
    //Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_GetHCLKFreq() >> APBprescTable[(RCC->CFGR >> 11) & 0b111]);
}
