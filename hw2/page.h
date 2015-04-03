#ifndef PAGE_H 
#define PAGE_H

#include <ctime>

using namespace std;

class Page
{
  public:
    Page( );
    void update( unsigned int PC );

    Page& operator=( unsigned int );

    unsigned int m_accessed, m_contents, m_loaded;

    bool m_clock;
};


#endif
