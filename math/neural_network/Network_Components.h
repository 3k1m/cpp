/**
@file Network_Components.h
@author Mike Lindstrom
@version 1

@brief this file defines the accesory classes and functions for the neural networks to work and function

@details In order we have:
- useful utility functions
- setting enumerative types
- activation classes
- cost classes
- layer class
*/

#ifndef _BASIC_NETWORK__NETWORK_BUILDER_
#define _BASIC_NETWORK__NETWORK_BUILDER_

#include<cmath>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<random>
#include<memory>
#include<deque>
#include<fstream>
#include<string>
#include<set>
#include<functional>

#include "Matrix.h"

// we define components of a network here, to be used by networks
namespace basic_network {

	/* Generically useful functions */

	/**
	ensures a matrix is a column vector
	@tparam T the type of data in the matrix
	@param _in the matrix to check
	*/
	template<typename T>
	void assert_column(const basic_math::matrix<T>& _in) {

		if (_in.size(2) != 1) { // if number of columns is not 1
			throw std::logic_error("required a column vector!"); // throw exception
		}

	}

	/**
	returns the minimum of two vaues
	@tparam any data type
	@param first the first
	@param second the second
	@return their minimum
	*/
	template<typename T>
	T min(const T& first, const T& second) {
		return first < second ? first : second;
	}

	/**
	returns the minimum of two entries, treating both as size types
	@tparam T the first data type
	@tparam S the second data type
	@param first the first
	@param second the second
	*/
	template<typename T, typename S>
	size_t min_size(const T& _first, const S& _second) {
		size_t first = static_cast<size_t>(_first), second = static_cast<size_t>(_second);
		return min(first, second);
	}

	/**
	power returns a power of 2 for a given type
	@param _in input value
	@return the given power of 2
	*/
	size_t pow2(const size_t _in) { // if it's 0, just return 1 otherwise recurse
		return (_in == 0) ? static_cast<size_t>(1) : static_cast<size_t>(2)*pow2(_in - 1);
	}

	/* enum types to set various options */

	/**
	@enum NETWORK_COST used for network policies in regards to the penalty term
	L2 means an objective to minimize the L2 norm error
	L1 means an objective to minimize the L1 norm error
	CROSS_ENTROPY means an objective to minimize the cross-entropy error
	*/
	enum class NETWORK_COST {
		L2,
		L1,
		CROSS_ENTROPY
	};

	/**
	@enum NETWORK_BINNING used for network policies in regards to the output format of the prediction term
	BUCKET for binary, ternary, k-ary classification problems
	SINGLE for a real valued output when a continuum of predictions is sought
	*/
	enum class NETWORK_BINNING {
		BUCKET,
		SINGLE
	};

	/**
	@enum NETWORK_HIDDEN_ACTIVATIONS used for network policies in regards to how the logits are transformed
	in a nonlinear form
	IDENTITY is identity function x -> x
	RELU is leaky relu x_i -> (x_i<0) ? a*x_i : x_i
	LOG is the "slow log" x_i -> (x_i>0) ? log(1+x_i) ? -log(1-x_i)
	SOFT is the soft max x_i -> exp(x_i) / sum (exp(x_j))
	*/
	enum class NETWORK_HIDDEN_ACTIVATIONS {
		IDENTITY,
		RELU,
		LOG,
		SOFT
	};

	/**
	@enum NETWORK_OUTPUT_ACTIVATIONS used for network policies in regards to the final nonlinear transformation
	IDENTITY is identity function x -> x
	RELU is leaky relu x_i -> (x_i<0) ? a*x_i : x_i
	LOG is the "slow log" x_i -> (x_i>0) ? log(1+x_i) ? -log(1-x_i)
	SOFT is the soft max x_i -> exp(x_i) / sum (exp(x_j))
	X_ABS_X is x -> x |x|
	*/
	enum class NETWORK_OUTPUT_ACTIVATIONS {
		IDENTITY,
		RELU,
		LOG,
		SOFT,
		X_ABS_X
	};

	/* The ACTIVATION CLASSES */

	/**
	@class soft_max applies the soft max thresholding to a vector of values
	@tparam T data type
	*/
	template<typename T>
	struct soft_max {

		static constexpr T eps = 1.e-4;

