#02/10/2023
#Nojus Satikauskas
CC=g++
CPPFILES=Barrier.cpp main.cpp Semaphore.cpp
HFILES=Barrier.h Semaphore.h
OBJFILES=Barrier.o main.co Semaphore.o
CFLAGS= -std=c++11 -pthread -I.
EXE=barrier

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(OBJFILES) $(HFILES)
	$(CC) -o $(EXE) $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES) $(EXE)
INSTALL:
	cp ./barrier /user/bin/barrier
