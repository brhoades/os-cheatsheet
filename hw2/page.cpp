#include "page.h"

Page::Page( )
{
  m_loaded = m_owner = m_accessed = m_contents = 0;
  m_clock = true;
}

void Page::update( unsigned int PC )
{
  m_accessed = PC;
  m_clock = true;
}

Page& Page::operator=( unsigned int rhs )
{
  m_contents = rhs;

  return *this;
}
