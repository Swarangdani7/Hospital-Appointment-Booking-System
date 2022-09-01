#include "receptionist.h"

/* Function to delete a Node from Linked List  */
appointment* removeNode(appointment* head, int app_id){
	if(head == NULL) return head;
	appointment *temp,*prev;
	if(head->appointmentID == app_id){
		temp = head;
		head = head->next;
		free(temp);
	}
	else{
		temp = head;
		while(temp != NULL && temp->appointmentID != app_id){
			prev = temp;
			temp = temp->next;
		}
		prev->next = temp->next;
		free(temp);
	}
	return head;
}

/* Function to accept AppointmentDetails */
appointment* acceptAppointmentDetails(appointment* head){
	int a_id,p_id,d_id,day,mon,year,hrs,min,sec;
	FILE *fptr;
	fptr = fopen("appointment_details.txt","r");
	
	if(fptr == NULL){
		printf("\nError! Cannot Open File...\n");
		exit(1);
	}
	
	while(fscanf(fptr,"%d,%d,%d,%d/%d/%d,%d:%d:%d",&a_id,&p_id,&d_id,&day,&mon,&year,&hrs,&min,&sec) != -1){
		appointment *newnode = (appointment*)malloc(sizeof(appointment));
		newnode->next = NULL;
		newnode->appointmentID = a_id;
		newnode->patientID = a_id;
		newnode->doctorID = a_id;
		newnode->dt.day = day;
		newnode->dt.mon = mon;
		newnode->dt.year = year;
		newnode->dt.hrs = hrs;
		newnode->dt.min = min;
		newnode->dt.sec = sec;
		
		if(head == NULL){
			head = newnode;
		}
		else{
			appointment* temp = head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newnode;
		}
	}
	fclose(fptr);
	return head;
}

/* Function to check if Appointment ID is valid or not */
int isValidAppointment(int app_id){
	int a_id,p_id,d_id,day,mon,year,hrs,min,sec,flg=0;
	
	FILE* fptr;
	fptr = fopen("appointment_details.txt","r");
	
	if(fptr == NULL){
		printf("\nError! Cannot Open File...\n");
		exit(1);
	}
	
	while(fscanf(fptr,"%d,%d,%d,%d/%d/%d,%d:%d:%d",&a_id,&p_id,&d_id,&day,&mon,&year,&hrs,&min,&sec) != -1){
		if(a_id == app_id){
			flg = 1;
			break;
		}
	}
	
	fclose(fptr);
	return flg;
}

/* Function to Display Appointment */
void Display_Appointment(){

	int app_id,valid;
	
	do{
		printf("\nEnter Appointment ID : ");
		scanf("%d",&app_id);
		valid = isValidAppointment(app_id); // function to check if Appointment ID is valid or not
		if(valid){
			int a_id,p_id,d_id;
			Date dt;
			
			FILE* fptr;
			fptr = fopen("appointment_details.txt","r");
			
			if(fptr == NULL){
				printf("\nError! Cannot Open File...\n");
				exit(1);
			}
			
			printf("\n-----------------------------------------------------------------------------\n");
			printf("Appointment ID | Patient ID | Doctor ID | Appointment Date | Appointment Time\n");
			printf("-----------------------------------------------------------------------------\n");
			
			while(fscanf(fptr,"%d,%d,%d,%d/%d/%d,%d:%d:%d\n",&a_id,&p_id,&d_id,&dt.day,&dt.mon,&dt.year,&dt.hrs,&dt.min,&dt.sec) != -1){
				if(a_id == app_id){
					printf("%d            | %d        | %d       | %d/%d/%d        | %d:%d:%d          \n",a_id,p_id,d_id,dt.day,dt.mon,dt.year,dt.hrs,dt.min,dt.sec);
					break;
				}
			}
			fclose(fptr);
		}
		else{
			printf("\n----------------------------------");
			printf("\nEnter valid Appointment ID !\n");
			printf("----------------------------------\n");
		}
	}
	while(valid == 0);
}



