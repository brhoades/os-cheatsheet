####################################################
# Student:    Billy J Rhoades II
# Username:   bjrq48
# Class:      CS
# Assignment: 2 
# File: 			Makefile 
####################################################

CXX=/usr/bin/clang++
CFLAGS=-g -Wall -W -pedantic-errors

OBJECTS=memorysimulator.o \
        program.o \
        page.o \
        main.o

.SUFFIXES: .cpp

.cpp.o: $<
	$(CXX) -c $(CFLAGS) -o $@ $<

memorysimulator: $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $?

default: all

all: memorysimulator

clean: 
	-@rm -rf core > /dev/null 2>&1
	-@rm -f driver > /dev/null 2>&1
	-@rm -f $(OBJECTS) > /dev/null 2>&1

memorysimulator.o: memorysimulator.cpp memorysimulator.h program.o page.o
program.o: program.cpp program.h
page.o: page.h page.cpp
main.o: main.cpp memorysimulator.o 
