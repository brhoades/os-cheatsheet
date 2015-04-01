#include "program.h"

Program::Program( ) { }

Program::Program( const unsigned int num, const unsigned pageNum, const unsigned int numPages )
{
  m_num = num;
  m_numPages = numPages;
  m_firstPage = pageNum;

  m_memory = new int[numPages];

  for( int i=0; i<numPages; i++ )
    m_memory[i] = -1;

  m_clockPointer = 0;
}

unsigned int Program::firstPage( ) const
{
  return m_firstPage;
}

unsigned int Program::lastPage( ) const
{
  return m_firstPage + m_numPages;
}

unsigned int Program::numPages( ) const
{
  return m_numPages;
}

unsigned int Program::num( ) const
{
  return m_num;
}

Program& Program::operator=( const Program& rhs )
{
  m_firstPage = rhs.firstPage( );
  m_numPages = rhs.numPages( );
  m_num = rhs.num( );

  m_clockPointer = rhs.m_clockPointer;

  m_memory = new int[m_numPages];

  for( unsigned int i=0; i<m_numPages; i++ )
    m_memory[i] = rhs.m_memory[i]; 

  return *this;
}

Program::~Program( )
{
  delete[] m_memory;
}
