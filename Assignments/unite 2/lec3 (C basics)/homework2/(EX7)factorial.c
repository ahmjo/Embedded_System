#include "stdio.h"
int main()
{
    int i ,j , sum =1;

    printf("enter a integer : ");
    fflush(stdin);fflush(stdout);
    scanf("%d",&j);

    if (j>0)
    {
        for (i=1 ; i<=j ; i++)
        {
            sum *= i ;
        }
        printf("factorial= %d\n", sum);
    }
    else if (j==0)
    {
        printf("factorial= 1");
    }
    else{
        printf("error!!! factorial of negative number is not exist");
    }
}