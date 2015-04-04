/*******************************************
 * Student:    Billy J Rhoades II
 * Username:   bjrq48
 * Class:      CS5201
 * Assignment: 2 
 * File:       main.cpp
 ******************************************/
#include <iostream>
#include "memorysimulator.h"

using namespace std;

int main( int argc, char* argv[] )
{
  MemorySimulator sim( argc, argv );

  sim.run( );

  cout << "Total Page Faults: " << sim.pageFaults( ) << endl;
  cout << "========================" << endl;

  return 0;
}
