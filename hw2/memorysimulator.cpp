#include "memorysimulator.h"

MemorySimulator::MemorySimulator( int argc, char* argv[] )
{
  if( argc <= 6 )
    throw domain_error( "Simulator must have all six arguments specified" );

  m_programName = argv[1];

  m_progList.open( argv[2] );
  if( !m_progList )
  {
    cerr << "Program list file provided does not appear to exist" << endl;
    throw domain_error( "File not found" );
  }

  m_progTrace.open( argv[3] );
  if( !m_progTrace )
  {
    cerr << "Program trace file provided does not appear to exist" << endl;
    throw domain_error( "File not found" );
  }

  m_pageSize = atoi( argv[4] );

  if( m_pageSize <= 0 || m_pageSize > AVAILABLE_FRAMES )
    throw domain_error( "Page size is not within range ( > 0 but < AVAILABLE_FRAMES )" );
    
  if( (float) sqrt( m_pageSize ) - sqrt( m_pageSize ) != 0 )
    throw domain_error( "Page size is not a multiple of two." );

  if( !strcmp( "clock", argv[5] ) || !strcmp("c", argv[5] ) )
    m_rAlgo = ALGO_CLOCK;
  else if( !strcmp("lru", argv[5] ) || !strcmp("l", argv[5] ) )
    m_rAlgo = ALGO_LRU;
  else if( !strcmp("f", argv[5] ) || !strcmp("fifo", argv[5] ) )
    m_rAlgo = ALGO_FIFO;
  else
    throw domain_error( "Unknown page replacement algorithm specified" );

  m_pagePolicy = argv[5];

  m_frames = AVAILABLE_FRAMES / m_pageSize;

  m_programs = NULL;
  m_numPrograms = 0;

  readPrograms( );
}

MemorySimulator::~MemorySimulator( )
{
  m_progList.close( );
  m_progTrace.close( );

  delete[] m_programs;
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
    m_progList >> num, numPages;

    if( i != 0 )
      m_programs[i] = Program( num, 0, numPages );
    else
      m_programs[i] = Program( num, m_programs[i-1].lastPage( ), numPages ); 
  }
}

unsigned int MemorySimulator::lastPage( ) const
{
  return m_lastPage;
}
