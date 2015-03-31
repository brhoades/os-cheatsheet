#include <iostream>
#include "memorysimulator.h"

using namespace std;

int main( int argc, char* argv[] )
{
  MemorySimulator sim( argc, argv );

  sim.run( );

  return 0;
}
