#include "System.c"

int main(){
	FIFO_Buf_t student;
    int choose;
	SStudent_Info temp;

    if(FIFO_init(&student,student_buffer,3)==FIFO_no_error)
	{
		printf("\n=============================================\n");
		printf("FIFO INIT HAS DONE");
		printf("===============================================");
    }

    while(1){
        printf("\n 1.Add Student:");
		printf("\n 2.read from file:");
		printf("\n 3.Dequeue:");
		printf("\n 4.View Students Info:");
		printf("\n 5.Count Of Students:" );
		printf("\n 6.Find Student By ID:");
		printf("\n 7.Find  Student By FirstName:");
		printf("\n 8.Find Students Registered In course:");
		printf("\n 9.Delete Student By ID:");
		printf("\n 10.Updata Student Info:");
		printf("\n 11.End The Program:");
		printf("\n Enter Your Choose: ");
		scanf("%d",&choose);

        if (choose==1)
        {
            if(FIFO_enqueue(&student,&temp)==FIFO_no_error){
				printf("====================================\n");
				printf("\t FIFO ENQUEUE Has Done");
				printf("\n====================================\n");
			}
			else if((FIFO_enqueue(&student,student_buffer)==FIFO_full)){
				printf("\n====================================\n");
				printf("FIFO IS FULL");
				printf("\n====================================\n");
			}else{
				printf("\t FIFO Enqueue Has Faild\n");
            }
        }

        if(choose==2){
            FIFO_enqueue_file(&student,student_buffer);
        }

        if(choose==3){
			if(FIFO_dequeue(&student,&temp)==FIFO_no_error);
		}

        if(choose==4){
			FIFO_Print(&student);
		}

        if(choose==5){
			Count_Of_Student(&student);
        }

        if(choose==6){
            Find_Student_By_ID(&student,student_buffer);
        }

        if(choose==7){
			Find_Student_By_FirstName(&student,student_buffer);
        }

        if (choose==8)
        {
			Find_Students_Registered_In_course(&student,student_buffer);
        }
        
        if (choose==9)
        {
            Delete_Student(&student,student_buffer);
        }
        
        if (choose==10){
            Update_Student(&student,student_buffer);
        }
        
        if (choose==11){
            break;
            return 0;
        }
    }
}