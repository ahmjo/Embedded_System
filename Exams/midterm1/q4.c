#include "stdio.h"
void reverse(char *s);
int main (){
    char s[100];
    char *ptr=s;
    printf("enter the number :  ");
    fgets(s, 100,stdin);
    reverse(ptr);
}

void reverse(char *s){
    if (*s=='\0') {
        return;
    }
    reverse(s+1);
    printf("%c",*s);
}