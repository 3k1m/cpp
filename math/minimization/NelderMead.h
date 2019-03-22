/**
@file NelderMead.h
@author Mike Lindstrom
@version 1
@date March 2019
@brief the Nelder-Mead algorithm is implemented in this file, which can be used
to solve minimization problems without the need for a gradient

@details The algorithm follows the implementation found in the popular paper:
J. Lagarias, J. Reeds, M. Wright, and P. Wright. Convergence Properties of the Nelder-Mead
Simplex Method in Low Dimensions, SIAM J. OPT. 1998. Vol. 9 No. 1, pp. 112-147

From what I can tell, the stable_sort choice satisfies the main tie-breaking requirements outlined
in the paper. And it seems to work :)

Note: the file does require the inclusion of PatchIndex.h
*/

#ifndef _BASIC_OPT__NELDER_MEAD_
#define _BASIC_OPT__NELDER_MEAD_

#include<functional>
#include<array>
#include<limits>
#include<algorithm>
#include<iostream>

#include "PatchIndex.h"

namespace basic_opt {

	/* start off with some helpers */

	/**
	This function calls a function using all the arguments of a container
	@tparam argc the number of arguments the function takes
	@tparam F the type of function
	@tparam Container the container type
	@tparam ... Is the sequence of index values to use
	@param f the function to call
	@param list the container
	@param seq is a sequence of indices
	@return f evaluated at all the elements
	*/
	template<size_t argc, typename Fun, typename Container, std::size_t... Is >
	auto call(Fun&& f, Container&& list, patch::index_sequence<Is...> seq) -> decltype(f(list[Is]...));

	/**
	This function accepts a functor to call with a container and subsequently passes
	all its arguments to be called
	@tparam argc the number of arguments the function takes
	@tparam Fun the type of functor
	@tparam Container the container type
	@param f the functor
	@param list the container
	@return f evaluated at all elements in the container
	*/
	template<size_t argc, typename Fun, typename Container>
	auto unpack(Fun&& f, Container&& list) -> 
		decltype(call<argc,Fun, Container>(f, list, patch::build_index_sequence<argc>{}));

	/* now some helpful utilty classes */

	/**
	@class param_vec stores a vector representing the parameters
	to optimize over
	@tparam param_count the number of parameters to optimize over
	@tparam precision the floating point precision to use and store
	*/
	template<size_t param_count, typename precision = double>
	class param_vec {
	private:	
		// array of parameters to optimize through
		precision params[param_count];
		
		// define out iterators to just be pointers!
		typedef precision* (iterator);
		typedef const precision* (const_iterator);

		/**
		Places the last element into the array
		@tparam Arg the argument type
		@param pos the index to place
		@param val the value inserted
		*/
		template<typename Arg>
		void construct_helper(size_t pos, Arg&& val){
			params[pos] = std::forward<Arg>(val);			
		}
		
		/**
		Places all elements into the array recursively
		@tparam Arg the argument type being placed
		@tparam ... Args type of remaing items
		@param pos the index to place
		@param val the value to insert
		@param ... vals the remaining values to insert
		*/		
		template<typename Arg, typename ... Args>
		void construct_helper(size_t pos, Arg&& val, Args&& ... vals){			
			if(pos < param_count){ // provided still in range
				params[pos] = std::forward<Arg>(val);
				construct_helper(pos+1,std::forward<Args>(vals)...);
			}
		}		

	public:	
	
		/**
		returns iterator to beginning
		@return a pointer to first element
		*/	
		iterator begin(){
			return &params[0];
		}
		
		/**
		returns iterator past the end
		@return pointer to past-end
		*/
		iterator end(){
			return &params[param_count];
		}
		
		/**
		returns const_iterator to beginning
		@return a pointer to const, for first element
		*/
		const_iterator begin() const {
			return &params[0];
		}
		
		/**
		returns const_iterator to past the end
		@return a pointer to const, for past-end
		*/
		const_iterator end() const {
			return &params[param_count];
		}
	
