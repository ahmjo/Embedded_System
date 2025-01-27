/*
 * STM32F103X6.h
 *
 *  Created on: Jan 27, 2025
 *      Author: AAMA
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//Includes
#include <stdio.h>
#include <stdint.h>

//---------------------------------------
//Base addresses for Memories
//---------------------------------------
#define FLASH_Memory_BASE 							0x08000000UL
#define System_Memory_BASE 							0x1FFFF000UL
#define SRAM_Memory_BASE 							0x20000000UL
#define Peripherals_BASE 							0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE 		0xE0000000UL



//---------------------------------------
//Base addresses for AHB Peripherals
//---------------------------------------
#define RCC_BASE       0x40021000UL
//or we can write it like this (Peripherals_BASE + 0x00021000UL)

//---------------------------------------
//Base addresses for APB2 Peripherals
//---------------------------------------

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE     0x40010800UL
#define GPIOB_BASE     0x40010C00UL

//C,D partial included in LQFP48 Package
#define GPIOC_BASE     0x40011000UL
#define GPIOD_BASE     0x40011400UL

//EXTI
#define EXTI_BASE	   0x40010400UL

//AFIO
#define AFIO_BASE      0x40010000UL

//=========================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t reserved;
	volatile uint32_t MAPR2;
}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//=============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA     ((GPIO_t *)GPIOA_BASE)
#define GPIOB     ((GPIO_t *)GPIOB_BASE)
#define GPIOC     ((GPIO_t *)GPIOC_BASE)
#define GPIOD     ((GPIO_t *)GPIOD_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO     ((AFIO_t *)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC     ((RCC_t *)RCC_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI     ((EXTI_t *)EXTI_BASE)

//=============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()							SET_BIT(RCC->APB2ENR,2)
#define RCC_GPIOB_CLK_EN()							SET_BIT(RCC->APB2ENR,3)
#define RCC_GPIOC_CLK_EN()							SET_BIT(RCC->APB2ENR,4)
#define RCC_GPIOD_CLK_EN()							SET_BIT(RCC->APB2ENR,5)
#define RCC_GPIOE_CLK_EN()							SET_BIT(RCC->APB2ENR,6)
#define RCC_AFIO_CLK_EN()							SET_BIT(RCC->APB2ENR,0)

//=============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(Reg,Bit_No)							(Reg |= (1 << Bit_No))
#define CLEAR_BIT(Reg,Bit_No)						(Reg &= ~ (1 << Bit_No))
#define TOGGLE_BIT(Reg,Bit_No)						(Reg ^= (1 << Bit_No))
#define READ_BIT(Reg,Bit_No)

#endif /* INC_STM32F103X6_H_ */
