#include "FIFO.h"
#include "stdio.h"

FIFO_buf_status FIFO_init(FIFO_buf_t* FIFO_buf, element_type* buf, uint32_t length) {
    if(buf == NULL)
        return FIFO_Null;

    FIFO_buf->base = buf;
    FIFO_buf->head = buf;
    FIFO_buf->tail = buf;
    FIFO_buf->length = length;
    FIFO_buf->count = 0;

    return FIFO_no_error;
}

FIFO_buf_status FIFO_enqueue(FIFO_buf_t* FIFO_buf, element_type item) {
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail)
        return FIFO_Null;
    if (FIFO_IS_FULL(FIFO_buf) == FIFO_full)
        return FIFO_full;

    *(FIFO_buf->head) = item;
    FIFO_buf->count++;

    if(FIFO_buf->head == (FIFO_buf->base + FIFO_buf->length))
        FIFO_buf->head = FIFO_buf->base;
    else
        FIFO_buf->head++;

    return FIFO_no_error;
}

FIFO_buf_status FIFO_dequeue(FIFO_buf_t* FIFO_buf, element_type* item) {
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail)
        return FIFO_Null;
    if(FIFO_buf->count == 0)
        return FIFO_empty;

    *item = *(FIFO_buf->tail);
    FIFO_buf->count--;

    if(FIFO_buf->tail == (FIFO_buf->base + FIFO_buf->length))
        FIFO_buf->tail = FIFO_buf->base;
    else
        FIFO_buf->tail++;

    return FIFO_no_error;
}

FIFO_buf_status FIFO_IS_FULL(FIFO_buf_t* FIFO_buf) {
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail)
        return FIFO_Null;
    if (FIFO_buf->count == FIFO_buf->length)
        return FIFO_full;

    return FIFO_no_error;
}

void FIFO_print(FIFO_buf_t* FIFO_buf) {
    element_type* temp;
    int i;
    if(FIFO_buf->count == 0) {
        printf("FIFO is empty\n");
    } else {
        temp = FIFO_buf->tail;
        printf("=====FIFO_print=====\n");
        for(i = 0; i < FIFO_buf->count; i++) {
            printf("\t %d \n", *temp);
            temp++;
            if(temp == (FIFO_buf->base + FIFO_buf->length))
                temp = FIFO_buf->base;
        }
        printf("===============\n");
    }
}
