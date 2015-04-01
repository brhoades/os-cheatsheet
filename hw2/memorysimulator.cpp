#include "memorysimulator.h"

MemorySimulator::MemorySimulator( int argc, char* argv[] )
{
  if( argc < 6 )
    throw domain_error( "Simulator must have all six arguments specified" );

  m_progList.open( argv[1] );
  if( !m_progList )
  {
    cerr << "Program list file provided does not appear to exist" << endl;
    throw domain_error( "File not found" );
  }

  m_progTrace.open( argv[2] );
  if( !m_progTrace )
  {
    cerr << "Program trace file provided does not appear to exist" << endl;
    throw domain_error( "File not found" );
  }

  m_pageSize = atoi( argv[3] );

  if( m_pageSize <= 0 || m_pageSize > AVAILABLE_FRAMES )
    throw domain_error( "Page size is not within range ( > 0 but < AVAILABLE_FRAMES )" );
    
  if( pow( 2, (int)log2( m_pageSize ) ) != pow( 2, log2( m_pageSize ) ) )
    throw domain_error( "Page size is not a power of two." );

  if( !strcmp( "clock", argv[4] ) || !strcmp("c", argv[4] ) )
    m_rAlgo = ALGO_CLOCK;
  else if( !strcmp("lru", argv[4] ) || !strcmp("l", argv[4] ) )
    m_rAlgo = ALGO_LRU;
  else if( !strcmp("f", argv[4] ) || !strcmp("fifo", argv[4] ) )
    m_rAlgo = ALGO_FIFO;
  else
    throw domain_error( "Unknown page replacement algorithm specified" );

  m_prepage = bool( atoi( argv[5] ) );

  m_frames = AVAILABLE_FRAMES / m_pageSize;

  m_programs = NULL;
  m_numPrograms = 0;

  m_pageFaults = 0;

  m_PC = 0;

  m_memory = NULL;

  readPrograms( );
  prepareMemory( );
}

MemorySimulator::~MemorySimulator( )
{
  m_progList.close( );
  m_progTrace.close( );

  delete[] m_programs;

  delete[] m_memory;
}

void MemorySimulator::readPrograms( )
{
  string trash;

  // figure out how many programs we're making
  while( getline( m_progList, trash ) ) 
    m_numPrograms++;

  m_programs = new Program[m_numPrograms];

  m_progList.clear( );
  m_progList.seekg( 0, ios::beg );

  for( unsigned int i=0; i<m_numPrograms; i++ )
  {
    unsigned int num, numPages;  
    m_progList >> num >> numPages;

    if( i == 0 )
      m_programs[i] = Program( num, 0, floor( numPages / m_pageSize ) );
    else
      m_programs[i] = Program( num, m_programs[i-1].lastPage( ), floor( numPages / m_pageSize ) ); 
  }
}

void MemorySimulator::prepareMemory( )
{
  m_memory = new Page[m_frames];
  
  unsigned int memEach = floor( m_frames / m_numPrograms ); 

  for( unsigned int i=0; i<m_numPrograms; i++ )
  {
    unsigned int size = 0;
    if( m_programs[i].numPages( ) > memEach )
      size = memEach;
    else
      size = m_programs[i].numPages( );

    for( unsigned int j=0; j<size; j++ )
    {
      unsigned int num = i * memEach + j;

      m_memory[num].m_owner = i;
      m_memory[num].m_contents = m_programs[i].firstPage( ) + j;
    }
  }
}

void MemorySimulator::run( ) 
{
  // Read in instructions and execute
  while( !m_progTrace.eof( ) )
  {
    unsigned int progNum, word;

    m_PC++;
    m_progTrace >> progNum >> word;

    access( progNum, word );
  }
}

void MemorySimulator::access( unsigned int num, unsigned int word )
{
  if( num >= m_numPrograms )
  {
    stringstream ss;
    ss << "Program #" << num << " requesting word #" << word << " does not exist";
    throw domain_error( ss.str( ) );
  }

  // Adjust entries so the go to the right page for each size.
  word = floor( word / m_pageSize );

  if( word > m_programs[num].numPages( ) )
  {
    stringstream ss;
    ss << "Page #" << word << " for program #" << num << " does not exist (only has " << m_programs[num].numPages( ) << " pages)";
    throw domain_error( ss.str( ) ); 
  }

  unsigned int min = m_programs[num].firstPage( );

  // Convert word to absolute page number
  word += min;

  // Check if this page is in memory 
  for( unsigned int i=0; i<m_frames; i++ )
  {
    if( m_memory[i].m_contents == word )
    {
      m_memory[i].update( m_PC );
      return;
    }
  }

  handleFault( m_programs[num], word );
}

void MemorySimulator::handleFault( Program& p, unsigned int word )
{
  m_pageFaults++;

  unsigned int sel=p.m_mm_first;

  switch( m_rAlgo )
  {
    // Rotate through memory and remove infrequently used memory first.
    case ALGO_CLOCK:
    {
      while( true )
      {
        if( p.m_clockPointer > p.m_mm_last )
          p.m_clockPointer = p.m_mm_first;  

        if( m_memory[p.m_clockPointer].m_clock )
          m_memory[p.m_clockPointer].m_clock = false;
        else
        {
          sel = p.m_clockPointer;
          break;
        }

        p.m_clockPointer++;
      }

      p.m_clockPointer++;
      break; 
    }

    // Swap out the first page with the lowest timestamp
    case ALGO_LRU:
    {
      unsigned int min=m_memory[p.m_mm_first].m_accessed;
      for( unsigned int i=0; i<m_frames; i++ )
      {
        if( m_memory[i].m_accessed < min )
        {
          min = m_memory[i].m_accessed;
          sel = i;
        }
      }
      break; 
    }

    // Choose the oldest loaded page and replace it
    case ALGO_FIFO:
    {
      unsigned int min = m_memory[p.m_mm_first].m_loaded;
      for( unsigned int i=0; i<m_frames; i++ )
      {
        if( m_memory[i].m_loaded < min )
        {
          min = m_memory[i].m_loaded;
          sel = i;
        }

        if( min == 0 )
          break;
      }
      break; 
    }
  }

  m_memory[sel] = word;
  m_memory[sel].update( m_PC );
  m_memory[sel].m_loaded = m_PC;

  // If prepaging is emabled and we won't write in someone else's memory
  if( m_prepage && sel+1 != m_frames )
  { 
    m_memory[sel+1] = word+1;
    m_memory[sel+1].update( m_PC );
    m_memory[sel+1].m_loaded = m_PC;
  }
  else if( m_prepage )
  {
    m_memory[0] = word+1;
    m_memory[0].update( m_PC );
    m_memory[0].m_loaded = m_PC;
  }
}

unsigned int MemorySimulator::lastPage( ) const
{
  return m_lastPage;
}

unsigned int MemorySimulator::pageFaults( ) const
{
  return m_pageFaults;
}

