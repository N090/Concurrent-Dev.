#Nojus Satikauskas 11/10/2023
#License: GNU GENERAL PUBLIC LICENSE
#Git Url: https://github.com/N090/Concurrent-Dev./tree/main


CC=g++
CFLAGS= -std=c++11 -pthread
HELLOFILES= helloThreads.o Semaphore.o
MUTUALFILES= mutualEx.o Semaphore.o

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#Compiling two sets of files, because we are compiling two seperate projects
HELLO: $(HELLOFILES) $(MUTUALFILES)
	$(CC) -o helloThreads $(HELLOFILES) $(CFLAGS) $(DEBUGFLAGS)
	$(CC) -o mutualEx $(MUTUALFILES) $(CFLAGS) $(DEBUGFLAGS)

#Setting Debug Flags as the first step of the debug rule
DEBUG: DEBUGFLAGS = -DDEBUG
#Setting Debug all to debug the rest of the files
DEBUG: ALL

#this just deletes all .o files
CLEAN:
	rm *.o
