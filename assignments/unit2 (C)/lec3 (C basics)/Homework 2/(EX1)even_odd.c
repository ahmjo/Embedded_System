#include "stdio.h"
int main()
{
    int N, x ;
    printf("Enter an integer number you want to chick : ");
    fflush(stdin);(stdout);
    scanf("%d", &N);

    x=N%2;

    if (x == 0)
    {
        printf("%d is even", N);
    }
    else{
        printf("%d is odd", N);
    }
}