#include "largest.h"

largest_value::largest_value(double _init) : val(_init) {}

void largest_value::add_value( double _val ) {
  if( val < _val ){ // new value is larger so store this instead 
    val = _val;
  }
}

double largest_value::get_max() const {
  return val;
}
