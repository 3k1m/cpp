/**
@file Random.h
@author Mike Lindstrom
@version 1
@brief this file makes use of the std random number generators in a more
black-box, ready to use fashion
*/

#ifndef _BASIC_MATH__RANDOM_
#define _BASIC_MATH__RANDOM_

#include<ctime>
#include<random>

namespace basic_math{

	/**
	Returns a poisson random variable
	@tparam Int the type of data it should return
	@param rate the Poisson rate
	@return a value ~Poiss(rate)
	*/
	template<typename Int,
		typename = std::enable_if< std::is_integral<Int>::value > >
	Int poiss(double rate){
		thread_local std::default_random_engine eng{static_cast<unsigned>(std::clock())};

		return std::poisson_distribution<Int>{rate}(eng);
	}

	/**
	Returns an exponential random variable
	@tparam Float the type of data for input/output
	@param lambda the rate where 1/lambda is the mean
	@return a value ~Exp(lambda)
	*/
	template<typename Float,
		typename = std::enable_if< std::is_floating_point<Float>::value> >
	Float exp_rand(const Float& lambda) {
		thread_local std::default_random_engine eng{static_cast<unsigned>(std::clock())};

		return std::exponential_distribution<Float>{lambda}(eng);		
	}

	/**
	Returns a real number with uniform distribution
	@tparam Float the type of data to return
	@param a the lower bound
	@param b the upper bound
	@return a value ~ Unif( [a,b) ) -- closed at a, open at b
	*/
	template<typename Float, typename = std::enable_if<std::is_floating_point<Float>::value> > 
	Float uniform_real(const Float& a, const Float& b) {
		thread_local std::default_random_engine eng{static_cast<unsigned>(std::clock())};

		return std::uniform_real_distribution<Float>{a,b}(eng);
	}
	
	/**
	Returns an integer number with uniform distribution
	@tparam Int the type of data to return
	@param a the lower bound
	@param b the upper bound
	@return a value ~ Unif( [a,b) ) -- closed at a, open at b
	*/
	template<typename Int, typename = std::enable_if<std::is_integral<Int>::value> > 
	Int uniform_integer(const Int& a, const Int& b){
		thread_local std::default_random_engine eng{static_cast<unsigned>(std::clock())};

		return std::uniform_int_distribution<Int>{a,b}(eng);
	}

	/**
	Returns a value from the normal distribution
	@tparam Float the type of data to return
	@param mu the mean
	@param sigma the standard deviation
	@return a value ~ N(mu, sigma^2)
	*/
	template<typename Float, 
		typename = std::enable_if< std::is_floating_point<Float>::value  > >
	Float normal(const Float& mu, const Float& sigma){
		thread_local std::default_random_engine eng{static_cast<unsigned>(std::clock())};

		return std::normal_distribution<Float>{mu,sigma}(eng);
	}	
	
}


#endif
