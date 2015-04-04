/*******************************************
 * Student:    Billy J Rhoades II
 * Username:   bjrq48
 * Class:      CS5201
 * Assignment: 2 
 * File:       program.h
 ******************************************/
#ifndef PROGRAM_H 
#define PROGRAM_H

#include <cmath>
#include <map>
#include "page.h"

using namespace std;

class Program
{
  public:
    Program( );
    Program( const unsigned int, const unsigned int, const unsigned int ); 
    ~Program( );

    Program& operator=( const Program& );

    // lookup table, absolute page -> index in m_memory
    map<unsigned int,int> m_jump;

    // our number of pages, our number in the program list, and out first page
    unsigned int m_num, m_numPages, m_firstPage;
};

#endif
