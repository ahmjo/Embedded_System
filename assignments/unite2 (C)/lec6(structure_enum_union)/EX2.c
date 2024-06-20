#include "stdio.h"

struct D
{
    int feet;
    float inch;
}D1,D2,SUM;

int main(){
    printf("Enter the distance(1):\nEnter Feet: ");
    scanf("%d",&D1.feet);
    printf("Enter inch: ");
    scanf("%f",&D1.inch);
    printf("\nEnter the distance(2):\nEnter Feet: ");
    scanf("%d",&D2.feet);
    printf("Enter inch: ");
    scanf("%f",&D2.inch);

    SUM.feet = D1.feet+D2.feet;
    SUM.inch = D1.inch+D2.inch;
    if (SUM.inch>=12){
        SUM.inch -= 12;
        ++SUM.feet;
    }
    printf("\nsum of distances= %d\'%.2f\"",SUM.feet,SUM.inch);
}