all: doctor_output_a

doctor_output_a: doctor_def_a.o doctor_client_a.o
	gcc doctor_a.h doctor_def_a.c doctor_client_a.c -o doctor_output_a
	
doctor_def_a.o: doctor_def_a.c
	gcc -c doctor_def_a.c
	
doctor_client_a.o: doctor_client_a.c
	gcc -c doctor_a.h doctor_client_a.c