#include <iostream>

#include "Neuron.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main( )
{
  srand( static_cast<unsigned int>(time( nullptr )) );

  Neuron* A = new Neuron( );
  Neuron* B = new Neuron( );

  A->project( B );

  float a = A->activate( 0.5f );
  float b = B->activate( );

  std::cout << "[" << a << ", " << b << "]" << std::endl;

  system( "PAUSE" );

  return 0;
}