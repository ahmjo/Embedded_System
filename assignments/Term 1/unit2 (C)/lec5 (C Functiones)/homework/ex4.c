#include "stdio.h"

int pow (int base , int power );

int main (){
    int base , power ; 
    printf("enter base number : ");
    scanf("%d",&base);
    printf("enter power number : ");
    scanf("%d",&power);
    printf("%d^%d=%d", base, power, pow(base, power));
}

int pow (int base, int power){
    if (power!=0){
        return (base*pow(base, power-1)) ;
    }
    else return 1;
}