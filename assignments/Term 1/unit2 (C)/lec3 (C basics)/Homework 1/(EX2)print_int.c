#include "stdio.h"
int main()
{
    int N;
    printf("Enter a integer : ");
    fflush(stdin);;fflush(stdout);
    scanf("%d", &N);
    printf("\nYou entered: %d\n", N);
}