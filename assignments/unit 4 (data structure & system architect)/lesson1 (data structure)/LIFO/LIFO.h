#ifndef LIFO_H_
#define LIFO_H_

typedef struct {
    unsigned int length;
    unsigned int count;
    unsigned int* base;
    unsigned int* head;
} LIFO_buf_t;

typedef enum {
    LIFO_no_error,
    LIFO_full,
    LIFO_empty,
    LIFO_null
} LIFO_status;

LIFO_status LIFO_Add_items(LIFO_buf_t* LIFO_buf, unsigned int items);
LIFO_status LIFO_get_items(LIFO_buf_t* LIFO_buf, unsigned int* items);
LIFO_status LIFO_init(LIFO_buf_t* LIFO_buf, unsigned int* buf, unsigned int length);

#endif
