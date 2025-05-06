#include <stdint.h>
#include "stm32f103x6.h"
#include "Stm32_F103C6_USART_driver.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "Stm32_F103C6_RCC_driver.h"
#include "lcd.h"


unsigned char ch;

void UART_IRQ_CallBack()
{
	MCAL_UART_ReceiveData(USART1, &ch, disable);
	MCAL_UART_SendData(USART1, &ch, enable);
}

int main(void)
{
	//enable Clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_GPIOC_CLK_EN();

	UART_Config_t uartCFG;
	uartCFG.BaudRate = UART_BaudRate_115200;
	uartCFG.HwFlow_CTL = UART_HwFlow_CTL_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uartCFG.P_IRQ_CallBack = UART_IRQ_CallBack;
	uartCFG.Payload_Length = UART_Payload_Length_8B;
	uartCFG.StopBits = UART_StopBits_1;
	uartCFG.USART_Mode = UART_Mode_TX_RX;
	uartCFG.parity = UART_parity_NONE;

	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1);

	//loop forever
    while(1)
    {

    }
}
