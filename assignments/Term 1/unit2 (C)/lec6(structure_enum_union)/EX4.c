#include "stdio.h"

struct Students {
    char name[100];
    int roll;
    int marks;
} S[3];

int main() {
    int i;
    printf("Enter the informations of students:\n");
    for(i = 0; i < 3; i++) {
        S[i].roll = i + 1;
        printf("\nFor roll number(%d)\nEnter name: ", S[i].roll);
        scanf("%s", S[i].name);
        printf("Enter marks: ");
        scanf("%d", &S[i].marks);
        printf("\n");
    }
    
    printf("Displaying the informations of students\n\n");
    for(i = 0; i < 3; i++) {
        printf("Information for roll number(%d)\n", S[i].roll);
        printf("Name: %s\n", S[i].name);
        printf("Marks: %d\n\n", S[i].marks);
    }
}
