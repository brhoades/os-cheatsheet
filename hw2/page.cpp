#include "page.h"

Page::Page( )
{
  m_accessed = m_loaded = m_contents = 1;
  m_owner = NULL;
  m_clock = false;
}

Page::Page( unsigned int num ) : m_num( num )
{
  m_loaded = m_accessed = m_contents = 1;
  m_owner = NULL;
  m_clock = false;
}

void Page::update( unsigned int word, unsigned long PC, Program* p )
{
  if( m_owner != NULL )
  {
    // remove ourself from our old owner's jump table
    // cerr << "old owner: " << m_owner->num( ) << "\tcon: " << m_contents << " -> " << m_owner->m_jump[m_contents] << endl;
    m_owner->m_jump[m_contents] = -1;
  }

  m_contents = word;
  m_owner = p;

  p->m_jump[m_contents] = m_num;
  //cerr << "new owner: " << m_owner->num( ) << "\tcon: " << m_contents << " -> " << m_owner->m_jump[m_contents] << endl;

  m_clock = true;
  m_accessed = PC;
  m_loaded = PC;
}

void Page::update( unsigned long PC )
{
  m_accessed = PC;
  m_clock = true;
}

Page& Page::operator=( unsigned int rhs )
{
  m_contents = rhs;

  return *this;
}
