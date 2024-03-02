#include "stdio.h"
int main ()
{
    char ch ;
    printf("Enter a character: "); 
    fflush(stdin);fflush(stdout);
    scanf("%c", &ch);
    printf("\nASCII value of %c is %d", ch, (int)ch);
}