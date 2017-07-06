#ifdef HOLA

#include "Neuron.h"

#include <vector>
#include <assert.h>
#include <algorithm>

class Layer
{
public:
  class Connection
  {
  public:
    enum class Type: short
    {
      ALL_TO_ALL,
      ONE_TO_ONE,
      ALL_TO_ELSE
    };
    Connection( Layer* fromLayer, Layer* toLayer )
      : Connection( fromLayer, toLayer, 
      ( fromLayer == toLayer ? Connection::Type::ONE_TO_ONE : Connection::Type::ALL_TO_ALL )
      )
    {
    }
    Connection( Layer* fromLayer, Layer* toLayer, Connection::Type type )
      : id( uid( ) )
    {
      this->from = fromLayer;
      this->to = toLayer;
      this->selfConnection = from == to;
      this->type = type;

      if ( this->type == Connection::Type::ALL_TO_ALL ||
        this->type == Connection::Type::ALL_TO_ELSE )
      {
        for ( unsigned int here = 0; here < from->neurons.size( ); ++here )
        {
          for ( unsigned int there = 0; there < to->neurons.size( ); ++there )
          {
            Neuron* from = this->from->neurons[ here ];
            Neuron* to = this->to->neurons[ there ];

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
        for ( unsigned int neuron = 0; neuron < from->neurons.size( ); ++neuron )
        {
          Neuron* from = this->from->neurons.at( neuron );
          Neuron* to = nullptr;
          if ( neuron < this->to->neurons.size( ) )
          {
            to = this->to->neurons.at( neuron );
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
    Layer* from;
    std::vector< Neuron::Connection* > neurons;
    bool selfConnection = false;
    Layer* to;
    Connection::Type type;

  protected:
    static unsigned int uid( )
    {
      static unsigned int _uid_ = 0;
      return _uid_++;
    }
  };
  Layer( unsigned int size );

  void propagate( float rate, std::vector< float > target = { } )
  {
    if ( !target.empty( ) )
    {
      assert( target.size( ) == neurons.size( ) );

      for ( unsigned int id = neurons.size( ) - 1; id >= 0; --id )
      {
        Neuron* neuron = neurons[ id ];
        neuron->propagate( rate, target[ id ] );
      }
    }
    else
    {
      for ( unsigned int id = neurons.size( ) - 1; id >= 0; --id )
      {
        Neuron* neuron = neurons[ id ];
        neuron->propagate( rate );
      }
    }
  }

  std::vector< float > activate( std::vector< float > weights = { } )
  {
    std::vector< float> activations;
    if ( !weights.empty( ) )
    {
      assert( weights.size( ) == neurons.size( ) );
      for ( unsigned int i = 0; i < neurons.size( ); ++i )
      {
        Neuron* neuron = neurons.at( i );
        float activation = neuron->activate( weights.at( i ) );
        activations.push_back( activation );
      }
    }
    else
    {
      for ( unsigned int i = 0; i < neurons.size( ); ++i )
      {
        Neuron* neuron = neurons.at( i );
        float activation = neuron->activate( );
        activations.push_back( activation );
      }
    }

    return activations;
  }

  Layer::Connection* project( Layer* layer )
  {
    //assert( weights.size( ) == neurons.size( ) );

    if ( !this->isConnected( layer ) )
    {
      return new Layer::Connection( this, layer );
    }
    throw;
  }

  Layer::Connection* project( Layer* layer, Connection::Type type )
  {
    //assert( weights.size( ) == neurons.size( ) );

    if ( !this->isConnected( layer ) )
    {
      return new Layer::Connection( this, layer, type );
    }
    throw;
  }

  bool isConnected( const Layer* layer )
  {
    // Check if all to all connection
    unsigned int connections = 0;
    for ( unsigned int here = 0; here < neurons.size( ); ++here )
    {
      for ( unsigned int there = 0; there < layer->neurons.size( ); ++there )
      {
        Neuron* from = neurons.at( here );
        Neuron* to = layer->neurons.at( there );

        std::string type = "";
        Neuron::Connection* connection = nullptr;

        bool connected = from->connected( to, type, connection );
        if ( connected && type == "projected" )
        {
          ++connections;
        }
      }
    }

    if ( connections == neurons.size( ) * layer->neurons.size( ) )
    {
      return true;// Layer::Connection::Type::ALL_TO_ALL;
    }

    // Check if ONE_to_ONE connection
    connections = 0;

    for ( unsigned int neuron = 0; neuron < neurons.size( ); ++neuron )
    {
      Neuron* from = neurons.at( neuron );
      Neuron* to = nullptr;
      if ( neuron < layer->neurons.size( ) )
      {
        to = layer->neurons.at( neuron );
      }

      std::string type = "";
      Neuron::Connection* connection = nullptr;

      bool connected = from->connected( to, type, connection );
      if ( connected && type == "projected" )
      {
        ++connections;
      }
    }
    if ( connections == neurons.size( ) )
    {
      return true;// Layer::Connection::Type::ONE_TO_ONE;
    }

    return false;
  }

  std::vector< Neuron* > neurons;
  std::vector< Layer::Connection* > connectedTo;
};


#endif