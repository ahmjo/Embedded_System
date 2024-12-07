#ifndef DC_H_
#define DC_H_

#include "STATE.h"

enum {
    DC_idle,
    DC_busy
} DC_STATE_id;

STATE_define(DC_idle);
STATE_define(DC_busy);

void DC_init ();
extern void (*DC_state)();

#endif
