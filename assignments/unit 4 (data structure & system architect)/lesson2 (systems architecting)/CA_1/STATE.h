#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_statefunc_)  void ST_##_statefunc_ ()
#define STATE(_statefunc_)  ST_##_statefunc_ 

#endif