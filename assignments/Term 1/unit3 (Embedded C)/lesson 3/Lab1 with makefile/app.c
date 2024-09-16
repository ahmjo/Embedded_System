#include "uart.h"

unsigned char string_buffer[100]="learn-in-depth:<Ahmed>";
void main(void){
	uart_send_string(string_buffer);
}