/* This file name is "doctor.h"
It contains the declarations of functions that will be performed by doctor
*/

//including the required libraries into this header fille
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//declaring a structure date which can be useful to store the dates
typedef struct date
{
	int day;
	int mon;
	int yr;
}dt;

//declaring a structure for appointment to store it's attributes
typedef struct Appointment
{
	int apt_id,pat_id,doc_id;
	char doc_fname[20];
	char doc_lname[20];
	char pat_fname[20];
	char pat_lname[20];
	char dept_name[20];
	char apt_dt[20];
	char apt_t[20];
}appointment;


//declaring a structure for doctor to store all his attributes
typedef struct Doctor
{
	int userId;
	char password[20];
	char name[20];
	char gmail[20];
	long phone_no;
	int shift_time;
	int dept_id;
	
}doctor;
	
//declaring a structure Doctor_LL which has nested structure of Doctor to perform the update operations using LL
typedef struct Doctor_LL
{
	doctor doc;
	struct Doctor_LL *next;

}d_node;


//Function to create a node for the linked list
//Paramaters: structure variable of doctor and returns the new node created
d_node* create_node(doctor);


//Function to add a node to the linked list
//Paramaters: 2 pointers of linked list
d_node* add_node(d_node*,d_node*);


//Function to update a record using user Id 
//Paramaters: integer and head pointer of the linked list and return type: head pointer of the updated list
d_node* update_doctor(int,d_node*);


//Function to load the contents from the linked list and store into the file after all the operations
//Paramaters: file pointer and head pointer of the linked list and  returns the file pointer
FILE* write_to_file(FILE*, d_node*);

//declaring the function "validate_date" to validate the date given by the doctor
//takes date string as a parameter
int validate_date(char[]);

//declaring the function "display" to display the appointment details according to a particular date
//takes int(doctor ID) as a parameter
void display(int);


//declaring the function "update_hours" to update the availability hours of doctor
//takes int(doctor ID) as a parameter
d_node* update_hours(int);


//declaring the function "menu" which is used by the doctor for login and further options
void menu();


//declaring the function "validate_login" to check for correct or invalid login details
int validate_login(int,char[]);
