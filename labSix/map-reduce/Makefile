#Nojus Satikauskas 21/11/2023
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

#this compiles sets of files
REDUCE: reduction.o
	$(CC) -o reduce.out reduction.o $(CFLAGS) $(DEBUGFLAGS)

#This applies the first Debug rule
DREDUCE: DEBUGFLAGS = -g -O0
#This applies Debug to REDUCE
DREDUCE: REDUCE

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
