#include <stdio.h>

int main() {
    float a,b;
    printf("Enter value of a: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&a);

    printf("Enter value of b: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&b);
    
    printf("the value of a = %f\nthe value of b = %f",b,a);
}

// There is another solution using addition and subtraction:
//     a = a + b;
//     b = a - b;
//     a = a - b;
// thus,we swaped it without using a temporary variable