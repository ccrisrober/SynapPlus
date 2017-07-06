#pragma once

#include "Layers.h"

class ITrainer
{
public:
  enum class ActivationFnc
  {
    STEP,
    LINEAR,
    SIGLOG,
    HYPERTAN
  };


  unsigned int epochs;  // training cycles
  float error;          // Error between estimated and real output
  float mse;            //  Mean square error (average of the squares of the errors or deviations);

  std::vector< std::vector< float > > trainSet;
  std::vector< float > realOutput;
  
  float learningRate;
  float maxTargetErrors;
  ActivationFnc actFnc = ActivationFnc::STEP;

  // n: Untrained network
  // return: Trained network
  NeuralNet* train( NeuralNet * n, unsigned int maxEpochs )
  {
    unsigned int rows = trainSet.size( );
    unsigned int cols = trainSet.at( 0 ).size( );

    while ( epochs < maxEpochs )
    {
      float estimatedOuput = 0.0f;
      float realOutput = 0.0f;

      for ( unsigned int i = 0; i < rows; ++i )
      {
        float netValue = 0.0f;
        for ( unsigned int j = 0; j < cols; ++j )
        {

        }

        estimatedOuput = activationFnc( actFnc, netValue );

        realOutput = this->realOutput[ i ];

        this->error = realOutput - estimatedOuput;

        std::cout << "Epoch: " << epochs << " / Error: " << this->error << std::endl;

        if ( std::abs( this->error > maxTargetErrors ) )
        {
          // Fix weights

        }
      }

//      mse = std::pow( this->realOutput - estimatedOuput, 2.0f );
      --epochs;
    }

    return n;
  }

private:
  float activationFnc( ActivationFnc fnc, float v )
  {
    switch ( fnc )
    {
      case ITrainer::ActivationFnc::STEP:
        return fncStep( v );
      case ITrainer::ActivationFnc::LINEAR:
        return fncLinear( v );
      case ITrainer::ActivationFnc::SIGLOG:
        return fncSigLog( v );
      case ITrainer::ActivationFnc::HYPERTAN:
        return fncHyperTan( v );
      default:
        throw;
    }
  }
  float derivativeActivationFnc( ActivationFnc fnc, float v )
  {
    switch ( fnc )
    {
      case ITrainer::ActivationFnc::LINEAR:
        return derivativeFncLinear( v );
      case ITrainer::ActivationFnc::SIGLOG:
        return derivativeFncSigLog( v );
      case ITrainer::ActivationFnc::HYPERTAN:
        return derivativeFncHyperTan( v );
      default:
        throw;
    }
  }

  float fncStep( float v )
  {
    if ( v >= 0.0f )
    {
      return 1.0f;
    }
    else
    {
      return 0.0f;
    }
  }
  float fncLinear( float v )
  {
    return v;
  }
  float fncSigLog( float v )
  {
    return 1.0f / ( 1.0f + std::exp( -v ) );
  }
  float fncHyperTan( float v )
  {
    return std::tanh( v );
  }

  float derivativeFncLinear( float v )
  {
    return 1.0f;
  }
  float derivativeFncSigLog( float v )
  {
    return v * ( 1.0f - v );
  }
  float derivativeFncHyperTan( float v )
  {
    return ( 1.0f / std::pow( std::cosh( v ), 2.0f ) );
  }
protected:
  ITrainer( )
  {
  }
};

class Perceptron : public ITrainer
{
public:
  Perceptron( )
  {
  }
  NeuralNet* train( NeuralNet* n, unsigned int maxEpochs )
  {
    return ITrainer::train( n, maxEpochs );
  }
};