#include "Functionalities.h"
#include <numeric>

double larger(double a, double b){
  return (a<b) ? b : a;
}

double mean( const std::vector<double>& values ){
  return std::accumulate( values.begin(), values.end(), 0.)/values.size();
}
