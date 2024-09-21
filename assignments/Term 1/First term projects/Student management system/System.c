#include "System.h"
#define width 5
SStudent_Info student_buffer[width];


FIFO_buf_status FIFO_init(FIFO_Buf_t* FIFO_buf, SStudent_Info* buf, unsigned int length){
    if(buf==NULL){return FIFO_Null;}

    FIFO_buf->length=length;
    FIFO_buf->count=0;
    FIFO_buf->base=buf;
    FIFO_buf->head=buf;
    FIFO_buf->tail=buf;
    return FIFO_no_error;
}

//-----------------------------------------------------

int check_ID(FIFO_Buf_t* FIFO_buf ,int temp_ID) { 
    int y;
    SStudent_Info* ptr=FIFO_buf->base;

    for(y=0;y<(FIFO_buf->count);y++){
        if(ptr->ID==temp_ID){
            return 0;
        }
        ptr++;
    }
    return 1;
}
//-------------------------------------------------------------------------------

FIFO_buf_status FIFO_is_full(FIFO_Buf_t* FIFO_buf){
    if(!FIFO_buf->base || !FIFO_buf->head || !FIFO_buf->tail){return FIFO_Null;}
    if(FIFO_buf->length==FIFO_buf->count){return FIFO_full;}
    return FIFO_no_error;
}

//--------------------------------------------------------------------------------

int FIFO_enqueue_file(FIFO_Buf_t* FIFO_buf, SStudent_Info* item) {
    char fName[50], lName[50];
    int ID_num, X = 0, course_ID[5], Num_std = 0, len = 0;
    float gpa;

    if (FIFO_is_full(FIFO_buf) == FIFO_Null) {
        printf("No Data Exist\n");
        return 0;
    }
    if (FIFO_is_full(FIFO_buf) == FIFO_full) {
        printf("FIFO Is Full\n");
        return 0;
    }

    FILE *p_file = fopen("F:\\courses\\embedded system diplom\\content\\Term 1\\final projects\\Student_sys\\stdData.txt", "r");
    if (p_file == NULL) {
        printf("The File not found\n");
        return FIFO_error;
    }

    while (fscanf(p_file, "%49s %d %49s %f %d %d %d %d %d", fName, &ID_num, lName, &gpa,
                &course_ID[0], &course_ID[1], &course_ID[2], &course_ID[3], &course_ID[4]) == 9) {
        
        if (FIFO_buf->count == FIFO_buf->length) {
            printf("\n====================================\n");
            printf("FIFO Is Full\n");
            printf("Students Added: %d\n", FIFO_buf->count);
            printf("Remaining Students: %d\n", FIFO_buf->length - FIFO_buf->count);
            fclose(p_file);
            return FIFO_full;
        }

        if (check_ID(FIFO_buf, ID_num) == 0) {
            printf("IN line %d: ID Number %d already exists\n", len, ID_num);
            len++;
            continue;
        }

        FIFO_buf->head->ID = ID_num;
        FIFO_buf->head->GPA = gpa;
        strcpy(FIFO_buf->head->first_name, fName);
        strcpy(FIFO_buf->head->last_name, lName);

        X = 0;
        for (int i = 0; i < 5; i++) {
            if (course_ID[i] < 0 || course_ID[i] > 50) {
                X = 1;
                break;
            }
            FIFO_buf->head->Courses_Resgisterd[i] = course_ID[i];
        }

        if (X == 1) {
            printf("IN Line %d: Invalid Course ID\n", len);
            len++;
            continue;
        }

        FIFO_buf->head++;
        if (FIFO_buf->head == FIFO_buf->base + FIFO_buf->length) {
            FIFO_buf->head = FIFO_buf->base;  // Wrap around if at the end
        }
        FIFO_buf->count++;
        len++;
        Num_std++;
    }

    fclose(p_file);
    printf("\n====================================\n");
    printf("Students Added: %d\n", FIFO_buf->count);
    printf("Remaining Students: %d\n", FIFO_buf->length - FIFO_buf->count);
    return FIFO_no_error;
}


//------------------------------------------------------------------------------

