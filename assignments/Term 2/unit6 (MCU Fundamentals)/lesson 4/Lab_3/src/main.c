#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BET(add,bit) add |= (1<<bit)
#define RESET_BET(add,bit) add &= ~(1<<bit)
#define TOGGLE_BET(add,bit) add ^= (1<<bit)
#define READ_BET(add,bit) ((add & (1<<bit))>>bit)


int main(void){
	SET_BET(MCUCR,0);
	RESET_BET(MCUCR,1);
	SET_BET(MCUCR,2);
	SET_BET(MCUCR,3);
	
	RESET_BET(MCUSR,6);
	
	SET_BET(GICR,5);
	SET_BET(GICR,6);
	SET_BET(GICR,7);
	
	SET_BET(DDRD,5);
	SET_BET(DDRD,6);
	SET_BET(DDRD,7);
	
	sei();
	
	while(1){
		RESET_BET(PORTD,5);
		RESET_BET(PORTD,6);
		RESET_BET(PORTD,7);
	}
}

ISR(INT0_vect){
	SET_BET(PORTD,5);
	_delay_ms(100);
	RESET_BET(PORTD,5);
}

ISR(INT1_vect){
	SET_BET(PORTD,6);
	_delay_ms(100);
	RESET_BET(PORTD,6);
}

ISR(INT2_vect){
	SET_BET(PORTD,7);
	_delay_ms(100);
	RESET_BET(PORTD,7);
}