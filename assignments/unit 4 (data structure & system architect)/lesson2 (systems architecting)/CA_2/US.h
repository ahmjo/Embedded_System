#ifndef US_H_
#define US_H_

#include "STATE.h"

enum {
    US_busy
} US_STATE_id;

STATE_define(CA_waiting);
STATE_define(CA_driving);

void US_init ();
extern void (*US_state)();

#endif
