#include "stdio.h"
int main(){
    int n ;
    printf("enter the number of data : ");
    scanf("%d",&n);
    float arr[n] , sum=0;

    for (int i=0; i<n; i++){
        printf("%d enter the number : ",i+1);
        scanf("%f",&arr[i]);
        sum+=arr[i];
    }
    float avr = sum/n;
    printf("average = %.2f",avr);
}