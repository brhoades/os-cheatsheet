#ifndef MEMORY_SIMULATOR_H
#define MEMORY_SIMULATOR_H

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
    void handleFault( Program& p, unsigned int word );

    //void lru( unsigned int );

    unsigned int lastPage( ) const;

    unsigned int pageFaults( ) const;

  private:
    unsigned int m_frames, m_rAlgo, m_PC, m_pageFaults;
    bool m_pagePolicy;

    fstream m_progList, m_progTrace;

    Program* m_programs;
    Page* m_memory;

    unsigned int m_numPrograms;
    unsigned int m_pageSize;
    unsigned int m_lastPage;
};

#endif
