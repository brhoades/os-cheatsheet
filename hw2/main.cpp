#include <iostream>
#include "memorysimulator.h"

using namespace std;

int main( int argc, char* argv[] )
{
  MemorySimulator sim( argc, argv );

  sim.run( );

  cout << "page faults: " << sim.pageFaults( ) << endl;

  return 0;
}
