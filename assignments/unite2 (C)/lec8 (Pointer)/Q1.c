#include "stdio.h"

int main(){
    int* ab ;
    int m ;
    m=29;
    printf("Address of m : %p\n",&m);
    printf("Content of pointer ab : %d\n\n",m);

    ab=&m;
    printf("Now ab is assigned with the address of m.\n");
    printf("Address of pointer ab : %p\n",ab);
    printf("Content of pointer ab : %d\n\n",*ab);

    m=34;
    printf("The value of m assigned to 34 now.");
    printf("Address of pointer ab : %p\n",ab);
    printf("Content of pointer ab : %d\n\n",*ab);

    *ab=7;
    printf("The pointer variable ab is assigned with the value 7 now.\n");
    printf("Address of m : %p\n",&m);
    printf("Value of m : %d\n",m);
}