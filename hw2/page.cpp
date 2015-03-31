#include "page.h"

Page::Page( )
{
  m_owner = m_used = m_accessed = 0;
}

void Page::update( unsigned int PC )
{
  m_accessed = PC;
}
