/*******************************************
 * Student:    Billy J Rhoades II
 * Username:   bjrq48
 * Class:      CS5201
 * Assignment: 2
 * File:       memorysimulator.h
 ******************************************/
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h> 
#include "program.h"
#include "page.h"

#define ALGO_CLOCK 0
#define ALGO_LRU   1
#define ALGO_FIFO  2

#define POLICY_DEMAND    0
#define POLICY_PREPAGING 1

#define AVAILABLE_FRAMES 512

using namespace std;

class MemorySimulator
{
  public:
    MemorySimulator( int, char* argv[] );
    ~MemorySimulator( );

    void readPrograms( );
    void prepareMemory( );

    void run( ); 
    void access( unsigned int, unsigned int );
    void handleFault( Program* p, unsigned int word, bool prepage=true );

    unsigned int lastPage( ) const;

    unsigned int pageFaults( ) const;

  private:
    unsigned long m_PC;
    unsigned int m_frames, m_rAlgo, m_pageFaults, m_clockPointer;
    bool m_prepage;

    fstream m_progList, m_progTrace;

    Program** m_programs;
    Page* m_memory;

    unsigned int m_numPrograms;
    unsigned int m_pageSize;
    unsigned int m_lastPage;
};
