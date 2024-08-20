#include "stdint.h"

#define SYSCTL_RCGC2_R      (*(volatile unsigned long *) 0x400FE108)
#define GPIO_PORTF_DIR_R    (*(volatile unsigned long *) 0x40025400)
#define GPIO_PORTF_DEN_R    (*(volatile unsigned long *) 0x4002551C)
#define GPIO_PORTF_DATA_R   (*(volatile unsigned long *) 0x400253FC)

int main() {
    volatile unsigned long delay_counter;
    SYSCTL_RCGC2_R = 0x20;
    for (delay_counter = 0; delay_counter < 200 ; delay_counter++);
    GPIO_PORTF_DIR_R |= 1<<3 ;
    GPIO_PORTF_DEN_R |= 1<<3 ;
    while(1){
        GPIO_PORTF_DATA_R |= 1<<3 ; 
        for (delay_counter = 0; delay_counter < 20000 ; delay_counter++);
        GPIO_PORTF_DATA_R &= ~(1<<3) ; 
        for (delay_counter = 0; delay_counter < 20000 ; delay_counter++);
    }
    return 0;
}