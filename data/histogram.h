/**
@file histogram.h defines a histogram class that can be used to tabulate and bin data
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#ifndef _DATA__SIMPLE_HISTOGRAM_
#define _DATA__SIMPLE_HISTOGRAM_

#include<iostream>
#include<iomanip>
#include<string>
#include<map>
#include<numeric>
#include<cmath>
#include<sstream>

namespace data {

	/**
	@class simple_histogram represents a basic
	histogram with a fixed number of bins/range
	*/
	class simple_histogram {
	public:
		/**
		constructor to set basic logic of class
		@param _num_bins how many bins to use
		@param _num_tokens how many total tokens to use
		@param _min the lower bound (values less than this get chunked to lowest bin)
		@param _max the upper bound (values larger than or equal to this get chunked to highest bin)
		*/
		simple_histogram(size_t _num_bins, size_t _num_tokens, double _min, double _max);

		/**
		adds a value to the data
		@param val the value to add
		*/
		void insert(double val);

		/**
		displays the results
		@param out a stream to write to
		*/
		void display(std::ostream& out) const;

		/**
		how many data are present
		@return the total number of values
		*/
		size_t size() const noexcept;

	private:
		size_t num_bins; // number of bins used 
		size_t num_tokens; // number of tokens to place 
		double min, max; // lower and upper range values 
		double bin_width; // the bin widths 
		size_t sz; // number of values present 

		// bin index, label, and count grouped together 
		std::map<size_t, std::pair<std::string, size_t>> idx_label_count;
		size_t label_width;

		/**
		computes the bin a value belongs to
		@param val the value to assign a bin to
		@return the bin index
		*/
		size_t assign(double val) const;

		/**
		rounds a double to size_t
		@param d the double to round
		@return the nearest size_t integral value
		*/
		size_t round(double d) const noexcept;

		/**
		converts a double to a string
		@param d the double to convert
		@return the string representation
		*/
		std::string to_string(double d);

		/**
		initializes the labels and counts
		*/
		void init_counts();

	};

}

#endif
