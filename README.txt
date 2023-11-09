FILE:       README.txt
AUTHOR:     George Devean Sinining
PURPOSE:    To explain how to compile and run the program.

----------------------
How to compile program
----------------------
Making the program:
    Command:    make

The command above when entered into the terminal will compile and link all the 
files needed to make the executable/program named 'diskSimulator'.

----------------------
How to execute program
----------------------

Once you 'make' the program, enter the following command to execute the program.

  ./diskSimulator

Additionally, if you would like to check for memory leaks, you can enter
the following.

  valgrind ./diskSimulator

----------------------
How to clean directory
----------------------
Cleaning Directory:
    Command:    make clean

This will delete all the .o files and the executable associated with the 
program, but will leave all the .c and .h files.