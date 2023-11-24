#Nojus Satikauskas 15/11/2023
#License: GNU GENERAL PUBLIC LICENSE
#GIT URL: https://github.com/N090/Concurrent-Dev./tree/main

CC=g++
CFLAGS= -std=c++11 -pthread -I. -Wall
CPPFILES=Barrier.cpp main.cpp Semaphore.cpp
HFILES=Barrier.h Semaphore.h
OBJFILES=Barrier.o main.o Semaphore.o

#makes it so that .o files require .cpp files of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#Compiling file sets into an executible called barrier
BARRIER: $(OBJFILES) $(HFILES)
	$(CC) -o barrier $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS) 

#Setting Debug Flags as the first step of the debug rule
DEBUG: DEBUGFLAGS = -g -O0
#Setting Debug to all files contained in BARRIER
DEBUG: BARRIER

#Deletes all OBJFILES
CLEAN:
	rm $(OBJFILES)
