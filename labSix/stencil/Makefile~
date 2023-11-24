#Joseph Kehoe 13/9/2017
#Simple Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

CFILES= stencil.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

STENCIL: stencil.o
	$(CC) -o stencil.out stencil.o $(CFLAGS) $(DEBUGFLAGS)

MANDEL: mandelbroit.o
	$(CC) -o mandelbroit.out mandelbroit.o $(CFLAGS) $(DEBUGFLAGS)


DSTENCIL: DEBUGFLAGS = -g -O0
DSTENCIL: STENCIL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
