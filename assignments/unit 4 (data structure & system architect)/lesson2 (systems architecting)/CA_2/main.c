#include "CA.c"
#include "DC.c"
#include "US.c"

void setup(){
    DC_init();
    US_init();
    CA_state = STATE(CA_waiting);
    US_state = STATE(US_busy);
    DC_state = STATE(DC_idle);
}

int main(){
    volatile int dd;
    setup();
    while(1){
        US_state();
        CA_state();
        DC_state();
        for(dd=0 ; dd<500 ; dd++);
    }
}