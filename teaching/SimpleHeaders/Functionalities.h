#ifndef _FUNCTIONALITIES_
#define _FUNCTIONALITIES_

#include<iostream>
#include<vector>

/**
 * computes the larger of two doubles
 * @param a the first
 * @param b the second
 * @return the larger of the two 
 */
double larger(double a, double b);


/**
 * computes mean value in vector
 * @param values the vector
 * @return the mean value
 */
double mean( const std::vector<double>& values);

/**
 * will print anything
 * @param an item to print  
 */
void print(const auto& item){
  std::cout << item;
}

#endif
