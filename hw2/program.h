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

    unsigned int firstPage( ) const;
    unsigned int lastPage( ) const;
    unsigned int numPages( ) const;
    unsigned int num( ) const;

    // Each program's individual clock pointer
    unsigned int m_clockPointer;

    // lookup table, absolute page -> index in m_memory
    map<unsigned int,int> m_jump;

    unsigned int m_num, m_numPages, m_firstPage;

};

#endif
