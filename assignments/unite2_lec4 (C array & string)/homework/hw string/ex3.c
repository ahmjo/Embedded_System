#include <stdio.h>
#include <string.h>

int main() {
    char c[1000],temp;
    printf("enter a string : ");
    gets(c);
    int n = strlen(c);
    int i,j;
    for( i=0 , j=n-1 ; i<j ; i++ , j--){
        temp=c[i]; c[i]=c[j]; c[j]=temp;
    }
    printf("reverse string is %s",c);
}