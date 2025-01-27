/*
 * STM32F103C6_GPIO_drivers.h
 *
 *  Created on: Jan 27, 2025
 *      Author: AAMA
 */

#ifndef INC_STM32F103C6_GPIO_DRIVERS_H_
#define INC_STM32F103C6_GPIO_DRIVERS_H_

//Includes
#include "STM32F103X6.h"


//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	//Specifies the GPIO Pins needed to be configured
	//This parameter must be a value of @ref GPIO_PIN_DEFINE
	uint16_t GPIO_PinNumber;

	//Specifies the MODE of the pins to be configured
	//This parameter must be a value of @ref GPIO_MODE_DEFINE
	uint16_t GPIO_PinMode;

	//Specifies the SPEED of the pins to be configured
	//This parameter must be a value of @ref GPIO_SPEED_DEFINE
	uint16_t GPIO_PinSpeed;
}GPIO_Config_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*

//@ref GPIO_PIN_DEFINE
#define GPIO_PIN_0					((uint16_t)0x0001)		/* PIN 00 selected */
#define GPIO_PIN_1					((uint16_t)0x0002)		/* PIN 01 selected */
#define GPIO_PIN_2					((uint16_t)0x0004)		/* PIN 02 selected */
#define GPIO_PIN_3					((uint16_t)0x0008)		/* PIN 03 selected */
#define GPIO_PIN_4					((uint16_t)0x0010)		/* PIN 04 selected */
#define GPIO_PIN_5					((uint16_t)0x0020)		/* PIN 05 selected */
#define GPIO_PIN_6					((uint16_t)0x0040)		/* PIN 06 selected */
#define GPIO_PIN_7					((uint16_t)0x0080)		/* PIN 07 selected */
#define GPIO_PIN_8					((uint16_t)0x0100)		/* PIN 08 selected */
#define GPIO_PIN_9					((uint16_t)0x0200)		/* PIN 09 selected */
#define GPIO_PIN_10					((uint16_t)0x0400)		/* PIN 10 selected */
#define GPIO_PIN_11					((uint16_t)0x0800)		/* PIN 11 selected */
#define GPIO_PIN_12					((uint16_t)0x1000)		/* PIN 12 selected */
#define GPIO_PIN_13					((uint16_t)0x2000)		/* PIN 13 selected */
#define GPIO_PIN_14					((uint16_t)0x4000)		/* PIN 14 selected */
#define GPIO_PIN_15					((uint16_t)0x8000)		/* PIN 15 selected */
#define GPIO_PIN_ALL				((uint16_t)0xFFFF)		/* All pins selected */

//@ref GPIO_MODE_DEFINE
/*
 * 0: Analog mode
 * 1: Floating input (reset state)
 * 2: Input with pull-up
 * 3: Input with pull-down
 * 4: General purpose output push-pull
 * 5: General purpose output Open-drain
 * 6: Alternate function output Push-pull
 * 7: Alternate function output Open-drain
 * 8: Alternate function input
 */
#define GPIO_MODE_ANALOG				0x00000000U		/* Analog mode */
#define GPIO_MODE_INPUT_FLO				0x00000001U		/* Floating input */
#define GPIO_MODE_INPUT_PU				0x00000002U		/* Input pull-up */
#define GPIO_MODE_INPUT_PD				0x00000003U		/* Input pull-down */
#define GPIO_MODE_OUTPUT_PP				0x00000004U		/* output push-pull */
#define GPIO_MODE_OUTPUT_OD				0x00000005U		/* output Open-drain */
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006U		/* Alternate function output Push-pull */
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007U		/* Alternate function output Open-drain */
#define GPIO_MODE_INPUT_AF				0x00000008U		/* Alternate function input */


//@ref GPIO_MODE_DEFINE
/*
 * 1: Output mode, max speed 10 MHz.
 * 2: Output mode, max speed 2 MHz.
 * 3: Output mode, max speed 50 MHz.
*/
#define GPIO_SPEED_10MHz				0x00000001u		/* Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2MHz					0x00000002u		/* Output mode, max speed 02 MHz. */
#define GPIO_SPEED_50MHz				0x00000003u		/* Output mode, max speed 50 MHz. */


//@ref GPIO_PIN_STATE
#define GPIO_PIN_SET					1
#define GPIO_PIN_RESET					0


//@ref GPIO_LOCK_STATE
#define GPIO_LOCK_OK					0
#define GPIO_LOCK_ERROR					1


//-*-*-*-*-*-*-*-*-*-*-*-
//APIs
//-*-*-*-*-*-*-*-*-*-*-*
//Initialize & DeInitialize GPIO
void MCAL_GPIO_Init(GPIO_t *GPIOx,GPIO_Config_t *pin_config);
void MCAL_GPIO_DeInit(GPIO_t *GPIOx,GPIO_Config_t *pin_config);

//READ PIN or PORT
uint8_t MCAL_GPIO_READ_Pin(GPIO_t *GPIOx,uint16_t pinnumber);
uint16_t MCAL_GPIO_READ_Port(GPIO_t *GPIOx);

//WRITE PIN or PORT
void MCAL_GPIO_WRITE_Pin(GPIO_t *GPIOx,uint16_t pinnumber,uint8_t value);
void MCAL_GPIO_WRITE_Port(GPIO_t *GPIOx,uint8_t value);

//TOGGLE PIN
void MCAL_GPIO_TOGGLE_Pin(GPIO_t *GPIOx,uint16_t pinnumber);

//LOCK PIN
uint8_t MCAL_GPIO_LOCK_Pin(GPIO_t *GPIOx,uint16_t pinnumber);


#endif /* INC_STM32F103C6_GPIO_DRIVERS_H_ */
