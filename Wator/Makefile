#Nojus Satikauskas (C00261186)
#30/11/2023
#License: GNU GENERAL PUBLIC LICENSE
#Git Url: https://github.com/N090/Concurrent-Dev./tree/main

CXX = g++
CPPFILES = wator.cpp
CPPFLAGS = -Wall -I/path/to/sfml/include -fopenmp
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lgomp
EXE = watorApp

SRCS = wator.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

# This rule says that each .o file depends on a .cpp file of the same name
# This is actually built into Make but anyways...
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)
