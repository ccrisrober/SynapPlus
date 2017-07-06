/*#pragma once

#include "Layer.h"
#include <vector>

class Network
{
public:
  Network( Layer* input = nullptr, 
    std::vector< Layer* > hidden = { }, 
    Layer* output = nullptr );

  std::vector< float > activate( std::vector<float> input );
  void propagate( float rate, std::vector<float> target );

  Layer* Input;
  std::vector< Layer* > Hidden;
  Layer* Output;
};

*/