#include "stdio.h"

int sum(int num){
    if (num==0){
        return 0;
    }
    else{
        return num+sum(num-1);
    }
}
int main(){
    int num=100;
    printf("the sum of numbers from 1 to 100 is %d" , sum(num));
}