		/**
		Transform
		@param _in the input vector value
		@return the activated inputs
		*/
		static basic_math::matrix<T> transform(basic_math::matrix<T> _in) {

			T denominator = 0; // what we divide by

			T max_arg = 0;

			for (size_t i = 0, num_rows = _in.size(1); i < num_rows; ++i) { // find max of all elements of vector
				if (_in(i, 0) > max_arg) {
					max_arg = _in(i, 0);
				}
			}

			for (size_t i = 0, num_rows = _in.size(1); i < num_rows; ++i) { // deduct max from all elements
				_in(i, 0) -= max_arg;
			}

			for (size_t i = 0, num_rows = _in.size(1); i < num_rows; ++i) { // for every row of the vector
				_in(i, 0) = std::exp(_in(i, 0)); // exponentiate entry        
				denominator += _in(i, 0); // increase denominator
			}

			_in = _in / denominator; // normalize

									 // now we fix possible roundoff issues

			for (size_t i = 0, num_rows = _in.size(1); i < num_rows; ++i) { // for every row
				if (_in(i, 0) < eps) { // check if value really small and if so
					_in(i, 0) = eps; // just make the value small but hopefully nonzero
				}
				else if (1 - _in(i, 0) < eps) { // if the value is really close to 1
					_in(i, 0) = 1 - eps; // make it 1 minus some threshold
				}
			}

			return _in;
		}

		/**
		Derivative of activations with respect to z-values
		@param _z the input z-values
		@return da/dz
		*/
		basic_math::matrix<T> static dadz(basic_math::matrix<T> _z) {

			T max_arg = 0;

			for (size_t i = 0, num_rows = _z.size(1); i < num_rows; ++i) {
				if (_z(i, 0) > max_arg) {
					max_arg = _z(i, 0);
				}
			}

			for (size_t i = 0, num_rows = _z.size(1); i < num_rows; ++i) {
				_z(i, 0) -= max_arg;
			}


			basic_math::matrix<T> ret(_z.size(1), _z.size(1)); // start at all 0's matrix

			T denominator = 0;
			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each element of input
				denominator += std::exp(_z(i, 0)); // exponentiate entry adding to normalization
			}

			for (size_t i = 0, num_rows = ret.size(1); i < num_rows; ++i) { // for all rows of derivative
				for (size_t j = 0, num_cols = ret.size(2); j < num_cols; ++j) { // and columns
					if (i == j) { // special case if i equal j
						ret(i, j) += std::exp(_z(i, 0)) / denominator;
					}

					ret(i, j) -= std::exp(_z(i, 0)) * std::exp(_z(j, 0)) / (denominator*denominator);
				}
			}

			return ret;
		}

		/**
		Derivative between layers
		@param _z the z-values
		@param _W the weight matrix
		@return da^(ell+1)/da^ell
		*/
		static basic_math::matrix<T> dada(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _W) {
			return dadz(_z) * _W;
		}


		/**
		Derivative of activation with respect to biases
		@param _z the z-values
		@return da/dz
		*/
		static basic_math::matrix<T> dadb(const basic_math::matrix<T>& _z) {
			return dadz(_z);
		}

		/**
		Derivative of activtions with respect to weights
		@param _z the z-values
		@param _a the prior activations
		@return a vector where the ith index is the derivative of the ith activation with respect to the weights
		*/
		static std::vector< basic_math::matrix<T> > dadW(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _a) {

			auto dadz_mat = dadz(_z).T(); // row i col j = derivative of a_j wrt z_i

										  // REMARK: _a is a column vector, so _a.T() is a row vector!

			std::vector< basic_math::matrix<T> > tensor;  // the result is a tensor

			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each first index of tensor
				tensor.push_back(basic_math::col_times_row<T>(dadz_mat.get_col(i), _a.T()[0])); // each matrix is outer product of column times row
			}

