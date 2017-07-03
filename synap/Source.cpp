#include <iostream>

#include "Neuron.h"
#include "Layer.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main( )
{
  srand( static_cast<unsigned int>(time( nullptr )) );

  /*Neuron* A = new Neuron( );
  Neuron* B = new Neuron( );

  A->project( B );

  float a = A->activate( 0.5f );
  float b = B->activate( );

  std::cout << "[" << a << ", " << b << "]" << std::endl;*/

  /*Layer* A = new Layer( 5 );
  Layer* B = new Layer( 3 );
  auto res = A->project( B, Layer::Connection::Type::ALL_TO_ALL );

  auto res2 = A->activate( { 1.0f, 0.0f, 1.0f, 0.0f, 1.0f } );
  auto res3 = B->activate( );*/

  Layer* inputLayer = new Layer( 2 );
  Layer* hiddenLayer = new Layer( 3 );
  Layer* outputLayer = new Layer( 1 );

  inputLayer->project( hiddenLayer );
  hiddenLayer->project( outputLayer );

  system( "PAUSE" );

  return 0;
}