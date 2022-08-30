//Definition file for doctor from admin
#include"doctor_a.h"

int id_count=100; //Global variable to generate the userId



//Function to create a node for the linked list
//Paramaters: structure variable of doctor and returns the new node created

d_node* create_node(doctor d)
{
	d_node *newnode= (d_node*)malloc(sizeof(d_node));
	
	newnode->doc.userId=d.userId;
	strcpy(newnode->doc.password,d.password);
	strcpy(newnode->doc.name,d.name);
	strcpy(newnode->doc.gmail,d.gmail);
	newnode->doc.phone_no=d.phone_no;
	newnode->doc.shift_time=d.shift_time;
	id_count=d.userId;
	
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
    }

   return head;
}


//Function to display the doctor details
//Paramaters: integer, head pointer of the linked list and  no return type

void display_doctor(int id,d_node *head)
{
	int check=0;
		d_node *temp=head;
		
		while(temp!=NULL && id!=temp->doc.userId)
		{
			temp=temp->next;
			
		}
		
		if(temp!=NULL)
			printf("\nDetails of the doctore are :\n%d %s %s %s %ld %d\n",temp->doc.userId, temp->doc.password, temp->doc.name, temp->doc.gmail, temp->doc.phone_no, temp->doc.shift_time);
		else
			printf("\nNo doctor exists with the ID you entered.\n");
}




//Function to update a record using user Id 
//Paramaters: integer and head pointer of the linked list and return type: head pointer of the updated list

d_node* update_doctor(int id,d_node* head)
{
	d_node *temp=head;
	int shift_time;
	char name[20],gmail[20],password[20];
	long phone_no;
	
		
	while(temp!=NULL && id!=temp->doc.userId)
		{
			temp=temp->next;
			
		}
		
	if(temp!=NULL)
	{
			printf("\nEnter new details of the doctor :\n");
			printf("\nPassword: ");
			scanf("%s",password);
			printf("\nName: ");
			scanf("%s",name);
			printf("\nGmail: ");
			scanf("%s",gmail);
			printf("\nPhone number: ");
			scanf("%ld",&phone_no);
			printf("\nShift time: ");
			scanf("%d", &shift_time);
			
			strcpy(temp->doc.password,password);
			strcpy(temp->doc.name,name);
			strcpy(temp->doc.gmail,gmail);
			temp->doc.phone_no=phone_no;
			temp->doc.shift_time=shift_time;
	}
			
			
	else
			printf("\nNo doctor exists with the ID you entered.\n");
		
	return head;
}



//Function to delete a record using user Id 
//Paramaters: integer and head pointer of the linked list and return type: head pointer of the updated list

d_node* delete_doctor(int id,d_node *head)
{
	
		d_node *temp=head;
		d_node *temp2;
		
		if(temp->doc.userId==id)
		{
			head=head->next;
			free(temp);
			temp=NULL;
			printf("\nDeletion succesful\n");
			return head;
		}
		while(temp!=NULL && id!=temp->next->doc.userId)
		{
			temp=temp->next;
			
		}
		
		if(temp!=NULL)
		{
			temp2=temp->next;
			temp->next=temp->next->next;
			free(temp2);
			temp2=NULL;
			printf("\nDeletion succesful\n");
			
		}
		else
			printf("\nNo doctor exists with the ID you entered.\n");
		
		return head;
	
}
	
	
//Function to load the contents from the linked list and store into the file after all the operations
//Paramaters: file pointer and head pointer of the linked list and  returns the file pointer


FILE* write_to_file(FILE *dptr2, d_node *head)
{
	d_node *temp=head;
	
	while(temp!=NULL)
	{
		fprintf(dptr2,"%d %s %s %s %ld %d\n",temp->doc.userId, temp->doc.password,temp->doc.name,temp->doc.gmail,temp->doc.phone_no,temp->doc.shift_time);
		temp=temp->next;
	}
	
	return dptr2;
	
}
	