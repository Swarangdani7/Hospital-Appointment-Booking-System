//client file for doctor from admin

#include"doctor_a.h"

int main()
{
	int id,choice;
	doctor doc;
	char name[20],pass[20];
	d_node *head,*temp,*newnode;
	head=NULL;
	temp=NULL;
	FILE *dptr,*dptr2;
	extern int id_count;
	dptr=fopen("Doctors_sample.txt","r");
	
	
	//Reading data from the file to linked list
	
	while(fscanf(dptr,"%d %s %s %s %ld %d\n",&doc.userId,doc.password,doc.name,doc.gmail,&doc.phone_no,&doc.shift_time)!=-1)
	{
		//printf("\n%d,%s,%s,%s,%ld,%d\n",doc.userId,doc.password,doc.name,doc.gmail,doc.phone_no,doc.shift_time);
		newnode=create_node(doc);
		head=add_node(head,newnode);
	}
	
	fclose(dptr);
	
	
	//do while loop runs until the user enters zero value
	
 do{
		
	printf("\n_ _ _ _ _ _ _ _ _ _ _ _ MENU _ _ _ _ _ _ _ _ _ _ _ _\n");
	printf("\nChoose your choice :\n1. Add Doctor\n2. Update Doctor\n3. Display doctor\n4. Delete Doctor\n0. Exit\n");
	scanf("%d",&choice);
	
	if(choice==1)
	{
		printf("\nEnter the details to add a doctor:\n");
		
		doc.userId=++id_count;
	    
		printf("\nPassword: ");
		scanf("%s",doc.password);
		printf("\nName: ");
		scanf("%s",doc.name);
		printf("\nEmail: ");
		scanf("%s",doc.gmail);
		printf("\nPhone number: ");
		scanf("%ld",&doc.phone_no);
		printf("\nShift time: ");
		scanf("%d",&doc.shift_time);
		newnode=create_node(doc);
		head=add_node(head,newnode);
		
		printf("\nDoctor with user id %d is added.\n",doc.userId);
	}
	
	else if(choice==2)
	{
		printf("\nEnter the Id to update the details of the doctor\n");
	
		scanf("%d",&id);
		head=update_doctor(id,head);
		
	}
	
	else if(choice==3)
	{
		printf("\nEnter the doctor Id to display the details:\n");
	
		scanf("%d",&id);
		display_doctor(id,head);
	}
	
	else if(choice==4)
	{
		printf("\nEnter the doctor id to delete the record\n");
		scanf("%d",&id);
		head=delete_doctor(id,head);
		
	}
	
	else if(choice==0)
	{
		dptr2=fopen("doctors_sample.txt","w");
	
		dptr2=write_to_file(dptr2,head);
		fclose(dptr2);
	
		printf("\nExited\n");
		exit(0);
		
	}
	
	else
		printf("\nEnter valid choice\n");
	printf("\n");
    
	}while(choice!=0);
	
	
	
	
	
	
	
}