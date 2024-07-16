#include "stdio.h"

int main(){
    char alpha[27];
    char* p;

    p=alpha;

    for(int i=0; i<26;i++){
        *p=i+'A';
        p++;
    }
    
    p=alpha;
    printf("\n\nThe Alphabets are : ");

    for(int i=0; i<26;i++){
        printf("%c ",*p);
        p++;
    }
    printf("\n\n");
}