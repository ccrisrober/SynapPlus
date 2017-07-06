#pragma once

#include <iostream>
#include <iomanip>
#include <assert.h>

#include "Neuron.h"

#include <vector>

class ILayer
{
protected:
  ILayer( unsigned int size )
  {
    listOfNeurons.resize( size );
    for ( unsigned int i = 0; i < size; ++i )
    {
      listOfNeurons[ i ] = new Neuron( );
    }
  }
public:
  class Connection
  {
  public:
    enum class Type : short
    {
      ALL_TO_ALL,
      ONE_TO_ONE,
      ALL_TO_ELSE
    };
    Connection( ILayer* fromLayer, ILayer* toLayer )
      : Connection( fromLayer, toLayer,
      ( fromLayer == toLayer ? 
        Connection::Type::ONE_TO_ONE : Connection::Type::ALL_TO_ALL )
      )
    {
    }
    Connection( ILayer* fromLayer, ILayer* toLayer, Connection::Type type )
      : id( uid( ) )
    {
      this->from = fromLayer;
      this->to = toLayer;
      this->selfConnection = from == to;
      this->type = type;

      if ( this->type == Connection::Type::ALL_TO_ALL ||
        this->type == Connection::Type::ALL_TO_ELSE )
      {
        for ( unsigned int here = 0; here < from->listOfNeurons.size( ); ++here )
        {
          for ( unsigned int there = 0; there < to->listOfNeurons.size( ); ++there )
          {
            Neuron* from = this->from->listOfNeurons[ here ];
            Neuron* to = this->to->listOfNeurons[ there ];

            if ( type == Connection::Type::ALL_TO_ELSE && from == to )
            {
              continue;
            }

            Neuron::Connection* connection = from->project( to );
            this->connections[ connection->id ] = connection;
            neurons.push_back( connection );
          }
        }
      }
      else if ( type == Connection::Type::ONE_TO_ONE )
      {
        for ( unsigned int neuron = 0; neuron < from->listOfNeurons.size( ); ++neuron )
        {
          Neuron* from = this->from->listOfNeurons.at( neuron );
          Neuron* to = nullptr;
          if ( neuron < this->to->listOfNeurons.size( ) )
          {
            to = this->to->listOfNeurons.at( neuron );
          }

          Neuron::Connection* connection = from->project( to );
          this->connections[ connection->id ] = connection;
          neurons.push_back( connection );
        }
      }
      fromLayer->connectedTo.push_back( this );
    }
    unsigned int id;
    std::map< int, Neuron::Connection* > connections;
    ILayer* from;
    std::vector< Neuron::Connection* > neurons;
    bool selfConnection = false;
    ILayer* to;
    Connection::Type type;
  protected:
    static unsigned int uid( )
    {
      static unsigned int _uid_ = 0;
      return _uid_++;
    }
  };
  std::vector< Neuron* > listOfNeurons;

  std::vector< float > activate( std::vector< float > weights = { } )
  {
    std::vector< float> activations;
    if ( !weights.empty( ) )
    {
      assert( weights.size( ) == listOfNeurons.size( ) );
      for ( unsigned int i = 0; i < listOfNeurons.size( ); ++i )
      {
        Neuron* neuron = listOfNeurons.at( i );
        float activation = neuron->activate( weights.at( i ) );
        activations.push_back( activation );
      }
    }
    else
    {
      for ( unsigned int i = 0; i < listOfNeurons.size( ); ++i )
      {
        Neuron* neuron = listOfNeurons.at( i );
        float activation = neuron->activate( );
        activations.push_back( activation );
      }
    }

    return activations;
  }
  ILayer::Connection* project( ILayer* layer,
    Connection::Type type = Connection::Type::ALL_TO_ALL )
  {
    if ( !this->isConnected( layer ) )
    {
      return new ILayer::Connection( this, layer, type );
    }
    throw;
  }
  bool isConnected( const ILayer* layer )
  {
    // Check if all to all connection
    unsigned int connections = 0;
    for ( unsigned int here = 0; here < listOfNeurons.size( ); ++here )
    {
      for ( unsigned int there = 0; there < layer->listOfNeurons.size( ); ++there )
      {
        Neuron* from = listOfNeurons.at( here );
        Neuron* to = layer->listOfNeurons.at( there );

        std::string type = "";
        Neuron::Connection* connection = nullptr;

        bool connected = from->connected( to, type, connection );
        if ( connected && type == "projected" )
        {
          ++connections;
        }
      }
    }

    if ( connections == listOfNeurons.size( ) * layer->listOfNeurons.size( ) )
    {
      return true;// Layer::Connection::Type::ALL_TO_ALL;
    }

    // Check if ONE_to_ONE connection
    connections = 0;

    for ( unsigned int neuron = 0; neuron < listOfNeurons.size( ); ++neuron )
    {
      Neuron* from = listOfNeurons.at( neuron );
      Neuron* to = nullptr;
      if ( neuron < layer->listOfNeurons.size( ) )
      {
        to = layer->listOfNeurons.at( neuron );
      }

      std::string type = "";
      Neuron::Connection* connection = nullptr;

      bool connected = from->connected( to, type, connection );
      if ( connected && type == "projected" )
      {
        ++connections;
      }
    }
    if ( connections == listOfNeurons.size( ) )
    {
      return true;// Layer::Connection::Type::ONE_TO_ONE;
    }

    return false;
  }
  std::vector< ILayer::Connection* > connectedTo;
};

