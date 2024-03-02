#include "stdio.h"
int main()
{
    float x, y ;
    char op ;
    printf("Enter first number: ");
    fflush(stdin);fflush(stdout);
    scanf("%f", &x);
    printf("Enter operator either + , - , * or / : ");
    fflush(stdin);fflush(stdout);
    scanf("%c", &op);
    printf("Enter socand number: ");
    fflush(stdin);fflush(stdout);
    scanf("%f", &y);

    switch (op)
    {
    case '+':
        printf("%f + %f = %f", x, y,x+y);
        break;
    case'-':
        printf("%f - %f = %f", x, y,x-y);
        break;
    case'/':
        printf("%f / %f = %f", x, y,x/y);
        break;
    case'*':
        printf("%f * %f = %f", x, y,x*y);
        break;
    default:
        break;
    }
}