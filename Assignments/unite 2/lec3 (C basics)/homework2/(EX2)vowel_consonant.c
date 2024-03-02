#include "stdio.h"
int main()
{
    char l ;
    printf("enter an alphabel : ");
    fflush(stdin);fflush(stdout);
    scanf("%c", &l);

    if (l == 'a' || l == 'A' || l == 'e' || l == 'E' || l == 'o' || l == 'O' || l == 'i' || l == 'I')
    {
        printf("%c is vowel", l);
    }
    else if ((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))
    {
        printf("%c is consonant", l);
    }
    else
    {
        printf("Invalid input. Please enter an alphabet letter.\n");
    }
}