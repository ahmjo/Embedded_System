/*
 * Stm32_F103C6_I2C_driver.c
 *
 *  Created on: Aug 19, 2025
 *      Author: AAMA
 */

#include "Stm32_F103C6_I2C_driver.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
I2C_Config_t Global_I2C_Config[2] = {0};



/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
#define I2C1_INDEX		0
#define I2C2_INDEX		1

/*
 * =======================================================================================
 * 							             APIs
 * =======================================================================================
 */

/**================================================================
 * @Fn            -MCAL_I2C_Init
 * @brief         -Initialize the I2C peripheral with the given settings.
 * @param [in]    -I2Cx: Select which I2C instance to use (e.g., I2C1 or I2C2).
 * @param [in]    -I2C_InitStruct: I2C configuration settings (clock speed, ACK, etc.).
 * @retval        -None
 * @note          -This function must be called before using the I2C.
 */
void MCAL_I2C_Init(I2C_t* I2Cx, I2C_Config_t* I2C_InitStruct)
{
	uint16_t tempreg = 0 , freqRenge = 0;
	uint32_t pclk1 = 8000000;
	uint16_t result;

	//Enable RCC
	if(I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct;
		RCC_I2C1_CLK_EN();
	}
	else
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct;
		RCC_I2C2_CLK_EN();
	}

	if(I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
	{
		//----------------------------------Init Timing---------------------------------------
		//I2C_CR2.FREQ[5:0]: Peripheral clock frequency
		tempreg = I2Cx->CR2;
		//CLear Frequency FREQ[5:0] bits
		tempreg &= ~(I2C_CR2_FREQ);
		//Get Pclk1 Frequency value
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		//Set Frequency bits depending on pclk1 value
		freqRenge = (uint16_t) (pclk1 / 1000000);
		//write to I2Cx CR2
		tempreg |= freqRenge;
		//--configure the clock control registers (I2C_CCR)
		//Disable the selected I2C Peripheral to configuration Time
		I2Cx->CR1 &= ~(I2C_CR1_PE);
		tempreg = 0;

		//Configure Speed
		if((I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K))
		{
			//standard mode speed calculate
			//	Tclk/2 = CCR * Tpclk1
			//  CCR = Tclk / (2* I2C_ClockSpeed)
			//	CCR = Fpclk / (2* I2C_ClockSpeed)
			result = (uint16_t) (pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));
			tempreg |= result;
			//write to I2Cx CCR
			I2Cx->CCR = tempreg;

			//I2C_TRSE Configuration
			//For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			//If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//therefore the TRISE[5:0] bits must be programmed with 09h.
			I2Cx->TRISE = freqRenge + 1;
		}
		else
		{
			// fast mode not supported
		}
		//---------------------- I2Cx CR1 Configuration ----------------------
		tempreg = I2Cx->CR1;

		tempreg |= (uint16_t)(I2C_InitStruct->I2C_ACK_Control | I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->StretchMode | I2C_InitStruct->I2C_Mode);

		I2Cx->CR1 = tempreg;

		//--------------------- I2Cx OAR1 & OAR2 Configuration ----------------------
		tempreg = 0;
		if(I2C_InitStruct->I2C_Slave_Address.Dual_ADD_ack == 1)
		{
			tempreg = I2C_OAR2_ENDUAL;
			tempreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tempreg;
		}
		tempreg = 0;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_Mode;
		I2Cx->OAR1 = tempreg;

	}
	else
	{
		//SMBUS Not Supported
	}

	//Interrupt Mode (Slave Mode) //Check CallBack Pointer != NULL
	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL) //that enable slave IRQ states Mode
	{
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_EN;
			NVIC_IRQ32_I2C1_ER_EN;
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_EN;
			NVIC_IRQ34_I2C2_ER_EN;
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	//Enable the selected I2C prepheral
	I2Cx->CR1 |= I2C_CR1_PE;
}


/**================================================================
 * @Fn            -MCAL_I2C_DeInit
 * @brief         -Reset the I2C peripheral and disable its clock.
 * @param [in]    -I2Cx: Select which I2C instance to reset (e.g., I2C1 or I2C2).
 * @retval        -None
 * @note          -After calling this, the I2C will stop working until re-initialized.
 */
