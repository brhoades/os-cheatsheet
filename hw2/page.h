#ifndef PAGE_H 
#define PAGE_H

#include <ctime>

using namespace std;

class Page
{
  public:
    Page( );
    void update( unsigned int PC );

    unsigned int m_owner, m_accessed, m_contents;
    bool m_used;
};


#endif
