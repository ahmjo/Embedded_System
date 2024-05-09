#include <stdio.h>

float squareRoot(int n) ;

int main() {
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);

    printf("Square root of %d is: %.3f\n", num, squareRoot(num));
}

float squareRoot(int n) {
    float x = n;
    float y = 1;
    float z = 0.00001;

    while (x - y > z) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}