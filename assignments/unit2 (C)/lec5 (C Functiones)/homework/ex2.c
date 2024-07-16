#include "stdio.h"
int factorial(int n);

void main(){
    int n;
    printf("enter positive number: ");
    scanf("%d",&n);
    printf("factorial of %d = %d",n, factorial(n));
}

int factorial(int n){
    if (n!=1){
        return n*factorial(n-1);
    }
}