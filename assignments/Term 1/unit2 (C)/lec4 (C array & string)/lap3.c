#include "stdio.h"
int main(){
    float matrix[3][3];
    int r,c;
    float trans[3][3];

    for(r=0;r<3;r++){
        for(c=0;c<3;c++){
            printf("enter the items (%d,%d) : ",r,c);
            fflush(stdin);fflush(stdout);
            scanf("%f",&matrix[r][c]);
            trans[c][r] = matrix[r][c];
        }
    }
    printf("\nthe matrix is : \n");
    for(r=0;r<3;r++){
        for(c=0;c<3;c++){
            printf("%0.2f\t",matrix[r][c]);
        }
    printf("\n");
    }
    printf("\nthe transposed matrix is : \n");
    for(r=0;r<3;r++){
        for(c=0;c<3;c++){
            printf("%0.2f\t",trans[r][c]);
        }
    printf("\n");
    }
}