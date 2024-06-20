#include "stdio.h"

int unique (int arr[],int size);

int main(){
    int a1[7]={4,2,5,2,5,7,4};
    int a2[3]={4,2,4};

    printf("Unique number in first array: %d\n", unique(a1, 7));
    printf("Unique number in second array: %d\n", unique(a2, 3));
}

int unique (int arr[],int size){
    int uni=0;

    for(int i=0;i<size;i++){
        uni^=arr[i];
    }
    return uni ;
}