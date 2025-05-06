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

//NVIC
#define NVIC_BASE									0xE000E100UL
#define NVIC_ISER0									(*(volatile uint32_t*)(NVIC_BASE+0x0))
#define NVIC_ISER1									(*(volatile uint32_t*)(NVIC_BASE+0x4))
#define NVIC_ISER2									(*(volatile uint32_t*)(NVIC_BASE+0x8))
#define NVIC_LCER0									(*(volatile uint32_t*)(NVIC_BASE+0x80))
#define NVIC_LCER1									(*(volatile uint32_t*)(NVIC_BASE+0x84))
#define NVIC_LCER2									(*(volatile uint32_t*)(NVIC_BASE+0x88))


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

//USART1
#define USART1_BASE	   0x40013800UL
//---------------------------------------
//Base addresses for APB1 Peripherals
//---------------------------------------

//USART2,3
#define USART2_BASE	   0x40004400UL
#define USART3_BASE	   0x40004800UL
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
	volatile uint32_t EXTICR[4];
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

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_t;


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

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: USART
//-*-*-*-*-*-*-*-*-*-*-*
#define USART1	((USART_t*)USART1_BASE)
#define USART2	((USART_t*)USART2_BASE)
#define USART3	((USART_t*)USART3_BASE)

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

//Clock enable USART
#define RCC_USART1_CLK_EN()							SET_BIT(RCC->APB2ENR,14)
#define RCC_USART2_CLK_EN()							SET_BIT(RCC->APB1ENR,17)
#define RCC_USART3_CLK_EN()							SET_BIT(RCC->APB1ENR,18)

//RCC reset mechanism
#define RCC_USART1_Reset()							SET_BIT(RCC->APB2RSTR,14)
#define RCC_USART2_Reset()							SET_BIT(RCC->APB1RSTR,17)
#define RCC_USART3_Reset()							SET_BIT(RCC->APB1RSTR,18)


//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Enable/Disable macros
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_EN			(NVIC_ISER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_EN			(NVIC_ISER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_EN			(NVIC_ISER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_EN			(NVIC_ISER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_EN			(NVIC_ISER0 |= (1<<10))
#define NVIC_IRQ23_EXTI5_9_EN		(NVIC_ISER0 |= (1<<23))
#define NVIC_IRQ40_EXTI10_15_EN		(NVIC_ISER1 |= (1<<8))//40-32=8


#define NVIC_IRQ6_EXTI0_Disable         (NVIC_LCER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_Disable         (NVIC_LCER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_Disable         (NVIC_LCER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_Disable         (NVIC_LCER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_Disable        (NVIC_LCER0 |= (1<<10))
#define NVIC_IRQ23_EXTI5_9_Disable      (NVIC_LCER0 |= (1<<23))
#define NVIC_IRQ40_EXTI10_15_Disable    (NVIC_LCER1 |= (1<<8))  // 40-32=8

//USART
#define NVIC_IRQ37_USART1_EN			(NVIC_ISER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_EN			(NVIC_ISER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_EN			(NVIC_ISER1 |= (1<<(USART3_IRQ-32)))

#define NVIC_IRQ37_USART1_Disable 			(NVIC_LCER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_Disable 			(NVIC_LCER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_Disable 			(NVIC_LCER1 |= (1<<(USART3_IRQ-32)))


//-*-*-*-*-*-*-*-*-*-*-*-
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI15_IRQ		40
#define EXTI16_IRQ		40
#define EXTI17_IRQ		40
#define EXTI18_IRQ		40

//USART
#define USART1_IRQ		37
#define USART2_IRQ		38
#define USART3_IRQ		39

//=============================================================
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(Reg,Bit_No)							(Reg |= (1 << Bit_No))
#define CLEAR_BIT(Reg,Bit_No)						(Reg &= ~ (1 << Bit_No))
#define TOGGLE_BIT(Reg,Bit_No)						(Reg ^= (1 << Bit_No))


#endif /* INC_STM32F103X6_H_ */
