#include "stdio.h"
#include "stdlib.h"
#include "LIFO.h"

unsigned int buffer1 [5];

int main (){
    unsigned int i , temp=0;
    LIFO_buf_t UART_buf , I2C_buf ;

    LIFO_init(&UART_buf, buffer1,5);

    unsigned int* buffer2 = malloc (sizeof(unsigned int)*5);
    LIFO_init(&I2C_buf, buffer2,5);

    for ( i = 0; i < 5; i++)
    {
        if(LIFO_Add_items(&UART_buf,i) == LIFO_no_error){
            printf("UART_buf add : %d\n",i);
        }
    }
    for ( i = 0; i < 5; i++)
    {
        if(LIFO_get_items(&UART_buf, &temp) == LIFO_no_error){
            printf("UART_buf get : %d\n",temp);
        }
    }
}