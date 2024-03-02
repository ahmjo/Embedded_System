#include "stdio.h"
int main ()
{
    char l ;
    printf("enter an character : ");
    fflush(stdin);fflush(stdout);
    scanf("%c", &l);
    if ((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))
    {
        printf("%c is an alphabet ",l);
    }
    else
    {
        printf("%c is not an alphabet",l);
    }
}