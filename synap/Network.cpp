/*#include "Network.h"
#include <algorithm>

Network::Network( Layer* input, std::vector< Layer* > hidden, Layer* output )
  : Input( input )
  , Hidden( hidden )
  , Output( output )
{
}

std::vector< float > Network::activate( std::vector<float> input )
{
  Input->activate( input );
  for ( auto hidden : Hidden )
  {
    hidden->activate( );
  }
  return this->Output->activate( );
}

void Network::propagate( float rate, std::vector<float> target )
{
  Output->propagate( rate, target );

  std::for_each( Hidden.rbegin( ), Hidden.rend( ), [rate] ( Layer* hidden )
  {
    hidden->propagate( rate );
  } );
}*/