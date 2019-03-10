/**
@file Wrapper.h
@author Mike Lindstrom

@brief This code illustrates template syntax

This is for PIC 10B, UCLA
*/

#ifndef _WRAPPER_
#define _WRAPPER_

#include<iostream>
#include<utility>

namespace basic {

	/**
	@brief this class wraps around a data type
	@tparam T the data type being wrapped
	*/
	template<typename T>
	class Wrapper {
	private:
		T member; // its member variable

	public:
		/**
		Default constructor: value initializes fundamental types, default constructs class types
		*/
		Wrapper() : member() {}

		/**
		Constructor accepting an input
		@tparam S an arbitrary type
		@param s the value given, will be converted to a T and stored as member
		*/
		template<typename S>
		Wrapper(const S& s);
		
		/**
		Nested class ref behaves as a reference
		*/
		class ref {
			T& val; // reference member
		public:
			/**
			Constructor accepting parameter to reference
			@param _val the value to reference
			*/
			ref(T& _val) : val(_val) {}

			/**
			Member retrieves by reference
			@return a reference to the stored object - note the const is appropriate!!! (like a const pointer, the
			reference itself cannot be changed)
			*/
			T& get() const { return val; }

			/**
			Equality operator checks if two ref values reference the same object
			@param rhs the other object
			*/
			friend bool operator==(const ref& left, const ref& right) {
				return &left.val == &right.val;
			}

			/**
			Emplace function to overwrite the referenced object
			with parameters passed
			@tparam Types any types
			@tparam params the values used to overwrite the object
			*/
			template<typename... Types>
			void emplace(Types&&... params) {
				val = T(std::forward<Types>(params)...);
			}
		};

		/**
		Returns a reference to the class member
		@return the reference class object
		*/
		ref get_ref() {
			return ref(member);
		}

		/**
		Nested class const_ref behaves as a reference to const
		*/
		class const_ref;

		/**
		Returns a reference to const to the class member
		@return the const reference class object
		*/
		const_ref get_const_ref() const;
		
		/**
		Swaps two Wrappers by swapping what they store
		@param other the other wrapper
		*/
		void swap(Wrapper& other){
			using std::swap; // enable ADL
			swap(member, other.member);
		}
	};

	// defining the Wrapper constructor accepting input
	template<typename T> // list Wrapper type
	template<typename S> // and type constructor receives
	Wrapper<T>::Wrapper(const S& s) : member(static_cast<T>(s)) {} // casts input to T and stores

	// defining the const_ref class nested within Wrapper
	template<typename T> // need to list the Wrapper type
	class Wrapper<T>::const_ref {
	private:
		const T& val; // reference member is const
	public:
		/**
		Constructor accepts value to reference via const
		@param _val the value to reference
		*/
		const_ref(const T& _val); 

		/**
		accessor retrives a reference to const for the value reference by this class
		@return a reference to const version of the stored object
		*/
		const T& get() const { return val; }
	};

	// define the constructor
	template<typename T> // list type of Wrapper plus scope of nested class
	Wrapper<T>::const_ref::const_ref(const T& _val) : val(_val) {}

	// define the get_const_ref member
	template<typename T> // the type of Wrapper stated
	typename Wrapper<T>::const_ref Wrapper<T>::get_const_ref() const { // need to add typename to be clear with compiler it is a type
		return const_ref(member);
	}

	/**
	Function prints a Wrapper object to console
	@tparam T the type stored by the wrapper
	@param w the Wrapper object to print
	*/
	template<typename T>
	void print_Wrapper(const Wrapper<T>& w) {
		std::cout << w.get_const_ref().get();
	}


}

#endif
