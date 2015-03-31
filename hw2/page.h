#ifndef PAGE_H 
#define PAGE_H

#include <ctime>

using namespace std;

class Page
{
  public:
    Page( );
    void update( );

    unsigned int m_owner;
    time_t m_accessed;
    bool m_used;
};


#endif
