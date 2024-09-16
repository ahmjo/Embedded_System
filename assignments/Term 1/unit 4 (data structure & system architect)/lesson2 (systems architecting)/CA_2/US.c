#include "stdio.h"
#include "US.h"

int US_distance = 0;

void (*US_state)();

void US_init(){
    printf("US_init\n");
}

int random_Number(int l, int r, int count) {
    int rand_num = 0;
    for (int i = 0; i < count; i++) {
        rand_num = (rand() % (r - l + 1)) + l;  
    }
    return rand_num;
}

STATE_define(US_busy){
    CA_STATE_id = US_busy;
    US_distance = random_Number(45,55,1);
    printf("\nUS_busy state : distance : %d \n", US_distance);
    US_distace_set (US_distance);
    US_state = STATE(US_busy);
    US_distace_set(US_distance);
}