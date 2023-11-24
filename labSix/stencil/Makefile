#Nojus Satikauskas 21/11/2023
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

#this compiles one set of files 
STENCIL: stencil.o
	$(CC) -o stencil.out stencil.o $(CFLAGS) $(DEBUGFLAGS)

#this compiles another set of files following the above set
MANDEL: mandelbroit.o
	$(CC) -o mandelbroit.out mandelbroit.o $(CFLAGS) $(DEBUGFLAGS)

#This applies the first Debug rule
DSTENCIL: DEBUGFLAGS = -g -O0
#This Debugs the files contained the files in Stencil
DSTENCIL: STENCIL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
