#include "stdio.h"
int main(){
    float degree[10];
    int i;
    for (i = 1; i <= 10; i++){
        printf("enter student %d degree : ",i);
        fflush(stdin);fflush(stdout);
        scanf("%f",&degree[i-1]);
    }
    for(i = 1; i <= 10; i++){
        printf("\nstudent %d degree is %f",i,degree[i-1]);
    }
}