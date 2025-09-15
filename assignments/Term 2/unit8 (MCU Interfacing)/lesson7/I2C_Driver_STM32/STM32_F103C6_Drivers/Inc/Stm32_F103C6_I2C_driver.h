/*
 * Stm32_F103C6_I2C_driver.h
 *
 *  Created on: Aug 19, 2025
 *      Author: AAMA
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

//Includes
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"


struct S_I2C_Slave_Device_Address
{
	uint16_t Dual_ADD_ack;	//1-Enable  0- Disable
	uint16_t Primary_slave_address;
	uint16_t Secondary_slave_address;
	uint32_t I2C_Addressing_Slave_Mode; //@ref I2C_Addressing_Slave
};

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ, //the APP layer should send the data
	I2C_EV_DATA_RCV	// the APP layer should read the data
}Slave_State;

typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	repeated_Start
}Repeated_Start;

typedef enum
{
	DISABLE = 0,
	ENABLE = 1
}FunctionalState;

typedef enum
{
	RESET = 0,
	SET = 1
}FlagStatus;

typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5, // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6, // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV8, // EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1, //EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8_2,// EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	EV7,
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070000) //TRA, MSL, TXE, BUSY
}Status;

typedef enum
{
	I2C_Direction_Transmitter = 0,
	I2C_Direction_Reciever = 1, // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
}I2C_Direction;

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING		((uint32_t)0x00070000)//TRA, MSL, TXE, BUSY



typedef struct
{
	uint32_t								I2C_ClockSpeed; 	//Specifies the Clock Freq
																//this parameter must be set to @ref I2C_SCLK

	uint32_t								StretchMode;		//this parameter must be set to @ref I2C_StretchMode

	uint32_t								I2C_Mode;			//Specifies the I2C Mode
																//this parameter must be set to @ref I2C_Mode

	struct S_I2C_Slave_Device_Address		I2C_Slave_Address;

	uint32_t								I2C_ACK_Control;	//Enables or disales the acknowladgment
																//this parameter must be set to @ref I2C_ACK

	uint32_t								General_Call_Address_Detection; //this parameter must be set to @ref I2C_ENGC

	void(* P_Slave_Event_CallBack)(Slave_State state);
}I2C_Config_t;

//--------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*

//@ref I2C_SCLK
//Standard Speed (up to 100 kHz) – Fast Speed (up to 400 kHz)
//-to configure Clock
//--I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//--configure the clock control registers
	//Thigh = CCR * Tpclk1 // SM or FM
//--configure the rise time register  I2C_TRISE
#define I2C_SCLK_SM_50K			(0x50000U)
#define I2C_SCLK_SM_100K		(100000U)
#define I2C_SCLK_FM_200K		(200000U) // Fast Mode Not Supported yet
#define I2C_SCLK_FM_400K		(400000U)


//@ref I2C_StretchMode
//in I2C_CR1
//0: CLock Stretching enable
//1: Clock Stretching disable
#define I2C_StretchMode_Enable		(0x00000000U)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH


//@ref I2C_Mode
//Bit 1 SMBUS: SMBus mode
// 0: I2C mode
// 1: SMBus mode
#define I2C_Mode_I2C		0U
#define I2C_Mode_SMBus		I2C_CR1_SMBUS


//@ref I2C_Addressing_Slave
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
#define I2C_Addressing_Slave_7Bit			0x00000000U
#define I2C_Addressing_Slave_10Bit			(uint16_t)(1<<15)


//@ref I2C_ACK
//I2C_CR1
//Bit 10 ACK: Acknowledge enable
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable			(I2C_CR1_ACK)
#define I2C_ACK_Disable			((uint32_t)0x0000)


//@ref I2C_ENGC
//I2C_CR1
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_ENGC_Enable			I2C_CR1_ENGC
#define I2C_ENGC_Disable		0x00000000U


/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_I2C_Init(I2C_t* I2Cx, I2C_Config_t* I2C_InitStruct);
void MCAL_I2C_DeInit(I2C_t* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_t* I2Cx);

//Master Polling Mechanism
void MCAL_I2C_Master_TX(I2C_t* I2Cx, uint16_t devAdder, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_t* I2Cx, uint16_t devAdder, uint8_t* dataOut, uint32_t dataLen, Stop_Condition Stop, Repeated_Start Start);



//Slave Interrupt Mechanism
void MCAL_I2C_SlaveSendData(I2C_t* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_t* I2Cx);


//Generic APIs
void I2C_GenerateStart(I2C_t* I2Cx, FunctionalState NewStart, Repeated_Start Start);
void I2C_GenerateSTOP(I2C_t* I2Cx, FunctionalState NewState);
FlagStatus I2C_GetFlagStatus(I2C_t* I2Cx, Status Flag);
void I2C_SendAddress(I2C_t* I2Cx , uint16_t Address, I2C_Direction Direction);//I2C_Direction R=1  W=0
void I2C_AcknowledgeConfig(I2C_t* I2Cx  , FunctionalState NewState);



#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
