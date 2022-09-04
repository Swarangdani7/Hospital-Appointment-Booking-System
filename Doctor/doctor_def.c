/* This file name is "doctor_def.c"
It contains the declarations of functions that will be performed by doctor
*/

//including the header file "doctor.h" where the functions were declared
#include"doctor.h"

//defining macros for better visibility of options in the switch case
#define DISPLAY 1
#define UPDATE 2
#define LOGOUT 3
#define EXIT 4

//temporarily defining main function for testing purpose
int main()
{
	menu();
}


//defining function to display menu for doctor
void menu()
{
	int doc_id,opt;
	char doc_password[20],ch;
	d_node *head;
	FILE *dptr;
	printf("\n--------------------WELCOME DOCTOR--------------------\n\n");
	printf("Doctor Login::\n");
	printf("Enter Doctor ID: ");
	scanf("%d",&doc_id);
	printf("Enter password: ");
	scanf("%s",doc_password);
	if(validate_login(doc_id,doc_password))			//passing the variables to validate login function
	{
		printf("\nLogged in successfully...\n\n");
		while(1)
		{
			printf("\n--------------DOCTOR MENU--------------\n\n");
			printf("Choose an option...\n1) Display Appointments\n2) Update availability Hours\n3) LogOut\n4) Exit\nOption: ");
			scanf("%d",&opt);
			switch(opt)
			{
				case DISPLAY:
					display(doc_id);
					continue;
				case UPDATE:
					printf("Update availability hours here..\n\n");
					head = update_hours(doc_id);
					dptr = fopen("doctor_details.txt","w");	
					dptr=write_to_file(dptr,head);
					fclose(dptr);
					free(head);
					printf("\nUpdated Hours successfully !!!\n\n");
					continue;
				case LOGOUT:
					printf("Logged out successfully..\n\n");
					printf("Do you want to login again..?\n");
					printf("Choose y/n : ");
					while(getchar()!='\n');
					ch=getchar();
					if(ch=='Y' || ch=='y')
						menu();
					else
					{
						printf("Exited !!\n");
						exit(0);
					}
					break;
				case EXIT:
					printf("\nThank you for using our services _/\_\nExited from Hospital Appointment Booking System..\n\n");
					exit(0);
				default:
					printf("Invalid Option!! Choose a valid option...\n");
					continue;
			}
		}
	}
	else
	{
		printf("Incorrect Doctor ID/Password !!!\n");
		printf("Do you want to login again..?");
		printf("Choose y/n : ");
		while(getchar()!='\n');
		ch=getchar();
		if(ch=='Y' || ch=='y')
			menu();
		else
		{
			printf("Exited !!\n");
			exit(0);
		}
	}
}

//function to validate login by comparing with the values in doctor_login.txt
int validate_login(int doc_id, char doc_password[20])
{
	char *token;
	FILE* fptr;
	doctor doc;
	int count=0;
	char line[100];
	fptr=fopen("doctor_details.txt","r");
	if(fptr==NULL)
		printf("File doesn't exist\n");
	
	while(fgets(line,sizeof(line),fptr)!=NULL)
	{
		token=strtok(line,",");
	
	if(count==0)
	{
		doc.userId=atoi(token);
		count++;
		token=strtok(NULL,",");
	}
	
	if(count==1)
	{
		strcpy(doc.password,token);
		token=strtok(NULL,",");
		count++;
	}
	if(doc_id==doc.userId && strcmp(doc_password,doc.password)==0)
		return 1;
	count=0;
	}
	return 0;
}

