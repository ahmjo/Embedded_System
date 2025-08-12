#include "MCAL/Inc/I2C.h"
#include <avr/io.h>
#include <util/delay.h>

#define I2C_MODE_MASTER
//#define I2C_MODE_SLAVE



int main (void)
{
#ifdef I2C_MODE_MASTER
	 I2C_config_t I2C_Config = {
		 .Own_Address = 0x00,
		 .Speed_MODE = I2C_Speed_MODE_100,
		 .IRQ_EN = I2C_IRQ_ENABLE_Disable,
		 .Prescaler = I2C_Prescaler_1,
		 .P_IRQ_CALL = NULL
	 };

	 MCAL_I2C_Init(&I2C_Config);
	 DDRA = 0xFF;

	

	 while (1) {
		uint8_t received_data = MCAL_I2C_Master_RX(0xD0);
		PORTA = received_data;
		_delay_ms(500);
	 }
	
#elif defined(I2C_MODE_SLAVE)
	I2C_config_t I2C_Config = {
		.Own_Address = 0xD0,          
		.Speed_MODE = I2C_Speed_MODE_100, 
		.IRQ_EN = I2C_IRQ_ENABLE_Disable, 
		.Prescaler = I2C_Prescaler_1,   
		.P_IRQ_CALL = NULL          
	};
	MCAL_I2C_Init(&I2C_Config);
	
	uint8_t data = 0 ;
	
	while(1)
	{
		 MCAL_I2C_Slave_TX(data);
		 data++;
		 _delay_ms(500);
	}
#endif
	return 0;
}