/* Function to Cancel an Appointment */
void Cancel_Appointment(){
	
	int app_id,valid;
	appointment* head = NULL;
	head = acceptAppointmentDetails(head); // function to read appointment details from file and store in Linked List
	if(head == NULL){
		printf("\nNo Appointments to Cancel !\n");
		return;
	}
	
	do{
		printf("\nEnter Appointment ID : ");
		scanf("%d",&app_id);
		valid = isValidAppointment(app_id); // function to check if Appointment ID is valid or not
		if(valid){
			head = removeNode(head,app_id); // function to delete record associated with app_id
			// if head is Null then print: There are no appointments to cancel !
			FILE *fptr;
			fptr = fopen("appointment_details.txt","w");
			
			if(fptr == NULL){
				printf("\nError! Cannot Open File...\n");
				exit(1);
			}
			
			appointment* temp = head;
			while(temp != NULL){
				fprintf(fptr,"%d,%d,%d,%d/%d/%d,%d:%d:%d",temp->appointmentID,temp->patientID,temp->doctorID,temp->dt.day,temp->dt.mon,temp->dt.year,temp->dt.hrs,temp->dt.min,temp->dt.sec);
				if(temp->next != NULL) fprintf(fptr,"\n");
				temp = temp->next;	
			}
			
			while(head != NULL){
				temp = head;
				head = head->next;
				free(temp);
			}
			fclose(fptr);
			printf("\nAppointment #%d Cancelled !\n",app_id);
		}
		else{
			printf("\n----------------------------------");
			printf("\nEnter valid Appointment ID !\n");
			printf("----------------------------------\n");
		}
	}
	while(valid == 0);
}

/* Function to display MENU */
void displayMenu(){
	int ch;
	do{
		while(1){
			printf("\n\n-----------------Receptionist Menu-----------------\n");
			printf("\n\t\t1. Book Appointment\n\t\t2. Cancel Appointment\n\t\t3. Display Appointment\n\t\t0. Exit\n");
			printf("\nEnter your choice :: ");
			scanf("%d",&ch);
			if(ch < 0 || ch > 3){
				system("clear");
				continue;
			}
			break;
		}
		
		
		switch(ch){
			case 1:
				//Book_Appointment();
				break;
			case 2:
				Cancel_Appointment();
				break;
			case 3:
				Display_Appointment();
				break;
			case 0:
				exit(0);
				break;
		}
		printf("\nDo you wish to continue (1/0) : ");
		scanf("%d",&ch);
		system("clear");
	}
	while(ch != 0);
}

/* Function to validate Username and Password */
int isValidCredentials(int userid, char *password){ 
	
	int flg = 0;
	char str[100];
	
	FILE *fptr;
	fptr = fopen("receptionist_details.txt","r"); /* Opening a file in read mode */
	
	if(fptr == NULL){
		printf("\nError! Cannot Open File...\n");
		exit(1);
	}
	
	while(fgets(str,sizeof(str),fptr) != NULL){
		char* token = strtok(str,",");
		int r_id = atoi(token); // convert string to int;
		if(r_id == userid){ 
			token = strtok(NULL,",");
			if(strcmp(token,password) == 0){
				flg = 1;
				break;
			}
		}
	}
	
	fclose(fptr);
	return flg;
}

/* Function to invoke Receptionist Module (Description for parameter type)*/
void GetReceptionist(){
	
	int rec_id,valid=0;
	char password[20];
	
	do{
		printf("\n\nEnter userID : ");
		scanf("%d",&rec_id);
		
		printf("Enter password : ");
		scanf("%s",password);
		password[strlen(password)] = '\0';
	
		valid = isValidCredentials(rec_id,password);
		
		if(valid){
			printf("\nLogin Successfull\n\n");
			displayMenu(); 
		}
		else{
			printf("\nEnter valid Username/Password");
		}
	}
	while(!valid);
}	
