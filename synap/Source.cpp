#include <iostream>

#include "Neuron.h"
#include "Layer.h"
#include "Network.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Layers.h"
#include "Train.h"

void neuronTest( )
{
  Neuron* A = new Neuron( );
  Neuron* B = new Neuron( );

  A->project( B );

  float a = A->activate( 0.5f );
  float b = B->activate( );

  std::cout << "[" << a << ", " << b << "]" << std::endl;
}

void layerTest( )
{
  ILayer* A = new InputLayer( 5 );
  ILayer* B = new OutputLayer( 3 );
  auto res = A->project( B, ILayer::Connection::Type::ALL_TO_ALL );

  auto res2 = A->activate( { 1.0f, 0.0f, 1.0f, 0.0f, 1.0f } );
  auto res3 = B->activate( );

  std::cout << "[" << "]" << std::endl;
}

int main( )
{
  srand( static_cast<unsigned int>(time( nullptr )) );
  neuronTest( );
  layerTest( );

  /*Layer* inputLayer = new Layer( 2 );
  Layer* hiddenLayer = new Layer( 3 );
  Layer* outputLayer = new Layer( 1 );

  inputLayer->project( hiddenLayer );
  hiddenLayer->project( outputLayer );

  Network* myNetwork = new Network( inputLayer, { hiddenLayer }, outputLayer );

  float learningRate = 0.3f;

  for ( unsigned int i = 0; i < 20000; ++i )
  {
    // 0,0 => 0
    myNetwork->activate( { 0.0f, 0.0f } );
    myNetwork->propagate( learningRate, { 0.0f } );

    // 0,1 => 1
    myNetwork->activate( { 0.0f, 1.0f } );
    myNetwork->propagate( learningRate, { 1.0f } );

    // 1,0 => 1
    myNetwork->activate( { 1.0f, 0.0f } );
    myNetwork->propagate( learningRate, { 1.0f } );

    // 1,1 => 0
    myNetwork->activate( { 1.0f, 1.0f } );
    myNetwork->propagate( learningRate, { 0.0f } );
  }*/

  /*const unsigned int numHiddenLayers = 2;

  auto inputLayer = new InputLayer( 2 );
  std::vector< HiddenLayer*> vhl;
  for ( unsigned int i = 0; i < numHiddenLayers; ++i )
  {
    vhl.push_back( new HiddenLayer( 3 ) );
  }
  auto outputLayer = new OutputLayer( 1 );*/

  //auto net = new NeuralNet( inputLayer, vhl, outputLayer );
  auto net = new NeuralNet( 2, 3, 3, 1 );

  std::cout << *net << std::endl;

  /*auto train = new Perceptron( );
  train->trainSet = {
    { 1.0f, 0.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f }
  };
  train->realOutput = { 0.0f, 0.0f, 0.0f, 1.0f };
  train->learningRate = 1.0f;
  train->maxTargetErrors = 0.002f;
  train->actFnc = ITrainer::ActivationFnc::STEP;

  train->train( net, 10 );*/

  system( "PAUSE" );

  return 0;
}