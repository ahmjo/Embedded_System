#include "stdio.h"
int main()
{
    int N1 , N2;
    printf("Enter two integers : ");
    fflush(stdin);;fflush(stdout);
    scanf("%d %d", &N1 , &N2);
    printf("\nSum: %d\n", N1+N2 );
}