		/**
		constructor accepts a variadic list of arguments
		@tparam ... Args the types of arguments
		@param ... vals their values
		*/
		template<typename ... Args>
		param_vec(Args&& ... vals){	
			construct_helper(0,std::move(vals)...);
		}			
		
		/**
		we need a constructor accepting L-value to non-const to prevent the variadic
		constructor from taking over: but we just call the regular copy constructor
		*/
		param_vec(param_vec& v) : param_vec(const_cast<const param_vec&>(v)) {}
		
		/**
		due to a bug in Visual Studio, it is necessary to define this
		copy constructor explicitly. other compilers like g++ allow = default
		@param other the other param_vec
		*/
		param_vec(const param_vec& other) {
			for (size_t i = 0; i < param_count; ++i) { // copy entries one by one
				params[i] = other.params[i];
			}
		}

		/*
		enable more copy/move semantics
		*/

		param_vec(param_vec&&) noexcept = default;
		param_vec& operator=(const param_vec&) = default;
		param_vec& operator=(param_vec&&) = default;
		
		/**
		default constructor sets all values to zero
		*/
		param_vec() {
			for (auto& p : params) { // make all values in the array 0
				p = 0;
			}
		}
		
		/**
		subscript operator, const
		@param i the index
		@return reference to const for item
		*/
		const precision& operator[](size_t i) const { return params[i]; }
		
		/**
		subscript operator, non-const
		@param i the index
		@return reference to that item
		*/
		precision& operator[](size_t i) { return params[i]; }

		/**
		defines += math operator to add right to left
		@param other the right-hand argument
		@return updated class after adding entries from right to its entries
		*/
		param_vec& operator+=(const param_vec& other);

		/**
		defines -= math operator to subtract right from left
		@param other the right-hand argument
		@return updated class after subtracting entries from right from its entries
		*/
		param_vec& operator-=(const param_vec& other);

		/**
		defines *= math operator to multiply left by scalar on right
		@param p the right-hand scalar argument
		@return updated class after multipying all its entries by p
		*/		
		param_vec& operator*=(const precision& p);

		/**
		defines /= math operator to divide left by scalar on right
		@param p the right-hand scalar argument
		@return updated class after dividing all its entries by p
		*/		
		param_vec& operator/=(const precision& p);
		
		/* we make these functions friends to avoid issues with scalar type deductions */
		
		/**
		multiples a param_vec by a scalar
		@param left the param_vec on the left
		@param p the scalar
		@return the product
		*/
		friend param_vec operator*(param_vec left, const precision& p){
			return left *= p;
		}

		/**
		multiples a scalar with a param_vec
		@param p the scalar
		@param right the param_vec
		@return the product
		*/		
		friend param_vec operator*(const precision& p, param_vec right){
			return right *= p;
		}
		
		/**
		divides a param_vec by a scalar
		@param left the param_vec
		@param p the scalar
		@return the result after division
		*/
		friend param_vec operator/(param_vec left, const precision& p){
			return left /= p;
		}		
	};
	
	/**
	adds two param_vecs
	@param left the left
	@param right the right
	@return their sum
	*/
	template<size_t param_count, typename precision = double>
	param_vec<param_count, precision> operator+(param_vec<param_count, precision> left,
		const param_vec<param_count, precision>& right){
		return left += right;
	}

	/**
	subtracts two param_vecs
	@param left the left
	@param right the right
	@return their difference
	*/	
	template<size_t param_count, typename precision = double>
	param_vec<param_count, precision> operator-(param_vec<param_count, precision> left, 
		const param_vec<param_count, precision>& right){
		return left -= right;
	}

	/**
	@struct simplex_point a pairing of the function
	value f at a point x
	*/
	template<size_t param_count, typename precision = double>
	struct evaluation_point {
		precision f; // function value
		param_vec<param_count,precision> x; // input value
	};
	
