#include "FIFO.h"
#include "stdint.h"
#include "stdio.h"

element_type buff[width];

int main() {
    element_type i, temp;
    FIFO_buf_t FIFO_UART;

    if (FIFO_init(&FIFO_UART, buff, width) == FIFO_no_error)
        printf("FIFO_init----------DONE\n");

    for (i = 0; i < 7; i++) {
        if (FIFO_enqueue(&FIFO_UART, i) == FIFO_no_error) {
            printf("FIFO_enqueue----------DONE\n");
        } else {
            printf("FIFO_enqueue----------failed\n");
        }
    }

    FIFO_print(&FIFO_UART);

    FIFO_dequeue(&FIFO_UART, &temp);
    printf("FIFO_dequeue: Data=%d\n", temp);

    FIFO_dequeue(&FIFO_UART, &temp);
    printf("FIFO_dequeue: Data=%d\n", temp);

    FIFO_print(&FIFO_UART);

    return 0;
}