//defining the function "validate_date" to validate the date given by the doctor
//takes date string as a parameter
int validate_date(char str[20])
{
	int count=0;
	char *token;
	dt d;
	
	token=strtok(str,"/");
			
	if(count==0)
	{
		d.day=atoi(token);
		count++;
		token=strtok(NULL,"/");
	}
	
	if(count==1)
	{
		d.mon=atoi(token);
		token=strtok(NULL,"/");
		count++;
	}
	if(count==2)
	{
		d.yr=atoi(token);
		token=strtok(NULL,"/");
		count++;
	}
	count=0;	
    if(d.yr>=1900 && d.yr<=2022)
    {
        //check month
        if(d.mon>=1 && d.mon<=12)
        {
            //check days
            if((d.day>=1 && d.day<=31) && (d.mon==1 || d.mon==3 || d.mon==5 || d.mon==7 || d.mon==8 || d.mon==10 || d.mon==12))
                return 1;
            else if((d.day>=1 && d.day<=30) && (d.mon==4 || d.mon==6 || d.mon==9 || d.mon==11))
                return 1;
            else if((d.day>=1 && d.day<=28) && (d.mon==2))
                return 1;
            else if(d.day==29 && d.mon==2 && (d.yr%400==0 ||(d.yr%4==0 && d.yr%100!=0)))
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    else
    	return 0;
}

//function to display the appointment details of particular date.
void display(int doct_id)
{
	int count=0,num=0;
	char *token;
	char line[200];
	appointment apmnt;
	char check_date[20],temp_date[20];
	printf("Enter date(DD/MM/YYYY) of appointments you wanted to display: ");
	scanf("%s",check_date);
	strcpy(temp_date,check_date);
	if(!(validate_date(temp_date)))
	{
		printf("\nInvalid date!!, Please re-enter correctly\n");
		display(doct_id);
	}
	else
	{
	FILE *fptr;
	fptr=fopen("ap_details.txt","r");
	
	if(fptr==NULL)
		printf("File doesn't exist\n");
		
	printf("Your appointment details on the particular date are..\n\n");
	printf("AppointmentID\tPatientID\tPatientFirstName\tPatientLastName\t\tDoctorFirstName\t\tDoctorLastName\t\tDepartment\tAppointmentDate\t\tTime\n");
	
	while(fgets(line,sizeof(line),fptr)!=NULL)
	{
		token=strtok(line,",");
			
		if(count==0)
		{
			apmnt.apt_id=atoi(token);
			count++;
			token=strtok(NULL,",");
		}
		
		if(count==1)
		{
			apmnt.pat_id=atoi(token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==2)
		{
			strcpy(apmnt.pat_fname,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==3)
		{
			strcpy(apmnt.pat_lname,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==4)
		{
			apmnt.doc_id=atoi(token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==5)
		{
			strcpy(apmnt.doc_fname,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==6)
		{
			strcpy(apmnt.doc_lname,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==7)
		{
			strcpy(apmnt.dept_name,token);
			token=strtok(NULL,",");
			count++;
			
		}
		if(count==8)
		{
			strcpy(apmnt.apt_dt,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==9)
		{
			strcpy(apmnt.apt_t,token);
			token=strtok(NULL,",");
		}
		
		count=0;
		if(doct_id==apmnt.doc_id && strcmp(apmnt.apt_dt,check_date)==0)
		{
			printf("%d\t\t%d\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t%s\t\t%s\n",apmnt.apt_id,apmnt.pat_id,apmnt.pat_fname,apmnt.pat_lname,apmnt.doc_fname,apmnt.doc_lname,apmnt.dept_name,apmnt.apt_dt,apmnt.apt_t);
			num++;
		}
	}
	if(num==0)
		printf("\n\n\t\t\tNo Appointments available on the given date :(\n\n");
	fclose(fptr);
	}
}

//Function to create a node for the linked list
//Paramaters: structure variable of doctor and returns the new node created
d_node* create_node(doctor d)
{
	d_node *newnode= (d_node*)calloc(sizeof(d_node),6);
	
	newnode->doc.userId=d.userId;
	strcpy(newnode->doc.password,d.password);
	strcpy(newnode->doc.name,d.name);
	strcpy(newnode->doc.gmail,d.gmail);
	newnode->doc.phone_no=d.phone_no;
	newnode->doc.shift_time=d.shift_time;
	newnode->doc.dept_id=d.dept_id;
	
	return newnode;
}


//Function to add a node to the linked list
//Paramaters: 2 pointers of linked list
d_node* add_node(d_node *head,d_node *newnode)
{
    d_node *temp=head;
    //check if LL is empty
    if(head==NULL)
         head = newnode;
    else
    {
        while(temp->next!=NULL)
              temp = temp->next;
          
        temp->next = newnode;
        //printf("%d\n",newnode->doc.shift_time);
    }

   return head;
}
	
//Function to load the contents from the linked list and store into the file after all the operations
//Paramaters: file pointer and head pointer of the linked list and  returns the file pointer
FILE* write_to_file(FILE *dptr, d_node *head)
{
	d_node *temp=head;
	
	while(temp!=NULL)
	{
		fprintf(dptr,"%d,%s,%s,%s,%ld,%d,%d\n",temp->doc.userId, temp->doc.password,temp->doc.name,temp->doc.gmail,temp->doc.phone_no,temp->doc.shift_time,temp->doc.dept_id);
		temp=temp->next;
	}
	
	return dptr;
}

//Function to update a record using user Id 
//Paramaters: integer and return type: head pointer of the updated list
d_node* update_hours(int doc_id)
{
	FILE *dptr;
	doctor doc;
	d_node *head,*newnode;
	head=NULL;
	int temp_id,hr,count=0;
	char ch;
	char line[100];
	char *token;
	char *end[20];
	printf("Please confirm your Doctor ID to update the availability hours: ");
	scanf("%d",&temp_id);
	if(doc_id!=temp_id)
	{
		printf("Incorrect Doctor ID !!!\n");
		printf("Do you want to try again..?");
		printf("Choose y/n : ");
		while(getchar()!='\n');
		ch=getchar();
		if(ch=='Y' || ch=='y')
			update_hours(doc_id);
		else
			menu();
	}
	else
	{
		printf("\nValidation succesfull :)\n\n");
		printf("Enter your new availability hours:  ");
		scanf("%d",&hr);
		
		dptr=fopen("doctor_details.txt","r");
		
		if(dptr==NULL)
		printf("File doesn't exist\n");
	
	    	while(fgets(line,sizeof(line),dptr)!=NULL)
		{
	
			token=strtok(line,",");
			
			if(count==0)
			{
				doc.userId=atoi(token);
				count++;
				token=strtok(NULL,",");
			}
			
			if(count==1)
			{
				strcpy(doc.password,token);
				token=strtok(NULL,",");
				count++;
			}
			if(count==2)
			{
				strcpy(doc.name,token);
				token=strtok(NULL,",");
				count++;
			}
			if(count==3)
			{
				strcpy(doc.gmail,token);
				token=strtok(NULL,",");
				count++;
			}
			if(count==4)
			{
				doc.phone_no=strtol(token,end,10);
				token=strtok(NULL,",");
				count++;
			}
			if(count==5)
			{
				doc.shift_time=atoi(token);
				token=strtok(NULL,",");
				count++;
			}
			if(count==6)
			{
				doc.dept_id=atoi(token);
				token=strtok(NULL,",");
				
			}
			count=0;
			newnode=create_node(doc);
			head=add_node(head,newnode);
		}
		fclose(dptr);
		d_node *temp=head;
		while(temp!=NULL && doc_id!=temp->doc.userId)
			temp=temp->next;
		if(temp!=NULL)
			temp->doc.shift_time=hr;
		else
			printf("\nNo doctor exists with the ID you entered.\n");
	}
	return head;
}
