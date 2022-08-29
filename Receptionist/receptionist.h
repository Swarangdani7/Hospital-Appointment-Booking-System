#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct date{
	int day,mon,year,hrs,min,sec;
}Date;

typedef struct shiftTime{
	Date start;
	Date finish;
}shift;

/* creating a linked list to store multiple records */
typedef struct receptionist{
	char userid[20]; 
	char passwd[20]; 
	char receptionist_name[30]; 
	long receptionist_id; 
	long phone_no; 
	shift receptionist_shiftTime;
	struct Receptionist* next;
}rec;

/* Function declarations */

void GetReceptionist(); /* function to invoke Receptionist */
void displayMenu(); /* Function to display Menu */
int isValid(char*,char*); /* function to check if username and password entered is correct or not */

