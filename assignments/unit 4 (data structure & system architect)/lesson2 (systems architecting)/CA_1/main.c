#include "CA.c"
#include <time.h>

void setup(){
    srand(time(0));
    CA_state = STATE(CA_waiting);
}

int main(){
    volatile int d;
    setup();
    while(1){
        CA_state();
        for(d=0 ; d<500 ; d++);
    }
}