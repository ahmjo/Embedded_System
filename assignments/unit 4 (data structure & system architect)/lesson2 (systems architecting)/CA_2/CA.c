#include "stdio.h"
#include "CA.h"
int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;

void (*CA_state)();

void US_distace_set (int d){
    CA_distance = d;
    (CA_distance <= CA_threshold)? (CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));
    printf("US -----distance=%d----->CA\n",CA_distance);
}

STATE_define(CA_waiting){
    CA_STATE_id = CA_waiting;
    printf("\nCA_waiting state : distance : %d, speed : %d \n", CA_distance, CA_speed);
    CA_speed = 0;
    DC_motor (CA_speed);
}
STATE_define(CA_driving){
    CA_STATE_id = CA_driving;
    printf("\nCA_driving state : distance : %d, speed : %d \n", CA_distance, CA_speed);
    CA_speed = 30;
    DC_motor (CA_speed);
}