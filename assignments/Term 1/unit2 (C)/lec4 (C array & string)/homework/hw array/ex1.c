#include "stdio.h"
int main(){
    float a[2][2],b[2][2];
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("enter a%d%d : ",i+1,j+1);
            scanf("%f",&a[i][j]);
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("enter b%d%d : ",i+1,j+1);
            scanf("%f",&b[i][j]);
        }
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            a[i][j]=a[i][j]+b[i][j];
        }
    }
    printf("\nsum of matrix:\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%0.2f\t",a[i][j]);
        }
    printf("\n");
    }
}