//Includes
#include "Stm32_F103C6_EXTI_driver.h"


//Generic Macros
#define AFIO_GPIO_EXTI_Mapping(x)		((x == GPIOA) ? 0 : \
										(x == GPIOB) ? 1 : \
										(x == GPIOC) ? 2 : \
										(x == GPIOD) ? 3 : 0)


//Generic Variable
void (*GP_IRQ_CallBack[15])();

//Generic Function
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_EN;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_EN;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_EN;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_EN;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_EN;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_EN;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_EN;
		break;
	}
}
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}
}

void Update_EXTI(EXTI_Config_t* EXTI_Config)
{
	//1-configure GPIO to be AF input -> Floating input
	GPIO_Config_t PINCFG;

	PINCFG.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	PINCFG.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port,&PINCFG);
	//====================================================
	//2-Update AFIO to Route between EXTI line with Port A,B,C,D
	uint8_t AFIO_EXTICR_Index = EXTI_Config->EXTI_PIN.EXTI_Input_LineNum/4;
	uint8_t AFIO_EXTICR_POS   = (EXTI_Config->EXTI_PIN.EXTI_Input_LineNum%4)*4;
	AFIO->EXTICR[AFIO_EXTICR_Index] &= (0xF << AFIO_EXTICR_POS);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTICR_POS);
	//====================================================
	//3-Update Rising or Falling Register
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Both)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	}
	//====================================================
	//4-Update IRQ handling CallBack
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_Input_LineNum] = EXTI_Config->P_IRQ_CallBack;

	//====================================================
	//5-Enable\Disable IRQ EXTI & NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_EN)
	{
		EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	}else{
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_Input_LineNum);
	}
}

//APIs Functions Define
/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Deinit
 * @brief 		-Reset the EXTI Registers & NVIC corresponding IRQ mask
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_EXTI_GPIO_Deinit(void)
{
	EXTI->IMR	 = 0x00000000;
	EXTI->EMR 	 = 0x00000000;
	EXTI->RTSR 	 = 0x00000000;
	EXTI->FTSR 	 = 0x00000000;
	EXTI->SWIER	 = 0x00000000;
	//rc_w1
	EXTI->PR	 = 0xFFFFFFFF;

	//Disable all EXTI ORQ from NVIC
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;
}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-Init EXTI from specific GPIO PIN & specify the mask/trigger
 * @param [in] 	-EXTI_Config set by @ref EXTI_Define & EXTI_Trigger_define & EXTI_IRQ_Define
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_EXTI_GPIO_Init(EXTI_Config_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief 		-Init EXTI from specific GPIO PIN & specify the mask/trigger
 * @param [in] 	-EXTI_Config set by @ref EXTI_Define & EXTI_Trigger_define & EXTI_IRQ_Define
 * @retval 		-none
 * Note			-none
================================================================**/

void MCAL_EXTI_GPIO_Update(EXTI_Config_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}




/***************************************************
 * ****** ISR Functions ****************************
 * *************************************************
*/

void EXTI0_IRQHandler(void)
{
	//cleared by writing 1 into the bit (EXTI_PR)
	EXTI->PR |= (1<<0);
	//Call IRQ Call
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler(void)
{
	//cleared by writing 1 into the bit (EXTI_PR)
	EXTI->PR |= (1<<1);
	//Call IRQ Call
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler(void)
{
	//cleared by writing 1 into the bit (EXTI_PR)
	EXTI->PR |= (1<<2);
	//Call IRQ Call
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler(void)
{
	//cleared by writing 1 into the bit (EXTI_PR)
	EXTI->PR |= (1<<3);
	//Call IRQ Call
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler(void)
{
	//cleared by writing 1 into the bit (EXTI_PR)
	EXTI->PR |= (1<<4);
	//Call IRQ Call
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<5)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[5]();}
	if(EXTI->PR & (1<<6)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[6]();}
	if(EXTI->PR & (1<<7)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[7]();}
	if(EXTI->PR & (1<<8)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[8]();}
	if(EXTI->PR & (1<<9)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[9]();}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[10]();}
	if(EXTI->PR & (1<<11)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[11]();}
	if(EXTI->PR & (1<<12)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[12]();}
	if(EXTI->PR & (1<<13)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[13]();}
	if(EXTI->PR & (1<<14)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[14]();}
	if(EXTI->PR & (1<<15)){EXTI->PR |= (1<<5);	GP_IRQ_CallBack[15]();}
}
