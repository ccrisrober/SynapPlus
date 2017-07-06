/*#pragma once

#include <map>
#include <functional>

class ActivationFunctions
{
protected:
  ActivationFunctions( )
  {
    functions[ "SIGMOID" ] = [] ( float x, bool derivate )
    {
      float fx = 1.0f / (1.0f + std::exp(-x));
      if ( !derivate )
      {
        return fx;
      }
      return fx * ( 1.0f - fx );
    };
    functions[ "HYPTAN" ] = [] ( float x, bool derivate )
    {
      return (1.0f - std::exp(-x)) / (1.0f + std::exp(-x));
    };
    functions[ "HLIM" ] = [] ( float x, bool derivate )
    {
      return derivate ? 1.0f : x > 0.0f ? 1.0f : 0.0f;
    };
    functions[ "LINEAR" ] = [] ( float x, bool derivate )
    {
      return x;
    };
  }
  typedef std::function<float(float, bool)> ActivationFn;
  std::map< std::string, ActivationFn> functions;
};*/