	/* useful comparison operators */
	
	/**
	less than: compares two evaluation_points based on their f values
	@tparam param_count their numbers of parameters
	@tparam precision their floating point precision
	@param first the left argument
	@param second the right argument
	@return if first.f < second.f
	*/
	template<size_t param_count, typename precision = double>	
	bool operator<(const evaluation_point<param_count,precision>& first,
		const evaluation_point<param_count,precision>& second){
			return first.f < second.f;
	}

	/**
	less than or equal: compares two evaluation_points based on their f values
	@tparam param_count their numbers of parameters
	@tparam precision their floating point precision
	@param first the left argument
	@param second the right argument
	@return if first.f <= second.f
	*/	
	template<size_t param_count, typename precision = double>	
	bool operator<=(const evaluation_point<param_count,precision>& first,
		const evaluation_point<param_count,precision>& second){
			return first.f <= second.f;
	}
	
	/**
	prints an evaluation_point in format: [FUNCTION VALUE] | [PARAMETERS, ...]
	@tparam param_count the numbers of parameters
	@tparam precision the floating point precision used
	@param o an output stream
	@param p an evaluation_point
	@return the stream
	*/
	template<size_t param_count, typename precision = double>
	std::ostream& operator<<(std::ostream& o, const evaluation_point<param_count, precision>& p){
		o << p.f << " | "; // print the function value
		for(const auto& i : p.x){ // now print its inputs
			o << i << ' ';
		}
		return o;
	}

	/**
	@class NelderMead: this is the real work-horse of the operation, bearing
	the functionality to minimize an objective function
	@tparam param_count the number of parameters we are minimizing over
	@tparam precision the floating point precision of the objective function and arguments		
	*/	
	template<size_t param_count, typename precision = double>
	class NelderMead {
	
	public: // useful typedefs
		
		using point_type = evaluation_point<param_count, precision>;
		
		using param_type = param_vec<param_count, precision>;
		using return_type = precision;

	private:

		/* special constants for algorithm */
		
		static constexpr precision rho = 1, chi = 2, gamma = 0.5, sigma = 0.5;
		
		/* member variables */

		std::function<return_type(const param_type& v)> obj; // objective function
		
		bool print_per_iter; // whether to give updates after every iteration
		
		point_type points[param_count+1]; // points used in method
		point_type xbest; // best value
		
		point_type xr; // reflected point
		point_type xe; // expand point
		point_type xc; // outside contraction point
		point_type xcc; // inside contraction point
		
		param_type guess; // the initial guess
		param_type xbar; // centroid	

	public:
		/**
		The constructor sets all points to have gigantic error terms initially,
		with all parameters set to zero. By default it will print updates after
		every iteration but this can be turned off.
		*/
		NelderMead();
		
		/**
		This function sets the objective function to minimize
		@tparam Fun the functor type
		@param _obj the objective functor
		*/
		template<typename Fun>
		void set_objective(Fun&& _obj);
		
		/**
		Sets the initial guess to start the algorithm
		@param i the initial guess, of type param_type
		*/
		void make_guess(param_type i){
			guess = std::move(i);
		}
		
		/**
		Sets the initial guess by accepting separate arguments for all values
		@tparam ... Args the argument types
		@param ... _guess the guess values
		*/
		template<typename ... Args>
		void make_guess(Args&& ... _guess){
			guess = param_type(std::forward<Args>(_guess)...);
		}
		
		/**
		Run the algorithm
		@param num_iter the number of iterations
		*/
		void run(int num_iter);
		
		/**
		Initializes the simplex forming param_count+1 distinct points
		*/
		void initialize();
		
		/**
		Puts the points in order based on their function value
		*/
		void order(){			
			// need to preserve the previous relative ordering so STABLE SORT
			std::stable_sort(std::begin(points), std::end(points));			
		}
		
		/**
		Performs a reflection step
		@return whether the iteration terminates
		*/
		bool reflect();
		
