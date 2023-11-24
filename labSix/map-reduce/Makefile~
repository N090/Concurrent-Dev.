#Joseph Kehoe 13/9/2017
#Simple Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

CPPFILES= reduction.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) -lgomp  $(DEBUGFLAGS)

REDUCE: reduction.o
	$(CC) -o reduce.out reduction.o $(CFLAGS) $(DEBUGFLAGS)


DREDUCE: DEBUGFLAGS = -g -O0
DREDUCE: REDUCE

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
