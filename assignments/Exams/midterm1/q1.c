#include "stdio.h"

int sum(int num);

int main(){
    int num ;
    printf("enter the number : ");
    scanf("%d",&num);
    printf("%d",sum(num));
}

int sum(int num ){
    if(num==0){
        return 0;
    }
    else{
        return (num%10)+(sum(num/10)) ;
    }
}