void MCAL_I2C_DeInit(I2C_t* I2Cx)
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_Reset();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_Reset();
	}
}


/**================================================================
 * @Fn            -MCAL_I2C_GPIO_Set_Pins
 * @brief         -Configure the SDA and SCL pins for the selected I2C peripheral.
 * @param [in]    -I2Cx: Choose which I2C instance (e.g., I2C1 or I2C2).
 * @retval        -None
 * @note          -Must be called before I2C initialization.
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_t* I2Cx)
{
	GPIO_Config_t pincfg;

	if(I2Cx == I2C1)
	{
		//PB6 : I2C_SCL
		//PB7 : I2C_SDA

		pincfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pincfg.GPIO_PinNumber = GPIO_PIN_6;
		pincfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		pincfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pincfg.GPIO_PinNumber = GPIO_PIN_7;
		pincfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pincfg);
	}
	else if(I2Cx == I2C2)
	{
		//PB10 : I2C_SCL
		//PB11 : I2C_SDA

		pincfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pincfg.GPIO_PinNumber = GPIO_PIN_10;
		pincfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pincfg);

		pincfg.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pincfg.GPIO_PinNumber = GPIO_PIN_11;
		pincfg.GPIO_PinSpeed = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &pincfg);
	}
}


/**================================================================
 * @Fn            -MCAL_I2C_Master_TX
 * @brief         -Send data from I2C Master to a specific Slave device.
 * @param [in]    -I2Cx: I2C instance (I2C1 or I2C2).
 * @param [in]    -devAdder: 7-bit or 10-bit slave address.
 * @param [in]    -dataOut: pointer to the data buffer to send.
 * @param [in]    -dataLen: number of bytes to send.
 * @param [in]    -Stop: Stop condition configuration (send stop or not).
 * @param [in]    -Start: Repeated start condition configuration.
 * @retval        -None
 * @note          -This function generates START, sends data, and optionally generates STOP.
 */
void MCAL_I2C_Master_TX(I2C_t* I2Cx, uint16_t devAdder, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start)
{
	int i=0;
	//todo Support Timeout (Configure timer working for specific duration rise interrupt)
	//timer_interrupt(){flag=1}
	//so any code exist in while (check flag || any polling condition)
	//1.Set the Start bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateStart(I2Cx, ENABLE, Start);
	//2.Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3.Send Address
	I2C_SendAddress(I2Cx, devAdder, I2C_Direction_Transmitter);

	//4.Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	//5.TRA, MSL, TXE, BUSY flags //in Status REG
	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	for(i = 0 ; i < dataLen ; i++)
	{
		//Write in the DR register the data to be sent
		I2Cx->DR = dataOut[i];
		//6.Wait for EV8
		// EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_GetFlagStatus(I2Cx, EV8));
	}

	//7.Wait EV8_2
	// EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	//while(!I2C_GetFlagStatus(I2Cx, EV8_2));

	//8.Send Stop condition
	if(Stop != Without_Stop) I2C_GenerateSTOP(I2Cx, ENABLE);
}

void I2C_SendAddress(I2C_t* I2Cx , uint16_t Address, I2C_Direction Direction)
{
	Address = (Address << 1);

	if(Direction != I2C_Direction_Transmitter)
	{
		//set the address bit0 for read
		Address |= 1<<0;
	}
	else
	{
		//reset the address bit0 for write
		Address &= ~(1<<0);
	}

	//send the address
	I2Cx->DR = Address;
}


void I2C_GenerateStart(I2C_t* I2Cx, FunctionalState NewStart, Repeated_Start Start)
{
	if(Start != repeated_Start)
	{
		//Check if the Bus is idle
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	}
	//Bit 8 START: Start generation
	//This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//In Master Mode:
	//0: No Start generation
	//1: Repeated start generation
	//In Slave mode:
	//0: No Start generation
	//1: Start generation when the bus is free
	if(NewStart != DISABLE) I2Cx->CR1 |= I2C_CR1_START;
	else I2Cx->CR1 &= ~(I2C_CR1_START);

}

