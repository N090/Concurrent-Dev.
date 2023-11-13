#Nojus Satikauskas 09/11/2023
#License: GNU GENERAL PUBLIC LICENSE
#Git Url: https://github.com/N090/Concurrent-Dev./tree/main

CC=g++
CFLAGS= -std=c++11 -pthread -Wall
RENDFILES=rendezvous.o Semaphore.o

#makes it so that .o files require .cpp files of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#Compiling main set of files 
REND:	 $(RENDFILES)
	$(CC) -o rendezvous $(RENDFILES) $(CFLAGS) $(DEBUGFLAGS)

#Setting Debug Flags as the first step of the debug rule
DEBUG: DEBUGFLAGS = -DDEBUG
#Setting Debug to all files contained in REND 
DEBUG: REND

#Deletes all .o files
CLEAN:
	rm *.o
