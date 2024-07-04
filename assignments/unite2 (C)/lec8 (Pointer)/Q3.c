#include "stdio.h"

void reverse (char* s);

void main (){
    char s[100];
    char* p ;
    p=s;
    
    printf ("enter the string: ");
    fgets(s,100,stdin);
    reverse (p);
}

void reverse (char* s){
    if(*s=='\0'){
        return;
    }
    else{
        reverse (s+1);
        printf ("%c",*s);
    }
}