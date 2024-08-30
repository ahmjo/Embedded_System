#include "LIFO.h"
#include "stdlib.h"

LIFO_status LIFO_Add_items(LIFO_buf_t* LIFO_buf, unsigned int items){
    if(!LIFO_buf->base || !LIFO_buf->head)
        return LIFO_null;

    if(LIFO_buf->count == LIFO_buf->length)
        return LIFO_full;

    *(LIFO_buf->head) = items;
    LIFO_buf->head++;
    LIFO_buf->count++;
    return LIFO_no_error;
}

LIFO_status LIFO_get_items(LIFO_buf_t* LIFO_buf, unsigned int* items){
    if(!LIFO_buf->base || !LIFO_buf->head)
        return LIFO_null;

    if(LIFO_buf->count == 0)
        return LIFO_empty;

    LIFO_buf->head--;
    *items = *(LIFO_buf->head);
    LIFO_buf->count--;
    return LIFO_no_error;
}

LIFO_status LIFO_init(LIFO_buf_t* LIFO_buf, unsigned int* buf, unsigned int length){
    if(buf == NULL)
        return LIFO_null;

    LIFO_buf->base = buf;
    LIFO_buf->head = buf;
    LIFO_buf->length = length;
    LIFO_buf->count = 0;
    return LIFO_no_error;
}
