#ifndef UTILS_H_
#define UTILS_H_

#define setbit(reg,bit)    reg|=(1<<bit)
#define resetbit(reg,bit)  reg&=~(1<<bit)
#define readbit(reg,bit)   ((reg>>bit)&1)
#define toggle(reg,bit)    reg^=(1<<bit)

#endif /* UTILS_H_ */