#include "stdio.h"
int main()
{
    float a,b,temp;
    printf("Enter value of a: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&a);

    printf("Enter value of b: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&b);

    temp=a;
    a=b;
    b=temp;

    printf("the value of a = %f\nthe value of b = %f",a,b);
}