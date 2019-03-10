/**
@file Array.h
@author Mike Lindstrom
@brief This code illustrates template syntax
This was written as an example for PIC 10B, UCLA
*/

#ifndef _BASIC_ARRAY_
#define _BASIC_ARRAY_

#include<cstddef>
#include<utility>

namespace basic {

	/**
	@class Array serves as an example class for a templated array class. It
	wraps around a normal C-style array to become a class-object.
	@tparam T the type being stored
	@tparam N the number of elements
	*/
	template<typename T, std::size_t N>
	class Array {
	private:
		T values[N]; // stores a static array as member

	public:
		/**
		@typedef value_type represents the type within the array
		*/
		using value_type = T;
		/**
		@typedef reference represents a non-const reference to T
		*/
		using reference = T&;
		/**
		@typedef const_reference represents a reference to const T
		*/
		using const_reference = T&;

		/**
		@class ArrayView behaves kind of like a string_view, allowing
		for a view of the Array without ownership of its values
		*/
		class ArrayView;

		/**
		Default constructor: value initializes all members of the array
		*/
		constexpr Array() : values{} {}

		/**
		Subscript operator, const version, returns reference to const
		@param i the index of value to access
		@return a reference to const for that value
		*/
		constexpr const_reference operator[](std::size_t i) const {
			return values[i];
		}

		/**
		Subscript operator, non-const version, returns reference
		@param i the index of value to access
		@return a reference for that value
		*/
		constexpr reference operator[](std::size_t i) {
			return values[i];
		}

		/**
		Emplace function, constructs a T object from variadic list of arguments
		at a given position
		@tparam ... Types various types used in construction
		@param i index of value to overwrite
		@param ... vals the values used in construction
		*/
		template<typename ... Types>
		constexpr void emplace(std::size_t i, Types&& ... vals);

		/**
		returns a non-owning ArrayView of the array objects
		@param begin_index initial index in range, 0 by default
		@param past_end_index, index just past the end, N by default
		*/
		constexpr ArrayView get_view(std::size_t begin_index = 0,
			std::size_t past_end_index = N) const;
	};

	// definition of Array::ArrayView

	template<typename T, std::size_t N>
	class Array<T, N>::ArrayView {
	private:
		const T* first; // its first entry
		const T* past_end; // past its last entry
	public:
		/**
		Constructor, sets pointers to first and past-end
		@param _first the beginning pointer
		@param _past_end past the end pointer
		*/
		constexpr ArrayView(const T* _first, const T* _past_end);

		/**
		Function prints an ArrayView to the console
		@param av the ArrayView to print
		*/
		friend void print(const ArrayView& av) {
			std::cout << "[ ";

			// print from first but do not include past_end!
			for (const T* it = av.first; it < av.past_end; ++it) {
				std::cout << *it << " ";
			}
			std::cout << "]";
		}
	};

	// defining the ArrayView constructor

	template<typename T, std::size_t N>
	constexpr Array<T, N>::ArrayView::ArrayView(const T* _first, const T* _past_end) :
		first(_first), past_end(_past_end) {}

	// defining the emplace function
	// note how outside the interface, we need to repeat both layers of templates!

	template<typename T, std::size_t N>
	template<typename ... Types>
	constexpr void Array<T,N>::emplace(std::size_t i, Types&& ... vals) {
		values[i] = T(std::forward<Types>(vals)...);
	}

	// defining the get_view function


	template<typename T, std::size_t N>
	constexpr typename Array<T, N>::ArrayView Array<T,N>::get_view(std::size_t begin_index,
		std::size_t past_end_index) const {
		return ArrayView(values + begin_index, values + past_end_index);
	}


	// ALTERNATIVE TO ABOVE DEFINITION TO AVOID THE TYPENAME
	// NEED TO USE THE AUTO FUNCTION NOTATION

	/*template<typename T, std::size_t N>
	constexpr auto Array<T, N>::get_view(std::size_t begin_index,
		std::size_t past_end_index) const -> ArrayView {
		return ArrayView(values + begin_index, values + past_end_index);
	}*/

}

#endif
