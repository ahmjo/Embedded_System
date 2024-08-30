#include "linked_list.h"
#include "linked_list.c"

int main(){
    char text [50];

    while(1){
        printf("\n=========================\n");
        printf("choose one of the following options : \n");
        printf("1.Add student : \n");
        printf("2.Delete student : \n");
        printf("3.View students : \n");
        printf("4.Delete all : \n");
        printf("5.Get Nth node : \n");
        printf("6.Find length with iterative : \n");
        printf("7.Find length with Recursive : \n");
        printf("8.Get Nth node from the End : \n");
        printf("9.Get Nth node from the End with 2Bointer: \n");
        printf("10.Get Middle : \n");
        printf("11.Detect Loop : \n");
        printf("12.Reverse : \n");
        gets(text);
        printf("========================\n");

        switch (atoi(text))
        {
        case 1:
            AddStudent();
            break;
        case 2:
            Delete_Student();
            break;
        case 3:
            View_Students();
            break;
        case 4:
            Delete_All();
            break;
        case 5:
            Get_Nth_Node();
            break;
        case 6:
            Find_Length_Iterative();
            break;
        case 7:
            Find_Length_Recursive(gpFirstStudent);
            break;
        case 8:
            Get_Nth_Node_End();
            break;
        case 9:
            Get_Nth_Node_End_2Bointer();
            break;
        case 10:
            Get_Middle();
            break;
        case 11:
            Detect_Loop();
            break;
        case 12:
            Reverse();
            break;
        default:
            printf("Wrong option");
            break;
        }
    }
}