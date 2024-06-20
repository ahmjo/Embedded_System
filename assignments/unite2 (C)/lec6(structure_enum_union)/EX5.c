#include "stdio.h"
#define PI 3.141592653589793
#define area(r) (PI*r*r)

void main(){
    float R;
    float area;
    printf("enter the redous : ");
    scanf("%f",&R);
    area = area(R);
    printf("area = %f\n", area);
}