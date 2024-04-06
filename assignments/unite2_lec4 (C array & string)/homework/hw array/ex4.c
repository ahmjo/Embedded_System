#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[100];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int a, loc;
    printf("Enter the number to be inserted: ");
    scanf("%d", &a);
    printf("Enter the location: ");
    scanf("%d", &loc);

    for (int i = n - 1; i >= loc - 1; i--) {
        arr[i + 1] = arr[i];
    }
    arr[loc - 1] = a;
    n++; 

    printf("after insertion:\n");
    for (int i = 0; i < n; i++) { 
        printf("%d ", arr[i]);
    }
    return 0;
}