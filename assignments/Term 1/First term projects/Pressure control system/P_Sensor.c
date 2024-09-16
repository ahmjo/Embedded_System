#include "P_Sensor.h"

int read_p_sensor(){
    int p_val;
    p_val=getPressureVal();
    return p_val;
}