void I2C_GenerateSTOP(I2C_t* I2Cx, FunctionalState NewState)
{
	// Bit 9 STOP: Stop generation
	if(NewState == ENABLE)
	{
		//Generate a STOP Condition
		I2Cx->CR1 |= I2C_CR1_STOP;
		I2Cx->SR2 &= ~(I2C_SR2_BUSY);
	}
	else
	{
		//Disable the STOP Condition Generation
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}

}


FlagStatus I2C_GetFlagStatus(I2C_t* I2Cx, Status Flag)
{
	volatile uint32_t dummyRead;
	uint32_t flag1 , flag2 , lastEvent=0;
	FlagStatus bitStatus = RESET;

	switch(Flag)
	{
	case I2C_FLAG_BUSY:
		//0: No communication on the bus
		//1: Communication ongoing on the bus– Set by hardware on detection of SDA or SCL low – cleared by hardware on detection of a Stop condition.
		//It indicates a communication in progress on the bus. This information is still updated when
		//the interface is disabled (PE=0).
		if((I2Cx->SR2) & (I2C_SR2_BUSY)) bitStatus = SET;
		else bitStatus = RESET;
		break;
	case EV5:
		// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//Bit 0 SB: Start bit (Master mode)
		//0: No Start condition
		//1: Start condition generated.– Set when a Start condition generated.– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//hardware when PE=0
		if((I2Cx->SR1) & (I2C_SR1_SB)) bitStatus = SET;
		else bitStatus = RESET;
		break;
	case EV6:
		// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		// Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		if((I2Cx->SR1) & (I2C_SR1_ADDR)) bitStatus = SET;
		else bitStatus = RESET;
		dummyRead = I2Cx->SR2;
		break;
	case MASTER_BYTE_TRANSMITTING:
		//read the I2Cx status register
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2<<16;
		//get the last event value from I2C status register
		lastEvent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
		//Check Whether the last event is equal to I2C_EVENT
		if((lastEvent & Flag) == Flag)
		{
			//SUCCRSS: last event is equal to I2C_EVENT
			bitStatus = SET;
		}
		else
		{
			//ERROR: last event is equal to I2C_EVENT
			bitStatus = RESET;
		}
		break;
	case EV8_1:
	case EV8:
		//Bit 7 TxE: Data register empty (transmitters)
		//0: Data register not empty
		//1: Data register empty
		if((I2Cx->SR1) & (I2C_SR1_TXE)) bitStatus = SET;
		else bitStatus = RESET;
		break;
	case EV7:
		//Bit 6 RxNE: Data register not empty (receivers)
		//0: Data register empty
		//1: Data register not empty– Set when data register is not empty in receiver mode. RxNE is not set during address phase.– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//RxNE is not set in case of ARLO event.
		if((I2Cx->SR1) & (I2C_SR1_RXNE)) bitStatus = SET;
		else bitStatus = RESET;
		break;
	}

	return bitStatus;
}

/**================================================================
 * @Fn            -MCAL_I2C_Master_RX
 * @brief         -Receive data from a specific I2C Slave device to the Master.
 * @param [in]    -I2Cx: I2C instance (I2C1 or I2C2).
 * @param [in]    -devAdder: 7-bit or 10-bit slave address.
 * @param [out]   -dataOut: pointer to the buffer where received data will be stored.
 * @param [in]    -dataLen: number of bytes to receive.
 * @param [in]    -Stop: Stop condition configuration (send stop or not).
 * @param [in]    -Start: Repeated start condition configuration.
 * @retval        -None
 * @note          -This function generates START, receives data, and optionally generates STOP.
 */
void MCAL_I2C_Master_RX(I2C_t* I2Cx, uint16_t devAdder, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_INDEX :  I2C2_INDEX;

	int i=0;
	//todo Support Timeout (Configure timer working for specific duration rise interrupt)
	//timer_interrupt(){flag=1}
	//so any code exist in while (check flag || any polling condition)
	//1.Set the Start bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateStart(I2Cx, ENABLE, Start);
	//2.Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3.Send Address
	I2C_SendAddress(I2Cx, devAdder, I2C_Direction_Reciever);

	//4.Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));
	I2C_AcknowledgeConfig(I2Cx , ENABLE);

	if(dataLen)
	{
		//read the data until len become zero
		for(i = dataLen ; i > 1 ; i--)
		{
			//wait until RXNE becomes 1
			while(!I2C_GetFlagStatus(I2Cx, EV7));
			//read the data from register in to buffer
			*dataOut = I2Cx->DR;
			//increment the buffer address
			dataOut++;
		}
		I2C_AcknowledgeConfig(I2Cx , DISABLE);
		while(!I2C_GetFlagStatus(I2Cx, EV7));
		*dataOut = I2Cx->DR;
	}

	if(Stop != Without_Stop)
	{
		//send stop condition
		I2C_GenerateSTOP(I2Cx, ENABLE);
	}

	//re-enable ACKing
	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx , ENABLE);
	}
}