class InputLayer : public ILayer
{
public:
  InputLayer( unsigned int size )
    : ILayer( size )
  {
  }
  //void activate( std::vector< float > weights );
  friend std::ostream& operator<<( std::ostream &out, const InputLayer& l )
  {
    out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
      << std::setprecision( 4 );
    out << "### INPUT LAYER ###" << std::endl;;

    for ( auto neuron : l.listOfNeurons )
    {
      out << "Neuron #" << neuron->id << ":";
      out << neuron->bias << std::endl;
    }

    return out;
  }
};

class HiddenLayer : public ILayer
{
public:
  HiddenLayer( unsigned int size )
    : ILayer( size )
  {
  }
public:
  friend std::ostream& operator<<( std::ostream &out, const HiddenLayer& l )
  {
    out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
      << std::setprecision( 4 );
    out << "### HIDDEN LAYER ###" << std::endl;

    for ( auto neuron : l.listOfNeurons )
    {
      out << "Neuron #" << neuron->id << ":";
      out << neuron->bias << std::endl;
    }

    return out;
  }
};

class OutputLayer : public ILayer
{
public:
  OutputLayer( unsigned int size )
    : ILayer( size )
  {
  }
public:
  friend std::ostream& operator<<( std::ostream &out, const OutputLayer& l )
  {
    out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
      << std::setprecision( 4 );
    out << "### OUTPUT LAYER ###" << std::endl;

    for ( auto neuron : l.listOfNeurons )
    {
      out << "Neuron #" << neuron->id << ":";
      out << neuron->bias << std::endl;
    }

    return out;
  }
};

class NeuralNet
{
public:
  /*NeuralNet( unsigned int numInputNeurons,
    std::vector< unsigned int > hiddenLayers_,
    unsigned int numOutputNeurons )
  {
    //TODO: NOT COMPETED
    inputLayer = new InputLayer( numInputNeurons );
    for ( unsigned int i = 0; i < hiddenLayers_.size( ); ++i )
    {
      hiddenLayers.push_back( new HiddenLayer( hiddenLayers_[ i ] ) );
    }
    outputLayer = new OutputLayer( numOutputNeurons );
  }*/
  NeuralNet( unsigned int numInputNeurons,
    unsigned int numHiddenLayers, unsigned int numNeuronsInHiddenLayers,
    unsigned int numOutputNeurons )
  {
    inputLayer = new InputLayer( numInputNeurons );
    ILayer* previous = inputLayer;
    for ( unsigned int i = 0; i < numHiddenLayers; ++i )
    {
      ILayer* layer = new HiddenLayer( numNeuronsInHiddenLayers );
      hiddenLayers.push_back( static_cast<HiddenLayer*>( layer ) );
      previous->project( layer );
      previous = layer;
    }
    outputLayer = new OutputLayer( numOutputNeurons );
    previous->project( outputLayer );
  }
  NeuralNet( InputLayer* il, const std::vector< HiddenLayer* > vhl, 
    OutputLayer* ol )
    : inputLayer( il)
    , hiddenLayers( vhl )
    , outputLayer( ol )
  {
  }

  friend std::ostream& operator<<( std::ostream &out, const NeuralNet& nn )
  {
    out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
      << std::setprecision( 2 );

    out << *nn.inputLayer << std::endl;
    for ( const auto& l : nn.hiddenLayers )
    {
      out << *l << std::endl;
    }
    out << *nn.outputLayer << std::endl;

    return out;
  }
protected:
  InputLayer* inputLayer;
  std::vector< HiddenLayer *> hiddenLayers;
  OutputLayer* outputLayer;
};