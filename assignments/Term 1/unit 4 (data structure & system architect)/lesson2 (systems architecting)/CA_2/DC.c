#include "stdio.h"
#include "DC.h"

int DC_speed = 0;

void (*DC_state)();

void DC_init(){
    printf("DC_init\n");
}

void DC_motor (int s){
    DC_speed=s;
    DC_state=STATE(DC_busy);
    printf("CA-----speed=%d----->DC\n",DC_speed);
}

STATE_define(DC_idle){
    DC_STATE_id = DC_idle;
    DC_state = STATE(DC_idle);
    printf("\nDC_idle state : speed : %d \n", DC_speed);
}
STATE_define(DC_busy){
    DC_STATE_id = DC_busy;
    DC_state = STATE(DC_idle);
    printf("\nDC_busy state : speed : %d \n", DC_speed);
}