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

/* Structure for Receptionist */
typedef struct receptionist{
	int receptionist_id;
	char passwd[20]; 
	char receptionist_name[30];  
	long phone_no; 
	shift receptionist_shiftTime;
	struct Receptionist* next;
}rec;

/* Structure for Appointment Details */
typedef struct appointmentDetails{
	int appointmentID;
    int patientID;
    int doctorID;
    Date dt;
    struct appointmentDetails* next;
}appointment;

/* Function declarations */

void GetReceptionist(); /* function to invoke Receptionist */
void displayMenu(); /* Function to display Menu */
int isValidCredentials(int,char*); /* function to check if username and password entered is correct or not */
void Display_Appointment(); /* function to book an Appointment for patient */
void Cancel_Appointment(); /* function to Cancel an Appointment */
int isValidAppointment(int); /* function to check if Appointment ID entered is correct or not */
appointment* acceptAppointmentDetails(appointment*); /* function to accept Appointment Details */
appointment* removeNode(appointment*,int); /* function to delete Record associated with Appointment ID */

