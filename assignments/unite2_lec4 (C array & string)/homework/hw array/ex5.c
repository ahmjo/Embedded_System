#include <stdio.h>

int main() {
    int n ;
    printf("enter no of elements : ");
    scanf("%d", &n);

    int arr[n];
    printf("enter the elements : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int num; 
    printf("Enter the number to be serched : ");
    scanf("%d", &num);

    for (int i = 0; i < n; i++) {
        if (arr[i] ==num) {
            printf("number found at the location : %d",i+1);
            break;
        }
    }
}