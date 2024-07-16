#include "stdio.h"

int loop (int num){
    for (int i=0; i<num; i++){
        for (int j=i; j<num; j++){
            printf("%d ",j);
        }
        printf("\n");
    }
}

// int main(){
//     loop (10);
// }