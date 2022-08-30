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
					dt d;
					printf("Enter date(DD/MM/YY) of appointments you wanted to display: ");
					scanf("%d/%d/%d",&d.day,&d.mon,&d.yr);
					display(d);
					continue;
				case UPDATE:
					printf("Update availability hours here..\n\n");
					head = update_hours(doc_id);
					dptr = fopen("doctor_details.txt","w");	
					dptr=write_to_file(dptr,head);
					fclose(dptr);
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
					printf("Program exited..\n\n");
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
	int id,t;
	long phone;
	char pwd[20],name[20],mail[50];
	FILE *fptr;
	fptr=fopen("doctor_details.txt","r");
	while(fscanf(fptr,"%d %s %s %s %ld %d\n",&id,pwd,name,mail,&phone,&t)!=-1)
	{
		if(doc_id==id && strcmp(doc_password,pwd)==0)
			return 1;
	}
	return 0;
}

//function to display the appointment details of particular date.
void display(dt d)
{
	int ap_id,day,month,year,pat_id;
	char pat_name[20];
	FILE *fptr;
	fptr=fopen("ap_details.txt","r");
	printf("Your appointment details on the particular date are..\n\n");
	printf("AppointmentID	AppointmentDate		PatientID	PatientName\n");
	while(fscanf(fptr,"%d,%d/%d/%d,%d,%s",&ap_id,&day,&month,&year,&pat_id,pat_name)!=-1)
	{
		if(day==d.day && month==d.mon && year==d.yr)
			printf("%d		%d/%d/%d		%d		%s\n",ap_id,day,month,year,pat_id,pat_name);
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
		fprintf(dptr,"%d %s %s %s %ld %d\n",temp->doc.userId, temp->doc.password,temp->doc.name,temp->doc.gmail,temp->doc.phone_no,temp->doc.shift_time);
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
	int temp_id,hr;
	char ch;
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
		
		//Reading data from the file to linked list
		while(fscanf(dptr,"%d %s %s %s %ld %d\n",&doc.userId,doc.password,doc.name,doc.gmail,&doc.phone_no,&doc.shift_time)!=-1)
		{
			//printf("\n%d,%s,%s,%s,%ld,%d\n",doc.userId,doc.password,doc.name,doc.gmail,doc.phone_no,doc.shift_time);
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
