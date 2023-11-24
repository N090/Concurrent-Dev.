#Joseph Kehoe 13/9/2017
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

QUICK: quicksort.o
	$(CC) -o qsort.out quicksort.o $(CFLAGS) $(DEBUGFLAGS)


DSORT: DEBUGFLAGS = -g -O0
DSORT: QUICK

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
