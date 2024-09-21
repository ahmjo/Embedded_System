#ifndef SYS_H_
#define SYS_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <string.h>
#define width 5

typedef struct{
    char first_name[50];
    char last_name[50];
    int ID ;
    float GPA ;
    unsigned int Courses_Resgisterd [5];
}SStudent_Info;

typedef struct{
    unsigned int length;
    unsigned int count;
    SStudent_Info* base;
    SStudent_Info* head;
    SStudent_Info* tail;
} FIFO_Buf_t;

typedef enum{
    FIFO_no_error,
    FIFO_full,
    FIFO_empty,
    FIFO_Null,
    FIFO_error
} FIFO_buf_status;

FIFO_buf_status FIFO_init(FIFO_Buf_t* FIFO_buf, SStudent_Info* buf, unsigned int length);
int check_ID(FIFO_Buf_t* FIFO_buf ,int temp_ID);
FIFO_buf_status FIFO_is_full(FIFO_Buf_t* FIFO_buf);
int FIFO_enqueue_file(FIFO_Buf_t* FIFO_buf, SStudent_Info* item);
FIFO_buf_status FIFO_enqueue(FIFO_Buf_t* FIFO_buf, SStudent_Info* item);
FIFO_buf_status FIFO_dequeue(FIFO_Buf_t* FIFO_buf, SStudent_Info* item);
int Find_Student_By_ID(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent);
int Find_Student_By_FirstName(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent);
int Find_Students_Registered_In_course(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent);
void Count_Of_Student(FIFO_Buf_t* FIFO_buf);
int Delete_Student(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent);
int Update_Student(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent);
void FIFO_Print(FIFO_Buf_t* FIFO_buf);

#endif