/**
@file ArrayVector.h
@author Mike Lindstrom
@version 1
@date November 2019

@brief I have found this sort of functionality of an array-based class that can do basic 
vector operations quite useful
*/

#ifndef _BASIC_MATH__ARRAY_VECTOR_
#define _BASIC_MATH__ARRAY_VECTOR_

#include<iostream>

namespace basic_math {

	/**
	@class array_vector stores an array representing coordinates of an object in space
	@tparam dim the vector dimension
	@tparam precision the floating point precision to use and store
	*/
	template<size_t dim, typename precision = double>
	class array_vector {
	private:
		// array of parameters to optimize through
		precision coords[dim];

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
		constexpr void construct_helper(size_t pos, Arg&& val) {
			coords[pos] = std::forward<Arg>(val);
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
		constexpr void construct_helper(size_t pos, Arg&& val, Args&& ... vals) {
			if (pos < dim) { // provided still in range
				coords[pos] = std::forward<Arg>(val);
				construct_helper(pos + 1, std::forward<Args>(vals)...);
			}
		}

	public:

		/**
		returns iterator to beginning
		@return a pointer to first element
		*/
		constexpr iterator begin() {
			return &coords[0];
		}

		/**
		returns iterator past the end
		@return pointer to past-end
		*/
		constexpr iterator end() {
			return &coords[dim];
		}

		/**
		returns const_iterator to beginning
		@return a pointer to const, for first element
		*/
		constexpr const_iterator begin() const {
			return &coords[0];
		}

		/**
		returns const_iterator to past the end
		@return a pointer to const, for past-end
		*/
		constexpr const_iterator end() const {
			return &coords[dim];
		}

		/**
		constructor accepts a variadic list of arguments
		@tparam ... Args the types of arguments
		@param ... vals their values
		*/
		template<typename ... Args>
		constexpr array_vector(Args&& ... vals) {
			construct_helper(0, std::move(vals)...);
		}

		/**
		we need a constructor accepting L-value to non-const to prevent the variadic
		constructor from taking over: but we just call the regular copy constructor
		*/
		constexpr array_vector(array_vector& v) : array_vector(const_cast<const array_vector&>(v)) {}

		/**
		due to a bug in Visual Studio, it is necessary to define this
		copy constructor explicitly. other compilers like g++ allow = default
		@param other the other array_vector
		*/
		constexpr array_vector(const array_vector& other) {
			for (size_t i = 0; i < dim; ++i) { // copy entries one by one
				coords[i] = other.coords[i];
			}
		}

		/*
		enable more copy/move semantics
		*/

		constexpr array_vector(array_vector&&) noexcept = default;
		constexpr array_vector& operator=(const array_vector&) = default;
		constexpr array_vector& operator=(array_vector&&) = default;

		/**
		default constructor sets all values to zero
		*/
		constexpr array_vector() {
			for (auto& p : coords) { // make all values in the array 0
				p = 0;
			}
		}

		/**
		subscript operator, const
		@param i the index
		@return reference to const for item
		*/
		constexpr const precision& operator[](size_t i) const { return coords[i]; }

		/**
		subscript operator, non-const
		@param i the index
		@return reference to that item
		*/
		constexpr precision& operator[](size_t i) { return coords[i]; }

		/**
		defines += math operator to add right to left
		@param other the right-hand argument
		@return updated class after adding entries from right to its entries
		*/
		constexpr array_vector& operator+=(const array_vector& other);

		/**
		defines -= math operator to subtract right from left
		@param other the right-hand argument
		@return updated class after subtracting entries from right from its entries
		*/
		constexpr array_vector& operator-=(const array_vector& other);

		/**
		defines *= math operator to multiply left by scalar on right
		@param p the right-hand scalar argument
		@return updated class after multipying all its entries by p
		*/
		constexpr array_vector& operator*=(const precision& p);

		/**
		defines /= math operator to divide left by scalar on right
		@param p the right-hand scalar argument
		@return updated class after dividing all its entries by p
		*/
		constexpr array_vector& operator/=(const precision& p);

		/* we make these functions friends to avoid issues with scalar type deductions */

		/**
		multiples a array_vector by a scalar
		@param left the array_vector on the left
		@param p the scalar
		@return the product
		*/
		constexpr friend array_vector operator*(array_vector left, const precision& p) {
			return left *= p;
		}

		/**
		multiples a scalar with a array_vector
		@param p the scalar
		@param right the array_vector
		@return the product
		*/
		constexpr friend array_vector operator*(const precision& p, array_vector right) {
			return right *= p;
		}

		/**
		divides a array_vector by a scalar
		@param left the array_vector
		@param p the scalar
		@return the result after division
		*/
		constexpr friend array_vector operator/(array_vector left, const precision& p) {
			return left /= p;
		}

		friend std::ostream& operator<<(std::ostream& out, const array_vector<dim,precision>& vec) {
			out << '[';
			auto it = vec.begin(), past_end = vec.end();
			for (/*empty*/; it < past_end - 1; ++it) { // do all but last
				out << *it << ", ";
			}
			out << *it << "]";
			return out;
		}

		friend std::istream& operator>>(std::istream& in, array_vector<dim,precision>& vec) {
			for (auto& c : vec) { // write to each component of vec
				in >> c;
			}
			return in;
		}
	};

	// define the member +=, -=, *=, /=

	template<size_t dim, typename precision>
	constexpr array_vector<dim, precision>&
		array_vector<dim, precision>::operator+=(const array_vector& other) {
		for (size_t i = 0; i < dim; ++i) { // update all dim positions
			coords[i] += other.coords[i];
		}
		return *this;
	}

	template<size_t dim, typename precision>
	constexpr array_vector<dim, precision>&
		array_vector<dim, precision>::operator-=(const array_vector& other) {
		for (size_t i = 0; i < dim; ++i) { // update all dim positions
			coords[i] -= other.coords[i];
		}
		return *this;
	}

	template<size_t dim, typename precision>
	constexpr array_vector<dim, precision>&
		array_vector<dim, precision>::operator*=(const precision& p) {
		for (auto& e : coords) { // multiply all entries
			e *= p;
		}
		return *this;
	}

	template<size_t dim, typename precision>
	constexpr array_vector<dim, precision>&
		array_vector<dim, precision>::operator/=(const precision& p) {
		for (auto& e : coords) { // divide all entries
			e /= p;
		}
		return *this;
	}

	/**
	adds two array_vectors
	@param left the left
	@param right the right
	@return their sum
	*/
	template<size_t dim, typename precision = double>
	constexpr array_vector<dim, precision> operator+(array_vector<dim, precision> left,
		const array_vector<dim, precision>& right) {
		return left += right;
	}

	/**
	subtracts two array_vectors
	@param left the left
	@param right the right
	@return their difference
	*/
	template<size_t dim, typename precision = double>
	constexpr array_vector<dim, precision> operator-(array_vector<dim, precision> left,
		const array_vector<dim, precision>& right) {
		return left -= right;
	}

}

#endif

