#ifndef FIFO_H_
#define FIFO_H_

#include "stdlib.h"
#include "stdint.h"

#define element_type uint8_t
#define width 5

element_type buff[width];

typedef struct{
    unsigned int length;
    unsigned int count;
    element_type* base;
    element_type* tail;
    element_type* head;
}FIFO_buf_t;

typedef enum{
    FIFO_no_error,
    FIFO_full,
    FIFO_empty,
    FIFO_Null
}FIFO_buf_status;


FIFO_buf_status FIFO_init (FIFO_buf_t* FIFO_buf , element_type* buf , uint32_t length);
FIFO_buf_status FIFO_enqueue (FIFO_buf_t* FIFO_buf , element_type item);
FIFO_buf_status FIFO_dequeue (FIFO_buf_t* FIFO_buf , element_type* item);
FIFO_buf_status FIFO_IS_FULL (FIFO_buf_t* FIFO_buf);
void FIFO_print (FIFO_buf_t* FIFO_buf);

#endif