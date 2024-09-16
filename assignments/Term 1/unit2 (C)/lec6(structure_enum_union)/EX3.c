#include "stdio.h"

struct C
{
    float real;
    float img;
} C1, C2, SUM;

int main(){
    printf("for complex number(1)\nenter the real and imaginary respectively: ");
    scanf("%f %f", &C1.real, &C1.img);
    
    printf("for complex number(2)\nenter the real and imaginary respectively: ");
    scanf("%f %f", &C2.real, &C2.img);

    SUM.real = C1.real + C2.real;
    SUM.img = C1.img + C2.img;
    printf("\nsum = %.2f + %.2fi\n", SUM.real, SUM.img);
}
