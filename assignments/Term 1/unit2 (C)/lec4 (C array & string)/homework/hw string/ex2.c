#include <stdio.h>

int main() {
    char c[1000];
    printf("Enter a string : ");
    gets(c);
    int i ;
    for( i=0;c[i]!='\0';i++);
    printf("length of string = %d ",i);
}