		/**
		Performs an expand step
		*/
		void expand();		
		
		/**
		Performs the contract step
		@return whether iteration terminates
		*/
		bool contract();
		
		/**
		Performs a shrink step, results in updating all but best points
		*/
		void shrink();
		
		/**
		Gives an update after every iteration
		@param iter the iteration count
		*/
		void give_progress(int iter) const{
			std::cout << "Current simplex:\n";
			for(const auto& e : points){ // list all the points, function value and all
				std::cout << e << '\n';
			}			
			std::cout << "Iteration: " << iter << '\n'
				<< "Optimal Point: " << points[0] << '\n';
		}		
		
		/**
		Sets whether there should be a print out after each iteration
		@param print whether to print per iteration
		*/
		void iteration_display(bool print){
			print_per_iter = print;
		}
	};
	
	/* definitions */
	
	// utility stuff
	
	template<size_t argc, typename Fun, typename Container, std::size_t... Is >
	auto call(Fun&& f, Container&& list, patch::index_sequence<Is...> seq) -> decltype(f(list[Is]...)) {
		return f(list[Is]...);		
	}
	
	template<size_t argc, typename Fun, typename Container>
	auto unpack(Fun&& f, Container&& list) -> 
		decltype(call<argc,Fun, Container>(f, list, patch::build_index_sequence<argc>{})) {
		return call<argc,Fun, Container>(f, list, patch::build_index_sequence<argc>{});		
	}
	
	// some math stuff
	
	template<size_t param_count, typename precision>
	param_vec<param_count,precision>& 
		param_vec<param_count,precision>::operator+=(const param_vec& other){
		for(size_t i=0; i < param_count; ++i){ // update all param_count positions
			params[i] += other.params[i];
		}
		return *this;
	}

	template<size_t param_count, typename precision>	
	param_vec<param_count, precision>& 
		param_vec<param_count, precision>::operator-=(const param_vec& other){
		for(size_t i=0; i < param_count; ++i){ // update all param_count positions
			params[i] -= other.params[i];
		}
		return *this;
	}
	
	template<size_t param_count, typename precision>
	param_vec<param_count, precision>& 
		param_vec<param_count, precision>::operator*=(const precision& p){
		for(auto& e : params){ // multiply all entries
			e *= p;
		}
		return *this;
	}
	
	template<size_t param_count, typename precision>
	param_vec<param_count,precision>& 
		param_vec<param_count,precision>::operator/=(const precision& p){
		for(auto& e : params){ // divide all entries
			e /= p;
		}
		return *this;
	}
	
	/* stuff for Nelder-Mead */
	
	// constructor: uses max to make initial function values gigantic
	
	template<size_t param_count, typename precision>
	NelderMead<param_count,precision>::NelderMead() : 
		print_per_iter(true), xbest{ std::numeric_limits<precision>::max() ,{} },
		xr{ std::numeric_limits<precision>::max() ,{} },
		xe{ std::numeric_limits<precision>::max() ,{} },
		xc{ std::numeric_limits<precision>::max() ,{} },
		xcc{ std::numeric_limits<precision>::max() ,{} },
		guess{}, xbar{} {
		for (auto& p : points) { // set all simplex points
			p.f = std::numeric_limits<precision>::max(); // make all values really big
			p.x = param_type{};
		}
	}
	
	template<size_t param_count, typename precision>
	template<typename Fun>
	void NelderMead<param_count,precision>::set_objective(Fun&& _obj){
		obj = [=](const param_type& v)-> precision {
			return unpack<param_count>(_obj, v);
		};
	}
	
	// the full running...
	