FIFO_buf_status FIFO_enqueue(FIFO_Buf_t* FIFO_buf, SStudent_Info* item) {
    char temp[50];

    if (FIFO_is_full(FIFO_buf) == FIFO_Null) {
        return FIFO_Null;
    }
    if (FIFO_is_full(FIFO_buf) == FIFO_full) {
        return FIFO_full;
    }

    printf("\n=====================================\n");
    printf("\nEnter ID: ");
    scanf("%d", &item->ID);

    if (check_ID(FIFO_buf, item->ID)==0) {
        printf("This ID is already exist\n");
        return FIFO_error;
    }

    printf("\nEnter the first name: ");
    scanf("%s", temp);
    strcpy(item->first_name, temp);

    printf("\nEnter the last name: ");
    scanf("%s", temp);
    strcpy(item->last_name, temp);

    printf("\nEnter GPA: ");
    scanf("%f", &item->GPA);

    printf("\nEnter Courses Registered (5 courses): \n");
    for (int j = 0; j < 5; j++) {
        printf("\tEnter ID of course %d: ", j + 1);
        scanf("%d", &item->Courses_Resgisterd[j]);
    }

    *FIFO_buf->head = *item;
    FIFO_buf->count++;

    if (FIFO_buf->head == FIFO_buf->base + FIFO_buf->length - 1) {
        FIFO_buf->head = FIFO_buf->base;
    } else {
        FIFO_buf->head++;
    }

    return FIFO_no_error;
}


//--------------------------------------------------------------------------------------

FIFO_buf_status FIFO_dequeue(FIFO_Buf_t* FIFO_buf, SStudent_Info* item){
    if(FIFO_is_full(FIFO_buf)== FIFO_Null){
		return FIFO_Null;
    }
    if(FIFO_buf->count==0){
        return FIFO_empty;
    }
    item->ID=FIFO_buf->tail->ID;
    FIFO_buf->count--;

    printf("\n==========================================================\n");
    printf("FIFO dequeue which ID of student is %d has DONE ", item->ID);
    printf("\n============================================================\n");

    if(FIFO_buf->tail == (FIFO_buf->base + (FIFO_buf->length - 1))){
        FIFO_buf->tail=FIFO_buf->base;
    }else{
        FIFO_buf->tail++;
    }
    return FIFO_no_error;
}

//-----------------------------------------------------------------------------------------

int Find_Student_By_ID(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent){
    int temp_ID ,i,j;
    PStudent=FIFO_buf->tail;

    printf("\nEnter ID for the Student You want it :");
    scanf("%d",&temp_ID);

	for(i=0;i<FIFO_buf->count;i++)
	{
		if(PStudent->ID==temp_ID)
		{
			printf("=====================================\n");
			printf("\t the first name is: %s \n",PStudent->first_name);
			printf("\t the last name is: %s \n",PStudent->last_name);
			printf("\t the ID is %d: \n",(PStudent->ID));
			printf("\t the GPA is %f : \n",(PStudent->GPA));
			for(j=0;j<5;j++)
			{
				printf("\t the ID of the %d course is: %d \n",j+1,(PStudent->Courses_Resgisterd[j]));
			}
			printf("====================================\n");
			return 0;
		}
		PStudent++;
	}
	printf("\n====================================\n");
	printf("This ID Not Found\n");
	printf("====================================\n");
	return 0;
}

//-----------------------------------------------------------------------------------------------------

int Find_Student_By_FirstName(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent){
    char FirstName[12];
	int i=0,j=0;
	PStudent=FIFO_buf->tail;
	printf("\nEnter The First Name for Student You want it :");
	scanf("%s",FirstName);

	for(i=0;i<FIFO_buf->count;i++)
	{
		if(strcmp(PStudent->first_name,FirstName)==0)
		{
			printf("====================================\n");
			printf("\t the first name is: %s \n",PStudent->first_name);
			printf("\t the last name is: %s \n",PStudent->last_name);
			printf("\t the ID is %d: \n",(PStudent->ID));
			printf("\t the GPA is %f : \n",(PStudent->GPA));
			for(j=0;j<5;j++)
			{
				printf("\t the ID of the %d course is: %d \n",j+1,(PStudent->Courses_Resgisterd[j]));
			}
			printf("====================================\n");
			return 0;
		}
		PStudent++;
	}
	printf("\n====================================\n");
	printf("This FirstName Not Found\n");
	printf("====================================\n");

	return 0;
}

//--------------------------------------------------------------------------------------

int Find_Students_Registered_In_course(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent){
    if(FIFO_buf->count==0)
	{
		printf("\n====================================\n");
		printf("fifo is empty\n");
		printf("======================================\n");
		return 0;
	}

    int Course_ID,X=0;
    PStudent =FIFO_buf->tail;
    printf("\nEnter The Course ID: ");
	scanf("%d",&Course_ID);

	for(int i=0;i<FIFO_buf->count;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(PStudent->Courses_Resgisterd[j]==Course_ID)
			{
				printf("\n====================================\n");
				printf("\t the first name is: %s \n",PStudent->first_name);
				printf("\t the last name is: %s \n",PStudent->last_name);
				printf("\t the ID is %d: \n",(PStudent->ID));
				printf("\t the GPA is %f : \n",(PStudent->GPA));
				for(int k=0;k<5;k++)
				{
					printf("\t the ID of the %d course is: %d \n",k+1,(PStudent->Courses_Resgisterd[k]));
				}
				printf("====================================\n");
				X=1;
			}
			if(i==4)
				return 0;
		}
		PStudent++;
	}
	if(X==0)
	{
	printf("\n====================================\n");
	printf("This Course ID Not Found\n");
	printf("====================================\n");
	}
	return 0;
}

