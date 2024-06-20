#include "stdio.h"

int is_prim(int num);

int main(){
    int n1,n2 ,i,check ;
    printf("enter two numbers : ");
    scanf("%d %d",&n1,&n2);
    printf("prim numbers beyween %d and %d : ", n1,n2);
    for(i=n1+1;i<n2;++i){
        check=is_prim(i);
        if (check==1){
            printf("%d ",i);
        }
    }
}

int is_prim(int num){
    if ( num==2 || num==3) {
        return 1;
    }
    else if ( num%2==0 || num%3==0){
        return 0;
    }
    else{
        int a=5;
        while (a<=num/2){
            if (num%a==0 || num%(a+2)==0){
                return 0 ;
            }
            a=a+6;
        }
        return 1;
    }
}