/*
 * Stm32_F103C6_SPI_driver.h
 *
 *  Created on: Jun 17, 2025
 *      Author: AAMA
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

//Includes
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"

struct S_IRQ_SRC
{
	uint8_t TXE:1; //Tx buffer empty interrupt
	uint8_t RXNE:1; //Rx buffer empty interrupt
	uint8_t ERRI:1;//Error interrupt
	uint8_t Reserved;
};

//Configuration Register
typedef struct
{
	uint16_t	Device_Mode; //Specifies the SPI operating mode @ref SPI_Device_Mode
	uint16_t 	Communication_Mode; //Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16_t	Frame_format; //Specifies LSB or MSB @ref SPI_Frame_Format
	uint16_t	DataSize; //@ref SPI_DataSize
	uint16_t	CLKPolarity; //@ref SPI_CLKPolarity
	uint16_t 	CLKPhase; //@ref SPI_CLKPhase
	uint16_t	NSS; //NSS Signal is manage by -HW (NSS PIN) -SW using the SSI bitenable @ref SPI_NSS
	uint16_t	SPI_BandRatePrescaler; //used to configure the Tx & Rx SCK clock. @ref SPI_BandRatePrescaler
										//@note the communication speed is derived from the master clock.
										  // the slave clock doesn't need to be set
										//Take care you have to configure RCC to enter the correct clock
	uint16_t	IRQ_Enable; //@ref SPI_IRQ_Enable
	void(*P_IRQ_CallBack)(struct S_IRQ_SRC IRQ_SRC); //Set the C func. which will be called once the IRQ happen
}SPI_Config_t;

//--------------------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*

//@ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE		(0x00000000U)
#define SPI_Device_Mode_MASTER		(0x1U<<2)

//@ref SPI_Communication_Mode
//all this in CR1 Register
#define SPI_DIRECTION_2LINES						(0x00000000U)//-2Lines -Full Duplex
#define SPI_DIRECTION_2LINES_RXONLY					(0x1U<<10)  //Bit 10 RXONLY: Receive-only mode
#define SPI_DIRECTION_1LINES_receive_only			(0x1U<<15)  //Bit 15 BIDIMODE:  bidirectional data mode selected
#define SPI_DIRECTION_1LINES_transmit_only			((0x1U<<15)|(0x1U<<14))//Bit 15 BIDIMODE:  bidirectional data mode selected & Bit14 BIDOPE: Output enabled (transmit-only mode)

//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB	(0x00000000U)
#define SPI_Frame_Format_LSB	(0x1U<<7)

//@ref SPI_DataSize
#define SPI_DataSize_8BIT		(0x00000000U)
#define SPI_DataSize_16BIT		(0x1U<<11)   //CR1.	Bit 11 DFF: Data frame format

//@ref SPI_CLKPolarity
#define SPI_CLKPolarity_LOW_When_Idle		(0x00000000U)
#define SPI_CLKPolarity_HIGH_When_Idle		(0x1U<<1)

//@ref SPI_CLKPhase
#define SPI_CLKPhase_1EDGE		(0x00000000U)
#define SPI_CLKPhase_2EDGE		(0x1U<<0)

//@ref SPI_NSS		SPI Slave Select Management
//========================NSS======================
//Hardware
#define SPI_NSS_HW_Slave 					(0x00000000U)
#define SPI_NSS_HW_Master_SS_OP_EN			(0x1U<<2)		//in SPI_CR2 Bit2 SSDE: SS output enable
#define SPI_NSS_HW_Master_SS_OP_Disable		5U	//in SPI_CR2 Bit2 SSDE: SS output disable
//NSS is driven by Software (Master or Slave)
#define SPI_NSS_SW_NSSInternalSW_Reset		(0x1U<<9)
#define SPI_NSS_SW_NSSInternalSW_set		((0x1U<<9)|(0x1U<<8))//Master or Slave
//================================================

//@ref SPI_BandRatePrescaler
#define SPI_BandRatePrescaler_2			(0x00000000U)
#define SPI_BandRatePrescaler_4			(0b001U<<3)
#define SPI_BandRatePrescaler_8			(0b010U<<3)
#define SPI_BandRatePrescaler_16		(0b011U<<3)
#define SPI_BandRatePrescaler_32		(0b100U<<3)
#define SPI_BandRatePrescaler_64		(0b101U<<3)
#define SPI_BandRatePrescaler_128		(0b110U<<3)
#define SPI_BandRatePrescaler_256		(0b111U<<3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE				(0x00000000U)
#define SPI_IRQ_Enable_TXEIE			(0x1U<<7)	//CR2 Bit7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE			(0x1U<<6)	//CR2 Bit6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE			(0x1U<<5)	//CR2 Bit 5 ERRIE: Error interrupt enable


enum PollingMechism
{
	PollingEnable,
	PollingDisable
};

/*
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_SPI_Init(SPI_t* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_t* SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_t* SPIx);

void MCAL_SPI_SendData(SPI_t* SPIx,const uint16_t* pTxBuffer, enum PollingMechism PollingEn);
void MCAL_SPI_ReceiveData(SPI_t* SPIx, uint16_t* pRxBuffer, enum PollingMechism PollingEn);
void MCAL_SPI_Tx_Rx(SPI_t* SPIx, uint16_t* pTxBuffer, enum PollingMechism PollingEn);




#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
