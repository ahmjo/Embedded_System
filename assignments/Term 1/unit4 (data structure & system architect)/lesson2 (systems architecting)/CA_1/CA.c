#include "stdio.h"
#include "CA.h"
int speed = 0;
int distance = 0;
int threshold = 50;

void (*CA_state)();

int random_Number(int l, int r, int count) {
    int rand_num = 0;
    for (int i = 0; i < count; i++) {
        rand_num = (rand() % (r - l + 1)) + l;  
    }
    return rand_num;
}

STATE_define(CA_waiting){
    CA_STATE_id = CA_waiting;
    speed = 0;
    distance = random_Number(45,55,1);
    (distance <= threshold)? (CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));
    printf("\nWaiting state : distance : %d, speed : %d \n", distance, speed);
}
STATE_define(CA_driving){
    CA_STATE_id = CA_driving;
    speed = 30;
    distance = random_Number(45,55,1);
    (distance <= threshold)? (CA_state=STATE(CA_waiting)):(CA_state=STATE(CA_driving));
    printf("\nDriving state : distance : %d, speed : %d \n", distance, speed);
}