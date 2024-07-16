#include "stdio.h"
int main ()
{
    float x , y , z ;
    printf("enter three numbers : \n");
    fflush(stdin);fflush(stdout);
    scanf("%f",&x);
    scanf("%f",&y);
    scanf("%f",&z);
    if (x>y)
    {
        if (x>z)
        {
            printf("the largest value is %f",x);
        }
        else
        {
            printf("the largest value is %f",z);
        }
    }
    else
    {
        if (y>z)
        {
            printf("the largest value is %f",y);
        }
        else
        {
            printf("the largest value is %f",z);
        }
    }
}
