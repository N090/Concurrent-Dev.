#Nojus Satikauskas 17/11/2023
#License: GNU GENERAL PUBLIC LICENSE
#Git Url: https://github.com/N090/Concurrent-Dev./tree/main

CC=g++
CPPFILES=main.cpp Semaphore.cpp
HFILES=Semaphore.h
OBJFILES=main.o Semaphore.o
CFLAGS= -std=c++11 -pthread -I. -Wall

#makes it so that .o files require .cpp files of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#Compiling main set of files 
PHIL: $(OBJFILES) $(HFILES)
	$(CC) -o philosophers $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS) 

#Setting Debug Flags as the first step of the debug rule
DEBUG: DEBUGFLAGS = -DDEBUG
#Setting Debug to all files contained in PHIL 
DEBUG: PHIL

CLEAN:
	rm $(OBJFILES)
