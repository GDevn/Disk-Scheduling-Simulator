##
 # File: Makefile
 # Author: George Devean Sinining
 # -----
 # Purpose: Makefile to allow ease of compilation of program, as well as cleaning program of
 #			.o files. 
##


# Makefile Variables
CC		 = gcc
EXEC	 = diskSimulator
CFLAGS = -pthread -Wall -ansi -pedantic
OBJ 	 = main.o fileIO.o scheduler.o simulator.o util.o 

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o : main.c simulator.h
	$(CC) $(CFLAGS) main.c -c

fileIO.o : fileIO.c fileIO.h
	$(CC) $(CFLAGS) fileIO.c -c

scheduler.o : scheduler.c scheduler.h util.h
	$(CC) $(CFLAGS) scheduler.c -c

simulator.o : simulator.c simulator.h util.h scheduler.h fileIO.h
	$(CC) $(CFLAGS) simulator.c -c

util.o : util.c util.h
	$(CC) $(CFLAGS) util.c -c

clean:
	rm -f $(EXEC) $(OBJ)