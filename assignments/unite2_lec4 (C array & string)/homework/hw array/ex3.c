#include "stdio.h"
int main(){
    int r,c;
    printf("enter the size of matrix : ");
    scanf("%d %d",&r,&c);
    float matrix[r][c];
    float trans[r][c];

    for(int i = 0 ; i<r;i++){
        for(int j=0;j<c;j++){
            printf("enter the items (%d,%d) : ",i+1,j+1);
            fflush(stdin);fflush(stdout);
            scanf("%f",&matrix[i][j]);
            trans[j][i] = matrix[i][j];
        }
    }
    printf("\nthe matrix is : \n");
    for(int i = 0 ; i<r;i++){
        for(int j=0;j<c;j++){
            printf("%0.2f\t",matrix[i][j]);
        }
    printf("\n");
    }
    printf("\nthe transposed matrix is : \n");
    for(int i = 0 ; i<c;i++){
        for(int j=0;j<r;j++){
            printf("%0.2f\t",trans[i][j]);
        }
    printf("\n");
    }
}