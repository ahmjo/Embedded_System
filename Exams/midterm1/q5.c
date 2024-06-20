#include <stdio.h>

int count_ones(int num) ;

int main() {
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);

    printf("Number of ones in binary = %d\n", count_ones(num));
}

int count_ones(int num) {
    int count = 0;
    
    while (num != 0) {
        if (num & 1) {
            count++;
        }
        num >>= 1; 
    }
    
    return count;
}