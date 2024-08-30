#include "linked_list.h"

struct SStudent* gpFirstStudent = NULL;

void AddStudent(){
    struct SStudent* PNewStudent;
    struct SStudent* PLaststudent;
    char temp[50];

    if(gpFirstStudent==NULL){
        PNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
        gpFirstStudent = PNewStudent; 
    }else{
        PLaststudent = gpFirstStudent;
        while(PLaststudent->PnextStudent){
            PLaststudent = PLaststudent->PnextStudent;
        }
        PNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
        PLaststudent->PnextStudent = PNewStudent;
    }
    
    printf("enter student ID : \n");
    gets(temp);
    PNewStudent->student.ID = atoi(temp);

    printf("enter student name : \n");
    gets(PNewStudent->student.name);

    printf("enter student height : \n");
    gets(temp);
    PNewStudent->student.height = atof(temp);

    PNewStudent->PnextStudent=NULL;
}

//---------------------------------------------------------------------------

int Delete_Student(){
    char temp[50];
    int selected_ID;

    printf("enter student ID : \n");
    gets(temp);
    selected_ID = atoi(temp);

    if(gpFirstStudent){
        struct SStudent* PSelectStudent = gpFirstStudent;
        struct SStudent* PPrevStudent = NULL;
        while(PSelectStudent){
            if(PSelectStudent->student.ID == selected_ID){
                if(PPrevStudent){
                    PPrevStudent->PnextStudent = PSelectStudent->PnextStudent;
                }else{
                    gpFirstStudent = PSelectStudent->PnextStudent;
                }
                free(PSelectStudent);
                return 1;
            }
            PPrevStudent = PSelectStudent;
            PSelectStudent = PSelectStudent->PnextStudent;
        }
    }
    printf("cann't find student ID :)");
    return 0;
}

//-----------------------------------------------------------------------------

void View_Students(){
    int count = 0;
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if (gpFirstStudent==NULL)
    {
        printf("\n empty list");
    }
    else{
        while (PCurrentStudent){
            printf("\nrecord number : %d",count+1);
            printf("\nID : %d", PCurrentStudent->student.ID);
            printf("\nName : %s", PCurrentStudent->student.name);
            printf("\nHeight : %.2f", PCurrentStudent->student.height);
            printf("\n====================\n");
            PCurrentStudent = PCurrentStudent->PnextStudent;
            count++;
        }
    }
}

//-------------------------------------------------------------------------------

void Delete_All(){
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if (gpFirstStudent==NULL)
    {
        printf("\n empty list");
    }
    else{
        while (PCurrentStudent){
            struct SStudent* PTemp = PCurrentStudent;
            PCurrentStudent = PCurrentStudent-> PnextStudent;
            free(PTemp);
        }
        gpFirstStudent = NULL;
    }
}

//-------------------------------------------------------------------------------

void Get_Nth_Node(){
    int count=0 , index ;
    struct SStudent* PCurrentStudent = gpFirstStudent;
    printf("enter the index of student : ");
    scanf("%d",&index);

    while(PCurrentStudent){
        if(count==index){
            printf("\nID: %d",PCurrentStudent->student.ID);
            printf("\nName: %s",PCurrentStudent->student.name);
            printf("\nHeight: %.2f",PCurrentStudent->student.height);
            break;
        }else{
            PCurrentStudent=PCurrentStudent->PnextStudent;
            count++;
        }
    }
}

//--------------------------------------------------------------------------------

void Find_Length_Iterative(){
    struct SStudent* PCurrentStudent = gpFirstStudent;
    int count = 0;
    while(PCurrentStudent){
        PCurrentStudent=PCurrentStudent->PnextStudent;
        count++;
    }
    printf("length of list : %d",count);
}

int Find_Length_Recursive(struct SStudent* gpFirstStudent){
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if(PCurrentStudent==NULL){
        return 0;
    }else{
        PCurrentStudent= PCurrentStudent->PnextStudent;
        return 1+Find_Length_Recursive(PCurrentStudent);
    }
}

//--------------------------------------------------------------------------------

void Get_Nth_Node_End(){
    int count = 0 , index;
    struct SStudent* PCurrentStudent = gpFirstStudent;
    if(gpFirstStudent==NULL){printf("\nempty list\n");}

    printf("enter the index of student : ");
    scanf("%d",&index);

    while(PCurrentStudent){
        if(index==(Find_Length_Recursive(gpFirstStudent)-count)){
            printf("\nID: %d ",PCurrentStudent->student.ID);
			printf("\nname: %s ",PCurrentStudent->student.name);
			printf("\nheight: %f ",PCurrentStudent->student.height);
			break;
        }else{
            PCurrentStudent = PCurrentStudent->PnextStudent;
            count++;
        }
    }
}

void Get_Nth_Node_End_2Bointer(){
    struct SStudent* main_P = gpFirstStudent;
    struct SStudent* ref_P = gpFirstStudent;
    int index , i ;
    printf("enter the index of student : ");
    scanf("%d",&index);
    for(i=0;i<index;i++){ref_P = ref_P->PnextStudent;}
    while(ref_P){
        main_P = main_P->PnextStudent;
        ref_P = ref_P->PnextStudent;
    }
        
	printf("\nID: %d ",main_P->student.ID);
	printf("\nname: %s ",main_P->student.name);
	printf("\nheight: %f ",main_P->student.height);
}

//--------------------------------------------------------------------------------

void Get_Middle(){
    int i,index;
    struct SStudent* PSelectStudent = gpFirstStudent;
    index = Find_Length_Recursive(gpFirstStudent) / 2;
    for(i=0 ; i<index ; i++){
        PSelectStudent = PSelectStudent -> PnextStudent;
    }
    printf("\nID: %d ",PSelectStudent->student.ID);
	printf("\nname: %s ",PSelectStudent->student.name);
	printf("\nheight: %f ",PSelectStudent->student.height);
}

//--------------------------------------------------------------------------------

int Detect_Loop(){
    struct SStudent* PSlow = gpFirstStudent;
    struct SStudent* PFast = gpFirstStudent;
    while(PSlow && PFast && PFast->PnextStudent){
        PSlow = PSlow ->PnextStudent;
        PFast = PFast ->PnextStudent->PnextStudent;
        if(PSlow==PFast){
            printf("\nfind loop");
            return 1;
        }
    }
    printf("\ndon't find loop");
    return 0;
}

//--------------------------------------------------------------------------------

void Reverse()
{
	struct SStudent* Pprev=NULL;
	struct SStudent* Pcurrent=gpFirstStudent;
	struct SStudent* Pnext=Pcurrent->PnextStudent;
	while(Pcurrent)
	{
		Pnext=Pcurrent->PnextStudent;
		Pcurrent->PnextStudent=Pprev;
		Pprev=Pcurrent;
		Pcurrent=Pnext;
	}
	gpFirstStudent=Pprev;
}