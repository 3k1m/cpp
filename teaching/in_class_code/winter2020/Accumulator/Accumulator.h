#ifndef _ACCUMULATOR_
#define _ACCUMULATOR_

// NEVER using namespace std; 
// in a header file

/**
@class Accumulator can add up
numbers and give a total
*/
class Accumulator {
public:
	/**
	Default constructor: starts off
	with a total of 0
	*/
	Accumulator();

	/**
	Constructor starts the total off at
	some offset value
	@param _offset the offset value
	*/
	Accumulator(int _offset);

	/**
	function adds to the total
	@param _to_add the value to add
	*/
	void add(int _to_add); /* mutator no const */

	/**
	returns the total of the Accumulator
	@return the cumulative total
	*/
	int get_total() const; /* accessor: const */

private: // for now you can ignore this
	int total;

};


#endif
