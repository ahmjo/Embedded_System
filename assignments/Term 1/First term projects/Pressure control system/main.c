#include "driver.h"
#include "P_Sensor.h"
#include "Alarm.h"
#define waiting 2000

void main(){
    int threshold=20;
    int volatile p_val;
    GPIO_INITIALIZATION();
    while(1){
        p_val=read_p_sensor();
        if(p_val >= threshold){
            Alarm_turn_ON();
            Delay(waiting);
            Alarm_turn_OFF();
            Delay(waiting);
        }
        else if (p_val < threshold){
            Alarm_turn_OFF();
        }
        Delay(20000);
    }
}