#include "page.h"

Page::Page( )
{
  m_owner = m_used = 0;

  m_accessed = time( NULL );
}

void Page::update( )
{
  m_accessed = time( NULL );
}
