#include "stdio.h"
#include "stdlib.h"

#ifndef linked_list_H_
#define linked_list_H_

struct Sdata{
    int ID;
    char name [50];
    float height;
};

struct SStudent{
    struct Sdata student;
    struct SStudent* PnextStudent; 
};

extern struct SStudent* gpFirstStudent;

void AddStudent();
int Delete_Student();
void View_Students();
void Delete_All();
void Get_Nth_Node();
void Find_Length_Iterative();
int Find_Length_Recursive(struct SStudent* gpFirstStudent);
void Get_Nth_Node_End();
void Get_Nth_Node_End_2Bointer();
void Get_Middle();
int Detect_Loop();
void Reverse();

#endif