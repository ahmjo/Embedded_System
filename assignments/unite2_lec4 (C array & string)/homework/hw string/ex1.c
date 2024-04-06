#include <stdio.h>

int main() {
    char x[1000],ch;
    int i,count=0;
    printf("Enter a string : ");
    gets(x);
    printf("Enter the chr to find freqancy : ");
    scanf("%c",&ch);    
    for (i=0;x[i]!='\0';i++){
        if (x[i]==ch) {
            count++;
        }
    }
    printf("freqancy of %c = %d",ch,count);
}