//--------------------------------------------------------------------------------------

void Count_Of_Student(FIFO_Buf_t* FIFO_buf){
	printf("\n======================================\n");
    printf("the Number of student = %d",FIFO_buf->count);
	printf("\n======================================\n");
}

//------------------------------------------------------------------------------------------

int Delete_Student(FIFO_Buf_t* FIFO_buf,SStudent_Info* PStudent){
	if(FIFO_buf->count==0)
	{
		printf("\n====================================\n");
		printf("Fifo Is Empty");
		printf("\n======================================\n");
		return 0;
	}

    PStudent=FIFO_buf->tail;
    SStudent_Info* PNext= (FIFO_buf->tail)+1;
    int temp_ID , X=0;

	printf("Enter Student ID To Delete It \n");
	scanf("%d",&temp_ID);

    for(int i=0 ; i<FIFO_buf->count;i++){
        if(PStudent->ID==temp_ID){
            *PStudent=*PNext;
            X=1;
        }
    }
    if(X==1){
        printf("\n===============================\n");
		printf("Deleation has DONE");
		printf("\n===============================\n");

		(FIFO_buf->count)--;
		(FIFO_buf->head)--;
		return 0;
    }else{
		printf("This ID Not Found\n");
		return 0;
    }
}

//-----------------------------------------------------------------------------------------

int Update_Student(FIFO_Buf_t* FIFO_buf, SStudent_Info* PStudent){
    if(FIFO_buf->count == 0){
        printf("\n====================================\n");
        printf("FIFO is empty");
        printf("\n====================================\n");
        return 0;
    }

    int temp_ID;
    int choice, Course_ID;
    SStudent_Info* current_student = FIFO_buf->base;

    printf("\n====================================\n");
    printf("Enter Student ID That You Want To Update: ");
    scanf("%d", &temp_ID);

    for(int i = 0; i < FIFO_buf->count; i++){
        if(current_student->ID == temp_ID){
            printf("1. First Name\n");
            printf("2. Last Name\n");
            printf("3. ID\n");
            printf("4. GPA\n");
            printf("5. Courses\n");
            printf("Choose What You Want To Update: ");
            scanf("%d", &choice);

            switch(choice){
                case 1: {
                    printf("Enter The New First Name: ");
                    scanf("%s", current_student->first_name);
                    break;
                }
                case 2: {
                    printf("Enter The New Last Name: ");
                    scanf("%s", current_student->last_name);
                    break;
                }
                case 3: {
                    printf("Enter The New ID: ");
                    scanf("%d", &current_student->ID);
                    break;
                }
                case 4: {
                    printf("Enter The New GPA: ");
                    scanf("%f", &current_student->GPA);
                    break;
                }
                case 5: {
                    printf("Enter ID Of The Course That You Want To Update: ");
                    scanf("%d", &Course_ID);

                    for(int j = 0; j < 5; j++){
                        if(current_student->Courses_Resgisterd[j] == Course_ID){
                            printf("Enter The New Course ID: ");
                            scanf("%d", &(current_student->Courses_Resgisterd[j]));
                            break;
                        }
                    }
                    break;
                }
                default: {
                    printf("Wrong Choice\n");
                    break;
                }
            }
            printf("\n====================================\n");
            return 1;
        }

        current_student++;
        if(current_student == (FIFO_buf->base + FIFO_buf->length)){
            current_student = FIFO_buf->base;
        }
    }

    printf("Student with ID %d not found\n", temp_ID);
    printf("\n====================================\n");
    return 0;
}


//-----------------------------------------------------------------------------------------

void FIFO_Print(FIFO_Buf_t* FIFO_buf){
    SStudent_Info *temp;
	int i;
	int j;

	if(FIFO_buf->count==0){
		printf("\n====================================\n");
		printf("FIFO is empty");
		printf("\n======================================\n");
	}

	else{
		temp=FIFO_buf->tail;
		printf("\n====================================\n");
		for(i=0;i<FIFO_buf->count;i++)
		{
			printf("\t the first name is: %s \n",temp->first_name);
			printf("\t the last name is: %s \n",temp->last_name);
			printf("\t the ID is %d: \n",(temp->ID));
			printf("\t the GPA is %f : \n",(temp->GPA));
			for(j=0;j<5;j++)
			{
				printf("\t the ID of the %d course is: %d \n",j+1,(temp->Courses_Resgisterd[j]));
			}
			printf("====================================\n");
			temp++;
		}
	}
}