	template<size_t param_count, typename precision>	
	void NelderMead<param_count,precision>::run(int num_iter){
		int iter = 0;
		initialize(); // start the simplex			
		order(); // place points in order						
		while(iter < num_iter){	// run specified number of iterations			
			bool reflected = reflect();	// whether reflect succeeds							
			if(!reflected){ // so went on to expand or contract...
				if(xr < points[0]){ // a new best						
					expand();
				} 
				else{ // just incremental improvement or none at all				
					bool contracted = contract(); // whether contract succeeds										
					if(!contracted){ // so need to shrink
						shrink();							
					}
				}
			}
			order(); // put things in order
			xbest = points[0]; // update the best
			++iter; // done one more step
			if(print_per_iter){ // should give update
				give_progress(iter);
			}
		}			
		std::cout << "Finished. Ran " << iter << " iterations.\n";
		std::cout << "Error: " << xbest.f << '\n';
		std::cout << "Optimal set: " << xbest << '\n';
	}
	
	// how everything begins
	
	template<size_t param_count, typename precision>
	void NelderMead<param_count,precision>::initialize(){			
		points[0].x = guess; // start at the guess place
		points[0].f = obj(points[0].x); // evaluate there
		
		// then perturb one point at a time
		for(size_t i=1; i < param_count+1; ++i){ // node there are param_count+1 slots, first filled
			auto pert = param_type{};
			pert[i-1] = 1; // can be changed of course: i-1 ranges from 0 ... param_count-1
			points[i].x = guess + pert; // pertub in just one direction
			points[i].f = obj(points[i].x); // evaluate
		}				
	}
	
	template<size_t param_count, typename precision>
	bool NelderMead<param_count,precision>::reflect(){
						
		// to be centroid
		xbar = param_type{};			
		
		for(auto itr = std::begin(points), last = std::end(points)-1; 
			itr != last; ++itr){ // average over all BUT the worst point
			xbar += itr->x;
		}			
		xbar /= param_count; // now proper centroid			
							
		xr.x = (1+rho)*xbar - rho*points[param_count].x; // our reflection point
		xr.f = obj(xr.x); // evaluate here							

		// new point isn't best, but better than second worst!
		// worst is at index param_count
		if(points[0] <= xr && xr < points[param_count-1]){				
			points[param_count] = xr;				
			return true;
		}
		else{ // did not accept new point as xr				
			return false;
		}
	}
	
	
	template<size_t param_count, typename precision>
	void NelderMead<param_count,precision>::expand(){
		
		xe.x = xbar + chi*(xr.x-xbar); // update expansion point
		xe.f = obj(xe.x);
		
		if(xe < xr){ // was better than reflected				
			points[param_count] = xe;
		} 
		else{ // xr was still better than this
			points[param_count] = xr;
		}
	}
	
	template<size_t param_count, typename precision>
	bool NelderMead<param_count,precision>::contract(){
		// for outside contraction
		if(points[param_count-1] <= xr && xr < points[param_count]){
			
			xc.x = xbar + gamma*(xr.x-xbar); // outside contraction point
			xc.f = obj(xc.x);
			
			if(xc <= xr){ // wish to accept xc
				points[param_count] = xc;
				return true;
			}
			else{ // reject
				return false;
			}
		}
		else{ // for inside contraction
			
			// inside contraction point
			xcc.x = xbar - gamma*(xbar - points[param_count].x);
			xcc.f = obj(xcc.x);
			
			if(xcc < points[param_count]){ // wish to accept xcc
				points[param_count] = xcc;
				return true;
			} 
			else{ // reject
				return false;
			}
		}					
	}
	
	template<size_t param_count, typename precision>
	void NelderMead<param_count,precision>::shrink(){
		
		// to store many new points and function values
		point_type extras[param_count];
		for(size_t i=0; i < param_count;++i){ // go through all but best
			extras[i].x = points[0].x + sigma*(points[i+1].x-points[0].x);				
		}
		for(auto& v : extras){ // evaluate objective at new points
			v.f = obj(v.x);			
		}
		for(size_t i=0; i < param_count; ++i){ // update all but best point
			points[i+1] = extras[i];
		}			
	}
	
}

#endif