/**================================================================
* @Fn            -MCAL_I2C_SlaveSendData
* @brief         -Send a single byte of data from the I2C Slave to the Master.
* @param [in]    -I2Cx: I2C instance (I2C1 or I2C2).
* @param [in]    -data: Byte to send.
* @retval        -None
* @note          -Used when the slave is addressed by the master for data transmission.
*/
void MCAL_I2C_SlaveSendData(I2C_t* I2Cx, uint8_t data)
{
	I2Cx->DR = data;
}


/**================================================================
* @Fn            -MCAL_I2C_SlaveReceiveData
* @brief         -Receive a single byte of data by the I2C Slave from the Master.
* @param [in]    -I2Cx: I2C instance (I2C1 or I2C2).
* @retval        -The received byte.
* @note          -Call this function when the master requests data from the slave.
*/
uint8_t MCAL_I2C_SlaveReceiveData(I2C_t* I2Cx)
{
	return (uint8_t) I2Cx->DR;
}

void I2C1_EV_IRQHandler (void)
{
	volatile uint32_t dummy_read = 0;
	I2C_t* I2Cx = I2C1;
	//Interrupt handling for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;

	temp1 = I2Cx->CR2 & (I2C_CR2_ITEVTEN);
	temp2 = I2Cx->CR2 & (I2C_CR2_ITBUFEN);
	temp3 = I2Cx->SR1 & (I2C_SR1_STOPF);

	//Handle for interrupt generated by STOPF event
	//Stop detection flag is applicable only slave mode
	if(temp1 && temp3)
	{
		//STOP flag is set
		//Clear the STOPF (i.e 1) read SR1 2)Write to CR1
		I2Cx->CR1 |=0x0000;
		Slave_States(I2Cx, I2C_EV_STOP);
	}
	//---------------------------------------
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR);
	//Handle for interrupt generated by ADDR event
	//When master mode : Address is sent
	//when slave mode : address matched with own address
	if(temp1 && temp3)
	{
		//interrupt is generated because of ADDR event
		//check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//master
		}
		else
		{
			//slave mode
			//clear the ADDR flag (read SR1 , read SR2)
			dummy_read = I2Cx->SR1;
			dummy_read = I2Cx->SR2;
			Slave_States(I2Cx, I2C_EV_ADDR_Matched);
		}
	}
	//----------------------------------------------
	temp3 = I2Cx->SR1 & (I2C_SR1_TXE);
	//handle for interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		//check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}
		else
		{
			Slave_States(I2Cx, I2C_EV_DATA_REQ);
		}
	}

}
void I2C1_ER_IRQHandler (void)
{

}



void Slave_States(I2C_t* I2Cx, Slave_State state)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_INDEX :  I2C2_INDEX;

	switch(state)
	{
	case I2C_ERROR_AF:
		//make sure that the slave is really transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//slave shouldn't send anything else
		}
		break;

	case I2C_EV_STOP:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_STOP);
		}
		break;

	case I2C_EV_ADDR_Matched:
		//notify APP that the stop condition is sent by the master
		Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
		break;

	case I2C_EV_DATA_REQ:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//the APP layer should send data (I2C_SlaveSendData) in this state
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
		}
		break;
	case I2C_EV_DATA_RCV:
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & (I2C_SR2_TRA)))
		{
			//the APP layer should send data (I2C_SlaveSendData) in this state
			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
		}
		break;
	}

}


void I2C_AcknowledgeConfig(I2C_t* I2Cx  , FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		//enable the acknowledgment
		I2Cx->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		//disable the acknowledgment
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}










