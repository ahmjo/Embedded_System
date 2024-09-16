#include "stdio.h"
int main()
{
    float N ;
    printf(" Enter a number : ");
    fflush(stdin);fflush(stdout);
    scanf("%f", &N);
    
    if (N>0)
    {
        printf(" %f is positive", N);
    }
    else if (N==0)
    {
        printf("you entered zero");
    }
    else
    {
        printf(" %f is negative", N);
    }
}