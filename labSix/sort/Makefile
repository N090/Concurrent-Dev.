#Nojus Satikauskas 21/11/2023
#Simple Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

CPPFILES= quicksort.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#This compiles a set of files
QUICK: quicksort.o
	$(CC) -o qsort.out quicksort.o $(CFLAGS) $(DEBUGFLAGS)

#This applies the first Debug rule
DSORT: DEBUGFLAGS = -g -O0
#This Debugs the files contained in Quick
DSORT: QUICK

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
