#include "stdio.h"
int main(){
    float x[5]={5,16,22,3.5,15};
    float y;
    int i;
    for (i=0 ; i < 5 ; i++) {
        y=5*x[i]*x[i] + 3*x[i]+2;
        printf("y(%0.1f)= %0.2f\n",x[i],y);
    }
}