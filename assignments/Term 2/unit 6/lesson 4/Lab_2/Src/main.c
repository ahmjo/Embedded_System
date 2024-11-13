typedef volatile unsigned int   vuint32;

#define RCC_BASE     0x40021000
#define PortA_BASE   0x40010800

#define RCC_APB2ENR  *(vuint32*)(RCC_BASE+0X18)
#define GPIO_CRH     *(vuint32*)(PortA_BASE+0X04)
#define GPIO_CRL     *(vuint32*)(PortA_BASE+0x00)
#define GPIO_ODR     *(vuint32*)(PortA_BASE+0X0C)

#define RCC_IOPAEN   (1<<2)
#define RCC_AFIORST  (1<<0)
#define GPIOA13      (1UL<<13)

#define EXTI_BASE    0x40010400
#define EXTI_IMR     *(vuint32*)(EXTI_BASE+0X00)
#define EXTI_RTSR    *(vuint32*)(EXTI_BASE+0X08)
#define EXTI_PR      *(vuint32*)(EXTI_BASE+0X14)

#define AFIO_BASE    0x40010000
#define AFIO_EXTICR1 *(vuint32*)(AFIO_BASE+0X08)

#define NVIC_EXTI0  *(vuint32*)(0XE000E100)


void clock_init()
{
	RCC_APB2ENR |=RCC_IOPAEN;
	RCC_APB2ENR |=RCC_AFIORST;
}

void GPIO_init()
{
	GPIO_CRH &=0xff0fffff;
	GPIO_CRH |=0x00200000;
	GPIO_CRL |=(1<<2);
}

int main(void)
{
	AFIO_EXTICR1 = 0;
	EXTI_RTSR |= (1<<0);
	EXTI_IMR |= (1<<0);
	NVIC_EXTI0 |= (1<<6);

	while(1);
}

void EXTI_IRQHandler(void)
{
	//toggle LED port A 13
	GPIO_ODR^=(1<<13);

	EXTI_PR |= (1<<0);
}