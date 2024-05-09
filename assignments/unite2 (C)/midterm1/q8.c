#include "stdio.h"
void reverse(int *s);
int main (){
    int s[100]={1,2,3,4,5};
    int *ptr=s;
    reverse(ptr);
}

void reverse(int *s){
    if (*s=='\0') {
        return;
    }
    reverse(s+1);
    printf("%d ",*s);
}