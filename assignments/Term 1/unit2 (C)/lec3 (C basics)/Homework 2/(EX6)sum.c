#include "stdio.h"
int main()
{
    int i ,j , sum =0;

    printf("enter a integer : ");
    fflush(stdin);fflush(stdout);
    scanf("%d",&j);

    for (i=1 ; i<=j ; i++)
    {
        sum += i ;
    }
    printf("sum= %d\n", sum);
}