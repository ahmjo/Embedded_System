#ifndef CA_H_
#define CA_H_

#include "STATE.h"

enum {
    CA_waiting,
    CA_driving
} CA_STATE_id;

STATE_define(CA_waiting);
STATE_define(CA_driving);

extern void (*CA_state)();

#endif
