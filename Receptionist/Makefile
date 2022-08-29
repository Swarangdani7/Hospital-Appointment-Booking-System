all: rec_op

rec_op: client.o receptionist_def.o
	gcc client.o receptionist_def.o -o rec_op

receptionist_def.o: receptionist_def.c
	gcc -c receptionist_def.c
		
client.o: client.c
	gcc -c client.c
	
clean:
	rm *.o rec_op
 
