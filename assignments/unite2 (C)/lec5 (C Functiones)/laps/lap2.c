#include "stdio.h"

int minimum(int array[] ,int num) {
    int min = array[0];
    for (int i = 1; i < num; i++){
        if(array[i] < min)min = array[i];
    }
    return min;
}

int main() {
    int ar[10]={1,2,3,4,5,6,3,1,0,77};
    printf("the minimum num in array is %d\n",minimum(ar,10));
}