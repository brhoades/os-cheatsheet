/*******************************************
 * Student:    Billy J Rhoades II
 * Username:   bjrq48
 * Class:      CS5201
 * Assignment: 2 
 * File:       page.h
 ******************************************/
#ifndef PAGE_H 
#define PAGE_H

#include <ctime>
#include <map>
#include <iostream>
#include "program.h"

class Program;

using namespace std;

class Page
{
  public:
    Page( );
    Page( unsigned int );

    void update( unsigned int word, unsigned long PC, Program* p ); // Page has been loaded
    void update( unsigned long PC ); // Page was read

    Page& operator=( unsigned int );

    unsigned long m_accessed, m_contents, m_loaded;
    unsigned int m_num;
    
    Program* m_owner;

    bool m_clock;
};


#endif
