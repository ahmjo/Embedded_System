#include "stdio.h"
int main ()
{
    int i = 0 , j ;
    for (i = 0 ; i < 10 ; i++)
    {
        for (j = i ; j < 10 ; j++)
        {
            printf("%d ",j);
        }
        printf("\n");
    }
}