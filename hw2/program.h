#ifndef PROGRAM_H 
#define PROGRAM_H

#include <cmath>
#include "page.h"

using namespace std;

class Program
{
  public:
    Program( );
    Program( const unsigned int, const unsigned int, const unsigned int ); 
    ~Program( );

    Program& operator=( const Program& );

    unsigned int firstPage( ) const;
    unsigned int lastPage( ) const;
    unsigned int numPages( ) const;
    unsigned int num( ) const;
    unsigned int m_mm_first, m_mm_last; // where our pages are in main memory

    unsigned int m_clockPointer;

    //lookup table
    int* m_memory;

    unsigned int m_num, m_numPages, m_firstPage;

};

#endif
