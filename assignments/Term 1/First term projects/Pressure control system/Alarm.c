#include "Alarm.h"

void Alarm_turn_ON(){
    Set_Alarm_actuator(0);
}

void Alarm_turn_OFF(){
    Set_Alarm_actuator(1);
}