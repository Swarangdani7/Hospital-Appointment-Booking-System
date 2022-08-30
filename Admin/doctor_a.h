//Header file for doctor from admin

#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct Doctor{

	int userId;
	char password[20];
	char name[20];
	char gmail[20];
	long phone_no;
	int shift_time;
	
	}doctor;
	
typedef struct Doctor_LL{

	doctor doc;
	struct Doctor_LL *next;

}d_node;




//Function to create a node for the linked list
//Paramaters: structure variable of doctor and returns the new node created

d_node* create_node(doctor);


//Function to add a node to the linked list
//Paramaters: 2 pointers of linked list

d_node* add_node(d_node*,d_node*);

//Function to display the doctor details
//Paramaters: integer, head pointer of the linked list and  no return type

void display_doctor(int id,d_node*);



//Function to update a record using user Id 
//Paramaters: integer and head pointer of the linked list and return type: head pointer of the updated list
d_node* update_doctor(int,d_node*);


//Function to delete a record using user Id 
//Paramaters: integer and head pointer of the linked list and return type: head pointer of the updated list

d_node* delete_doctor(int,d_node*);


//Function to load the contents from the linked list and store into the file after all the operations
//Paramaters: file pointer and head pointer of the linked list and  returns the file pointer

FILE* write_to_file(FILE*, d_node*);
