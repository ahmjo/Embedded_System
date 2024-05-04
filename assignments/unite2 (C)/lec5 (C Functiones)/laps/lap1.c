#include "stdio.h"

int factorial(int num) {
    int facto=1;
    if (num==1 || num==0){
        facto = 0;
    }
    for(int i=1; i <= num; i++){
        facto = facto* i;
    }
    return facto;
}

int main() {
    int x;
    printf("enter the number : ");scanf("%d",&x);
    printf("factoeial(%d)= %d ",x , factorial(x));
}