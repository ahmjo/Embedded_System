#include "stdio.h"
#include "stdlib.h"
struct information {
    char name[100];
    int roll;
    float marks;
};

int main(){
    struct information student ;
    char n[100];
    printf("Enter the information of students : \n\nEnter name : ");
    scanf("%s", &n);
    strcpy(student.name,n);
    printf("Enter roll number : ");
    scanf("%d", &student.roll);
    printf("Enter marks : ");
    scanf("%f", &student.marks);
    printf("Displaying information\nName : %s\nRoll : %d\nMark : %.2f", student.name, student.roll, student.marks);
}