#include "program.h"

Program::Program( ) { }

Program::Program( const unsigned int num, const unsigned pageNum, const unsigned int numPages )
{
  m_num = num;
  m_numPages = numPages;
  m_firstPage = pageNum;

  for( unsigned int i=pageNum; i<pageNum+numPages; i++ )
    m_jump[i] = -1;

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
  m_jump = rhs.m_jump;

  return *this;
}

Program::~Program( )
{
}