			return tensor;

		}

	};

	/**
	@class relu applies the relu function to a vector of values
	@tparam T data type
	*/
	template<typename T>
	struct relu {

		static constexpr T a = 0.01;

		/**
		Transform
		@param _in the input vector value
		@return the activated inputs
		*/
		static basic_math::matrix<T> transform(basic_math::matrix<T> _in) {

			for (size_t i = 0, length = _in.size(1); i < length; ++i) { // for each element
				if (_in(i, 0) < 0) { // if negative, shrink slope
					_in(i, 0) = a*_in(i, 0);
				}
			}

			return _in;

		}

		/**
		Derivative of activations with respect to z-values
		@param _z the input z-values
		@return da/dz
		*/
		basic_math::matrix<T> static dadz(const basic_math::matrix<T>& _z) {

			basic_math::matrix<T> ret(_z.size(1), _z.size(1)); // start at all 0's matrix

			for (size_t i = 0, length = ret.size(1); i < length; ++i) { // for each element
				if (_z(i, 0) > 0) { // if the entry is positive, derivative of identity is 1
					ret(i, i) = 1;
				}
				else { // otherwise, derivative is a
					ret(i, i) = a;
				}
			}

			return ret;
		}

		/**
		Derivative between layers
		@param _z the z-values
		@param _W the weight matrix
		@return da^(ell+1)/da^ell
		*/
		static basic_math::matrix<T> dada(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _W) {
			return dadz(_z) * _W;
		}


		/**
		Derivative of activation with respect to biases
		@param _z the z-values
		@return da/dz
		*/
		static basic_math::matrix<T> dadb(const basic_math::matrix<T>& _z) {
			return dadz(_z);
		}

		/**
		Derivative of activtions with respect to weights
		@param _z the z-values
		@param _a the prior activations
		@return a vector where the ith index is the derivative of the ith activation with respect to the weights
		*/
		static std::vector< basic_math::matrix<T> > dadW(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _a) {

			auto dadz_mat = dadz(_z).T(); // row i col j = derivative of a_j wrt z_i

										  // REMARK: _a is a column vector, so _a.T() is a row vector!
			std::vector< basic_math::matrix<T> > tensor;  // the result is a tensor

			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each first index of tensor
				tensor.push_back(basic_math::col_times_row<T>(dadz_mat.get_col(i), _a.T()[0])); // each matrix is outer product of column times row
			}

			return tensor;
		}
	};



	/**
	@class identity applies the identity function to a vector of values
	@tparam T data type
	*/
	template<typename T>
	struct identity {

		/**
		Transform
		@param _in the input vector value
		@return the activated inputs
		*/
		static basic_math::matrix<T> transform(const basic_math::matrix<T> _in) {
			return { { _in(0,0) } }; // give an initializer list of initializer lists to make matrix
		}

		/**
		Derivative of activations with respect to z-values
		@param _z the input z-values
		@return da/dz
		*/
		basic_math::matrix<T> static dadz(const basic_math::matrix<T>& _z) {

			basic_math::matrix<T> ret(_z.size(1), _z.size(1)); // start at all 0's matrix

			for (size_t i = 0, length = ret.size(1); i < length; ++i) { // for each entry
				ret(i, i) = 1; // derivative is just identity matrix, 1's along diagonal
			}

			return ret;
		}

		/**
		Derivative between layers
		@param _z the z-values
		@param _W the weight matrix
		@return da^(ell+1)/da^ell
		*/
		static basic_math::matrix<T> dada(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _W) {
			return dadz(_z) * _W;
		}


		/**
		Derivative of activation with respect to biases
		@param _z the z-values
		@return da/dz
		*/
		static basic_math::matrix<T> dadb(const basic_math::matrix<T>& _z) {
			return dadz(_z);
		}

		/**
		Derivative of activtions with respect to weights
		@param _z the z-values
		@param _a the prior activations
		@return a vector where the ith index is the derivative of the ith activation with respect to the weights
		*/
		static std::vector< basic_math::matrix<T> > dadW(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _a) {

			auto dadz_mat = dadz(_z).T(); // row i col j = derivative of a_j wrt z_i

										  // REMARK: _a is a column vector, so _a.T() is a row vector!
			std::vector< basic_math::matrix<T> > tensor;  // the result is a tensor

			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each first index of tensor
				tensor.push_back(basic_math::col_times_row<T>(dadz_mat.get_col(i), _a.T()[0])); // each matrix is outer product of column times row
			}

			return tensor;

		}

	};

	/**
	@class slow_log is slow to grow as a function, can help with issues of unboundedness/instabilities, etc., but is slow,
	done componentwise
	@tparam T data type
	*/
	template<typename T>
	struct slow_log {

		/**
		Transform
		@param _in the input vector value
		@return the activated inputs
		*/
		static basic_math::matrix<T> transform(basic_math::matrix<T> in) {

			for (size_t i = 0, length = in.size(1); i < length; ++i) { // over every row of in, transform it depending on whether pos or neg
				in(i, 0) = (in(i, 0) > 0 ? std::log(in(i, 0) + 1) : -std::log(1 - in(i, 0))); // either do log(z+1) or log(1-z)
			}

			return in;
		}

		/**
		Derivative of activations with respect to z-values
		@param _z the input z-values
		@return da/dz
		*/
		basic_math::matrix<T> static dadz(const basic_math::matrix<T>& _z) {

			basic_math::matrix<T> ret(_z.size(1), _z.size(1)); // start at all 0's matrix

			for (size_t i = 0, length = ret.size(1); i < length; ++i) { // for each element
				ret(i, i) = (_z(i, 0) > 0 ? 1. / (_z(i, 0) + 1) : 1. / (1 - _z(i, 0))); // compute derivative piecewise, either 1/(z+1) or 1/(1-z)
			}

			return ret;
		}

		/**
		Derivative between layers
		@param _z the z-values
		@param _W the weight matrix
		@return da^(ell+1)/da^ell
		*/
		static basic_math::matrix<T> dada(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _W) {
			return dadz(_z) * _W;
		}


		/**
		Derivative of activation with respect to biases
		@param _z the z-values
		@return da/dz
		*/
		static basic_math::matrix<T> dadb(const basic_math::matrix<T>& _z) {
			return dadz(_z);
		}

		/**
		Derivative of activtions with respect to weights
		@param _z the z-values
		@param _a the prior activations
		@return a vector where the ith index is the derivative of the ith activation with respect to the weights
		*/
		static std::vector< basic_math::matrix<T> > dadW(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _a) {

			auto dadz_mat = dadz(_z).T(); // row i col j = derivative of a_j wrt z_i

										  // REMARK: _a is a column vector, so _a.T() is a row vector!
			std::vector< basic_math::matrix<T> > tensor;  // the result is a tensor

			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each first index of tensor
				tensor.push_back(basic_math::col_times_row<T>(dadz_mat.get_col(i), _a.T()[0])); // each matrix is outer product of column times row
			}

			return tensor;

		}

	};



	/**
	@class x_abs_x applies the x|x| function to all elements of a vector
	@tparam T data type
	*/
	template<typename T>
	struct x_abs_x {
		/**
		Transform
		@param _in the input vector value
		@return the activated inputs
		*/
		static basic_math::matrix<T> transform(basic_math::matrix<T> _in) {

			for (size_t i = 0, length = _in.size(1); i < length; ++i) { // for each element
				_in(i, 0) = (_in(i, 0) > 0 ? _in(i, 0)*_in(i, 0) : -_in(i, 0)*_in(i, 0));
			}

			return _in;
		}

		/**
		Derivative of activations with respect to z-values
		@param _z the input z-values
		@return da/dz
		*/
		basic_math::matrix<T> static dadz(const basic_math::matrix<T>& _z) {

			basic_math::matrix<T> ret(_z.size(1), _z.size(1)); // start at all 0's matrix

			for (size_t i = 0, length = ret.size(1); i < length; ++i) { // for each element
				if (_z(i, 0) > 0) { // if the entry is positive, derivative is 2z
					ret(i, i) = 2 * _z(i, 0);
				}
				else { // otherwise, derivative is -2z
					ret(i, i) = -2 * _z(i, 0);
				}
			}

			return ret;
		}

		/**
		Derivative between layers
		@param _z the z-values
		@param _W the weight matrix
		@return da^(ell+1)/da^ell
		*/
		static basic_math::matrix<T> dada(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _W) {
			return dadz(_z) * _W;
		}


		/**
		Derivative of activation with respect to biases
		@param _z the z-values
		@return da/dz
		*/
		static basic_math::matrix<T> dadb(const basic_math::matrix<T>& _z) {
			return dadz(_z);
		}

		/**
		Derivative of activtions with respect to weights
		@param _z the z-values
		@param _a the prior activations
		@return a vector where the ith index is the derivative of the ith activation with respect to the weights
		*/
		static std::vector< basic_math::matrix<T> > dadW(const basic_math::matrix<T>& _z, const basic_math::matrix<T>& _a) {

			auto dadz_mat = dadz(_z).T(); // row i col j = derivative of a_j wrt z_i

										  // REMARK: _a is a column vector, so _a.T() is a row vector!
			std::vector< basic_math::matrix<T> > tensor;  // the result is a tensor

			for (size_t i = 0, length = _z.size(1); i < length; ++i) { // for each first index of tensor
				tensor.push_back(basic_math::col_times_row<T>(dadz_mat.get_col(i), _a.T()[0])); // each matrix is outer product of column times row
			}

			return tensor;
		}
	};



	/* The COST CLASSES */

	/**
	@class log_cost this is the cross-entropy cost implementation such that the error in a prediction a with ground truth
	y is sum_i -y_i log(a_i)
	@tparam T the data type used
	*/
	template<typename T>
	struct log_cost {
		/**
		Computes a single non-normalized component of the cost
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		T static cost(const basic_math::matrix<T>& _y, const basic_math::matrix<T>& _a) {
			T err = 0;

			for (size_t i = 0, length = _y.size(1); i < length; ++i) { // for each index of the exact and final activations

				err += -(_y(i, 0)*log(_a(i, 0)));

			}

			return err;
		}

		/**
		Computes the rate of change of cost with respect to activations
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		basic_math::matrix<T> static dCda(basic_math::matrix<T> _y, const basic_math::matrix<T>& _a) {

			for (size_t i = 0, length = _y.size(1); i < length; ++i) { // for each index of the exact and final activations, 
																	   // set rate of change of cost with respect to given activation

				_y(i, 0) = -_y(i, 0) / _a(i, 0);

			}
			return _y;
		}


	};


	/**
	@class quadratic_cost gives a classical sum of squares error
	@tparam T the data type used
	*/
	template<typename T>
	struct quadratic_cost {
		/**
		Computes a single non-normalized component of the cost
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		T static cost(const basic_math::matrix<T>& _y, const basic_math::matrix<T>& _a) {
			T err = 0;

			for (size_t i = 0, length = _y.size(1); i < length; ++i) { // for each index of the exact and final activations
				err += (_y(i, 0) - _a(i, 0))*(_y(i, 0) - _a(i, 0));
			}

			return err;
		}

		/**
		Computes the rate of change of cost with respect to activations
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		basic_math::matrix<T> static dCda(basic_math::matrix<T> _y, const basic_math::matrix<T>& _a) {

			return -2 * (_y - _a); // d/da (y-a)^T (y-a) = -2(y-a)
		}


	};


	/**
	@class L1_cost gives a sum of absolute values as error
	@tparam T the data type used
	*/
	template<typename T>
	struct L1_cost {
		/**
		Computes a single non-normalized component of the cost
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		T static cost(const basic_math::matrix<T>& _y, const basic_math::matrix<T>& _a) {
			T err = 0;

			for (size_t i = 0, length = _y.size(1); i < length; ++i) { // for each index of the exact and final activations
				err += std::fabs(_y(i, 0) - _a(i, 0));
			}

			return err;
		}

		/**
		Computes the rate of change of cost with respect to activations
		@param _y the correct resulting vector
		@param _a the final activation vector
		*/
		basic_math::matrix<T> static dCda(basic_math::matrix<T> _y, const basic_math::matrix<T>& _a) {

			for (size_t i = 0, len_y = _y.size(1); i < len_y; ++i) {
				_y(i, 0) = (_y(i, 0) < _a(i, 0) ? 1 : -1);
			}

			return _y; // d/da |y-a| component wise is -sgn(y-a) componentwise
		}


	};

	/* Neural networks are comprised of LAYERS */

	/**
	@class layer stores an array of nodes
	with their biases and a weight matrix transitioning into
	the layer
	@tparam T the data type stored, double by default, must be a floating point
	*/
	template<typename T = double>
	class layer {

	private:
		const size_t left_nodes; // number of prior nodes
		const size_t these_nodes; // number of output nodes
		basic_math::matrix<T> biases; // the biases, these_nodes by 1
		basic_math::matrix<T> weights; // transition weights

	public:


		/**
		constructor sets input and output nodes, matrices, biases, and function call
		@param _left number of lower layer nodes
		@param _here number of nodes of given layer
		@param _sig the type of sigmoid used, the classic sigmoid by default
		*/
		layer(size_t _left, size_t _here) : left_nodes(_left), these_nodes(_here), biases(these_nodes, 1), weights(these_nodes, left_nodes) {}

		/**
		returns biases size
		@return length of biases
		*/
		size_t biases_size() const { return biases.size(1); }

		/**
		returns weights size
		@return a pair with first dimension rows and second columns
		*/
		auto weights_size() const { return std::make_pair(weights.size(1), weights.size(2)); }

		/**
		to access the weights matrix
		@return the weights matrix
		*/
		const basic_math::matrix<T>& get_weights() const { return weights; }

		/**
		to access the biases vector
		@return the biases vector
		*/
		const basic_math::matrix<T>& get_biases() const { return biases; }

		/**
		call operator to set biases
		@param i the row index
		@return the reference to the element
		*/
		T& operator()(const size_t i) { return biases(i, 0); } // return ith index of biases

															   /**
															   call operator to get biases
															   @param i the row index
															   @return the reference to the element
															   */
		const T& operator()(const size_t i) const { return biases(i, 0); } // return ith index of biases

																		   /**
																		   call operator to set weights
																		   @param i the row index
																		   @param j the column index
																		   @return the reference to the element
																		   */
		T& operator()(const size_t i, const size_t j) { return weights(i, j); } // return i j th entry of weights

																				/**
																				call operator to get weights
																				@param i the row index
																				@param j the column index
																				@return the reference to the element
																				*/
		const T& operator()(const size_t i, const size_t j) const { return weights(i, j); } // return i j th entry of weights

																							/**
																							adds the given matrix (vector) to the biases
																							@param _rhs the vector to add
																							*/
		void add_biases(const basic_math::matrix<T>& _rhs) { biases += _rhs; }

		/**
		adds the given matrix to the weights
		@param _rhs the matrix to add
		*/
		void add_weights(const basic_math::matrix<T>& _rhs) { weights += _rhs; }

		/*
		computes output of given input via W*in + bias
		@param _in the input value
		@return the output
		*/
		basic_math::matrix<T> linear(const basic_math::matrix<T>& _in) const { return weights*_in + biases; }

	};

	/**
	@class in_out stores an input and corresponding output
	@tparam T the data type used
	*/
	template<typename T = double>
	struct in_out {
		basic_math::matrix<T> input;
		basic_math::matrix<T> output;

		/**
		constructor sets the input and output
		@param _in the input values
		@param _out the known output
		*/
		in_out(const basic_math::matrix<T>& _in, const basic_math::matrix<T>& _out) : input(_in), output(_out) {}

		/**
		a comparison operator so these data can be sorted
		@param _right the right structure
		@return whether current < _right
		*/
		bool operator<(const in_out& _right) const;

	};


	/* DEFINITIONS */

	/* The operator< for in_out's */


	template<typename T>
	bool in_out<T>::operator<(const in_out<T>& _right) const {
		size_t i = 0; // start at 0
		while ((i < input.size(1)) && (i < _right.input.size(1))) { // while both in range
			if (input(i, 0) < _right.input(i, 0)) { // somewhere left < right
				return true;
			}
			else if (_right.input(i, 0) < input(i, 0)) { // somwhere right < left
				return false;
			}
			else { // then equal so move on
				++i;
			}
		}

		// now check if there is a longer one
		if (input.size(1) < _right.input.size(1)) { // more on right
			return true;
		}
		else if (_right.input.size(1) < input.size(1)) { // more on left
			return false;
		}

		// if here then need to look at the outputs
		i = 0; // move i back to 0
		while ((i < output.size(1)) && (i < _right.output.size(1))) { // while both in range
			if (output(i, 0) < _right.output(i, 0)) { // somewhere left < right
				return true;
			}
			else if (_right.output(i, 0) < output(i, 0)) { // somwhere right < left
				return false;
			}
			else { // then equal so move on
				++i;
			}
		}

		// now check if there is a longer one
		if (output.size(1) < _right.output.size(1)) { // more on right
			return true;
		}
		else { // more on left or equal so false!
			return false;
		}

	} // end < definition



}

#endif
