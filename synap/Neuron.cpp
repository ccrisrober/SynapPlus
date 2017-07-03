#include "Neuron.h"

#include <functional>

Neuron::Neuron( )
{
  id = Neuron::uid( );
  bias = ( static_cast < float > ( rand( ) ) /
    static_cast < float > ( RAND_MAX ) ) /* * 2.0f - 1.0f*/;

  selfConnection = new Neuron::Connection( this, this, 0.0f );
}

bool Neuron::connected( Neuron* neuron, std::string& type, Neuron::Connection* connection )
{
  if ( this == neuron )
  {
    type = "selfConnection";
    connection = selfConnection;
    return true;
  }

  for ( auto conn : connections.input )
  {
    if ( conn.second->to == neuron )
    {
      type = "input";
      connection = conn.second;
      return true;
    }
    else if ( conn.second->from == neuron )
    {
      type = "input";
      connection = conn.second;
      return true;
    }
  }

  for ( auto conn : connections.projected )
  {
    if ( conn.second->to == neuron )
    {
      type = "projected";

      return true;
    }
    else if ( conn.second->from == neuron )
    {
      type = "projected";

      return true;
    }
  }

  return false;
}

Neuron::Connection* Neuron::project( Neuron* neuron, float weight )
{
  if ( neuron == this )
  {
    selfConnection->weight = 1.0f;
    return this->selfConnection;
  }

  std::string type = "";
  Neuron::Connection* connection = nullptr;
  auto con = connected( neuron, type, connection );
  if ( con && type == "projected" )
  {
    // Actualizar conexión
    if ( weight != 0.0f )
    {
      connection->weight = weight;

      return connection;
    }
    return connection;
  }
 else
 {
   connection = new Neuron::Connection( this, neuron, weight );
 }

  // Referece all the connections
  this->connections.projected[ connection->id ] = connection;
  this->neightboors[ neuron->id ] = neuron;
  neuron->connections.input[ connection->id ] = connection;

  return connection;
}

float Neuron::activate( )
{
  this->old = this->state;

  this->state = this->selfConnection->gain * 
    this->selfConnection->weight * this->state + this->bias;


  for ( auto conn : connections.input )
  {
    Neuron::Connection* input = conn.second;
    this->state += input->from->activation * input->weight - input->gain;
  }

  std::function<float( float, bool )> squash_logistic = []( float x, bool derivative/* = false*/ )
  {
    auto fx = 1.0f / ( 1.0f - std::exp( -x ) );
    if ( !derivative )
    {
      return fx;
    }
    return fx * ( 1.0f - fx );
  };

  
  this->activation = squash_logistic( this->state, false );
  this->derivative = squash_logistic( this->state, true );
  
  return activation;
}

float Neuron::activate( float v )
{
  this->activation = v;
  this->bias = 0.0f;

  return this->activation;
}