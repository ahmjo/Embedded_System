#include "Stm32_F103C6_USART_driver.h"


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
UART_Config_t* Global_UART_Config = NULL;


/*
 * =======================================================================================
 * 							             APIs
 * =======================================================================================
 */

/**================================================================
 * @Fn				- MCAL_UART_Init
 * @brief 			- Initializes UART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			- NONE
 ==================================================================*/

void MCAL_UART_Init(USART_t* USARTx, UART_Config_t* UART_Config)
{
	uint32_t pclk, BRR;
	Global_UART_Config = UART_Config;

	//Enable the Clock for given USART Peripheral
	if(USARTx == USART1) RCC_USART1_CLK_EN();
	else if(USARTx == USART2) RCC_USART2_CLK_EN();
	else if(USARTx == USART3) RCC_USART3_CLK_EN();

	//Enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//Enable USART Tx & Rx engines according  to the USART_Mode configuration item
	//USART_CR1  Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode;

	//PayLoad Width
	//USART_CR1 Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Configuration of parity control bit fields
	//USARTx->CR1 Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->parity;

	//configure the number of stop bits
	//USART_CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= UART_Config->StopBits;

	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HwFlow_CTL;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2,3
	//PCLK2 for USART1
	if(USARTx == USART1) pclk = MCAL_RCC_GetPCLK2Freq();
	else pclk = MCAL_RCC_GetPCLK1Freq();

	BRR = UART_BRR_Register(pclk, UART_Config->BaudRate) ;
	USARTx->BRR = BRR ;

	//ENABLE / DISABLE Interrupt
	//USART_CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		//Enable NVIC For USARTx IRQ
		if(USARTx == USART1) NVIC_IRQ37_USART1_EN;
		else if(USARTx == USART2) NVIC_IRQ38_USART2_EN;
		else if(USARTx == USART3) NVIC_IRQ39_USART3_EN;
	}
}


/**================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief 			- DEInitializes UART
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- NONE
 =================================================================*/
void MCAL_UART_DeInit(USART_t* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
}


/**================================================================
 * @fn      		  - MCAL_UART_SendData
 *
 * @brief             - Send Buffer on UART
 *
 * @param [in] 		  - USARTx: where x can be (1..3 depending on device used)
 * @param[in]         - pTxBuffer
 * @param[in]         - PollingEn   Enable pooling or disable it
 *
 * @retval 			  - NONE
 =================================================================*/
void MCAL_UART_SendData(USART_t* USARTx, uint16_t* pTxBuffer, enum Polling_mechism PollingEn)
{

	// wait until TXE flag is set in the SR
	if(PollingEn == enable) while(!(USARTx->SR & 1<<7));

	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit.

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
		//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	else
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
}


void MCAL_UART_WAIT_TC (USART_t* USARTx )
{
	// wait till TC flag is set in the SR
	while(!(USARTx->SR & 1<<6));
}



void MCAL_UART_ReceiveData(USART_t* USARTx, uint16_t* pRxBuffer, enum Polling_mechism PollingEn )
{
	// wait until TXE flag is set in the SR
	if(PollingEn == enable) while(!(USARTx->SR & 1<<5));

	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		//This is 9bit data
		if(Global_UART_Config->parity == UART_parity_NONE)
		{
			//no parity So all 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR;
		}
		else
		{
			//Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else
	{
		//This is 8bit data
		if (Global_UART_Config->parity == UART_parity_NONE)
		{
			//no parity So all 8bit are considered data
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			//Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}
}


/**================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- NONE
 =================================================================*/
void MCAL_UART_GPIO_Set_Pins(USART_t* USARTx)
{
	GPIO_Config_t PinCfg;
	if(USARTx == USART1)
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if(Global_UART_Config->HwFlow_CTL == UART_HwFlow_CTL_CTS || Global_UART_Config->HwFlow_CTL == UART_HwFlow_CTL_RTS_CTS)
		{
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if(Global_UART_Config->HwFlow_CTL == UART_HwFlow_CTL_RTS || Global_UART_Config->HwFlow_CTL == UART_HwFlow_CTL_RTS_CTS)
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if(USARTx == USART2)
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_CTS  || Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS_CTS  )
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if (Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS || Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS_CTS  )
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if ( USARTx == USART3 )
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if (Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_CTS  || Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS_CTS  )
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		if (Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS || Global_UART_Config->HwFlow_CTL  == UART_HwFlow_CTL_RTS_CTS  )
		{
			//PA14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
	}
}



//ISR
void USART1_IRQHandler()
{
	Global_UART_Config->P_IRQ_CallBack();
}

void USART2_IRQHandler()
{
	Global_UART_Config->P_IRQ_CallBack();
}

void USART3_IRQHandler()
{
	Global_UART_Config->P_IRQ_CallBack();
}




















