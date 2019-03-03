/**
@file Example.cpp
@author Mike Lindstrom

@brief The Nelder-Mead algorithm implemented in this folder - see NelderMead.h - is
tested with a few examples.

@details There are 3 examples:
first - minimize f(x,y) = x^2+y^2
second - minimize the negative log-likelihood of an exponential random process
third - minimize the sum of squares error for a linear model

Scroll down to main.cpp just to see everything in action

The last line of any given run is the minimum value of the objective function
found along with the parameter values
*/

#include<functional>
#include<iostream>
#include<array>
#include<cmath>
#include<numeric>

#include "Random.h"
#include "NelderMead.h"

/**
Function returns sum of squares
@param a first number
@param b second number
@return sum of their squares
*/
double f(double a, double b);

/**
@struct G a callable class that stores the result of 10
trials of an ~Exp(2.36) process
*/
struct ExpFit{
	double sequence[20]; // will be 20 exp random variables
	/**
	constructor sets up the data
	*/
	ExpFit();
	
	/**
	call operator returns negative log-likelihood of observing the data
	for a given parameter
	@param lam the rate
	@return the negative log-likelihood
	*/
	double operator()(double lam) const;
};

/**
This simulates an experimental output: given x1-x4
@param x1 first argument
@param x2 second argument
@param x3 third argument
@param x4 fourth argument
@return 3.2 + 4.2*x2 + 2.2*x2 - 7*x3 + 0.0026*x4 + some random noise
*/
float model(float x1, float x2, float x3, float x4);

/**
This gives the error of a single trial
@param trial the experimental results
@param a0 first fit parameter
@param a1 second fit parameter
@param a2 third fit parameter
@param a3 fourth fit parameter
@param a4 fifth fit parameter
@return error squared
*/
float trial_penalty(const std::array<float,5>& trial, float a0, float a1, float a2, float a3, float a4);

/**
This gives the error over all trials
@param data 100 trial results
@param a0 first fit parameter
@param a1 second fit parameter
@param a2 third fit parameter
@param a3 fourth fit parameter
@param a4 fifth fit parameter
@return sum of all trial errors
*/
float total_penalty(const std::array< std::array<float, 5>, 100>& data, float a0, float a1, 
	float a2, float a3, float a4);

int main() {	
	// EXAMPLE #1: we minimize a function of 2 variables f(x,y) = x^2+y^2
	// minimum is at (0,0) with value 0
	// we use a free function objective
	std::cout << "EXAMPLE 1\n";
	basic_opt::NelderMead<2,double> ex1;	
	ex1.set_objective(f); // use function pointer	
	ex1.make_guess(11,200); // starting guess
	std::cout << "EXAMPLE 1\n";
	ex1.run(50); // 100 iterations, want tol < 1.e-3
	std::cout << '\n';
	
	// EXAMPLE #2: minimize the negative log likelihood of
	// some trials
	// proper minimum is at 2.36
	basic_opt::NelderMead<1,double> ex2;
	ex2.set_objective(ExpFit{}); // use the class	
	ex2.make_guess(9);
	std::cout << "EXAMPLE 2\n";
	ex2.run(40);
	std::cout << '\n';
		
	// EXAMPLE #3: want to find best fitting parameters via least squares
	// should find values 3.2, 4.2, 2.2, -7, 0.0026 as used in model function
	// we will use a lambda as an objective function
	
	// make a bunch of data for model: 
	// 100 pieces of data with 4 inputs + 1 output = 5 values
	std::array< std::array<float, 5>, 100> data;
	for(auto& trial : data){ // for every trial, pick some numbers to feed to model
		float x1 = basic_math::uniform_real<float>(-100,100);
		float x2 = basic_math::uniform_real<float>(-100,100);
		float x3 = basic_math::uniform_real<float>(-100,100);
		float x4 = basic_math::uniform_real<float>(-100,100);
		float out = model(x1,x2,x3,x4);
		trial[0] = x1;
		trial[1] = x2;
		trial[2] = x3;
		trial[3] = x4;
		trial[4] = out;
	}
	
	// objective function
	auto lam = [data](float a0, float a1, float a2, float a3, float a4)->float{
		return total_penalty(data, a0, a1, a2, a3, a4);
	};
	
	basic_opt::NelderMead<5, float> ex3;
	ex3.set_objective(lam);

	// we can also pass the guess function a param_vec object
	basic_opt::param_vec<5, float> guess3{ 0,0,0,0,0 };
	ex3.make_guess(guess3); // guess all zeros...
	
	ex3.iteration_display(false); // don't show progress until end
	std::cout << "EXAMPLE 3\n";
	ex3.run(1000);
	
	std::cout << "Program finished. Press ENTER to terminate.\n";
	std::cin.get();	

	return 0;
}

// definitions

double f(double a, double b) {
	return a*a + b*b;
}

ExpFit::ExpFit(){
	for(double &d: sequence){ // generate value for all elements
		d = basic_math::exp_rand<double>(2.36); // get random ~Exp(2.36)
	}
}

double ExpFit::operator()(double lam) const{
	// find negative log likelihood
	double log_like = std::accumulate(std::begin(sequence), std::end(sequence), 0.,
		[lam](double a, double b)->double{
			return a += (std::log(lam) - lam*b);
		});
	return -log_like;
}

float model(float x1, float x2, float x3, float x4){
	return 3.2 + 4.2*x1 + 2.2*x2 - 7*x3 + 0.0026*x4 + basic_math::normal<float>(0,0.01);
}

float trial_penalty(const std::array<float,5>& trial, float a0, float a1, float a2, float a3, float a4){
	return std::pow(a0 + a1*trial[0] + a2*trial[1] + a3*trial[2] + a4*trial[3] - trial[4], 2);	
}

float total_penalty(const std::array< std::array<float, 5>, 100>& data, float a0, float a1, 
	float a2, float a3, float a4){
	float tot = 0;
	for(const auto& trial: data){ // add errors for all trials
		tot += trial_penalty(trial, a0, a1, a2, a3, a4);
	}
	return tot;
}
