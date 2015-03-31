#ifndef PROGRAM_H 
#define PROGRAM_H

#include <cmath>

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


  private:
    unsigned int m_num, m_numPages, m_firstPage;
};

#endif
