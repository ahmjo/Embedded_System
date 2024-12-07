#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_statefunc_)  void ST_##_statefunc_ ()
#define STATE(_statefunc_)  ST_##_statefunc_ 

void US_distace_set (int d);
void DC_motor (int s);

#endif