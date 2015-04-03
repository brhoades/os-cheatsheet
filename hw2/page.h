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

    void update( unsigned int word, unsigned int PC, Program* p ); // Page has been loaded
    void update( unsigned int PC ); // Page was read

    Page& operator=( unsigned int );

    unsigned int m_accessed, m_contents, m_loaded, m_num;
    
    Program* m_owner;

    bool m_clock;
};


#endif
