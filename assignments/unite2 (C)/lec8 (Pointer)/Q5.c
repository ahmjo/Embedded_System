#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct emp {
    char name[100];
    int id;
};

int main() {
    struct emp *em[2];
    
    em[0] = (struct emp *)malloc(sizeof(struct emp));

    em[0]->id = 1002;
    strcpy(em[0]->name, "Alex");

    printf("Employee Name: %s\n", em[0]->name);
    printf("Employee ID: %d\n", em[0]->id);
}
