#pragma once

#include <map>

class Neuron
{
public:
  class Connection
  {
  public:
    Connection( Neuron* from, Neuron* to )
      : Connection( from, to, (static_cast < float > ( rand( ) ) / 
      static_cast < float > ( RAND_MAX ) ) /* * 2.0f - 1.0f */ )
    {
    }
    Connection( Neuron* from_, Neuron* to_, float weight_ )
      : id( uid( ) )
      , from( from_ )
      , to( to_ )
      , weight( weight_ )
      , gain( 1 )
    {
    }
    unsigned int id;
    Neuron* from;
    Neuron* to;
    float weight;
    int gain;

  protected:
    static unsigned int uid( )
    {
      static unsigned int _uid_ = 0;
      return _uid_++;
    }
  };
  struct Connections
  {
    std::map< int, Neuron::Connection* > input;
    std::map< int, Neuron::Connection* > projected;
  };
  struct Error
  {
    float responsibility = 0.0f;
    float projected = 0.0f;
  };
  Neuron( );
  Neuron::Connection* project( Neuron* n, float weight = 0.0f );
  float activate( );
  float activate( float v );

  bool connected( Neuron* n, std::string& type, Neuron::Connection* connection );

  void propagate( float rate );
  void propagate( float rate, float target );

//protected:
  unsigned int id;
  float activation = 0.0f;
  float bias;
  Connections connections;
  Error error;
  std::map< int, Neuron* > neightboors;
  float old = 0.0f;
  float state = 0.0f;
  float derivative = 0.0f;

  Neuron::Connection* selfConnection;

  static unsigned int uid( )
  {
    static unsigned int _uid_ = 0;
    return _uid_++;
  }
};

