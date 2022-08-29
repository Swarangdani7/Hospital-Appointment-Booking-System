/* info.txt file contains username followed by password. Whitespace is used as a delimiter */

#include "receptionist.h"

/* Function to validate Username and Password */
int isValid(char *username, char *password){ 
	
	FILE *fptr;
	fptr = fopen("details.txt","r"); /* Opening a file in read mode */
	
	char arr1[20],arr2[20];
	fscanf(fptr,"%s",arr1);
	fscanf(fptr,"%s",arr2);
	
	arr1[strlen(arr1)] = '\0';
	arr2[strlen(arr2)] = '\0';
	
	if(strcmp(username,arr1) == 0 && strcmp(password,arr2) == 0){
		return 1;
	}
	else{
		return 0;
	}
	fclose(fptr);
}

/* Function to invoke Receptionist Module (Description for parameter type)*/
void GetReceptionist(){
	char username[20],password[20];
	int valid;
	
	do{
		printf("\n\nEnter username : ");
		fgets(username,20,stdin);
		username[strlen(username)-1] = '\0';
		
		printf("Enter password : ");
		fgets(password,20,stdin);
		password[strlen(password)-1] = '\0';
	
		valid = isValid(username,password);
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

void displayMenu(){
	int ch;
	
	do{
		printf("\n\n\t------------------------Menu------------------------");
		printf("\n\t\t\t1. Book Appointment\n\
			2. Cancel Appointment\n\
			3. Display Appointment\n\
			0. Exit\n");
			
		printf("\n\tEnter your choice :: ");
		scanf("%d",&ch);
		
		switch(ch){
			case 1:
				// Book_Appointment();
				break;
			case 2:
				// Cancel_Appointment();
				break;
			case 3:
				//Display_Appointment();
				break;
			case 0:
				exit(0);
		}
	}
	while(ch != 0);
}
	
