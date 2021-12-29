/**
@file histogram.cpp provides implementations for a histogram class
@author Mike Lindstrom
@version 1.0
@date Dec 2021
@copyright under GNU Affero General Public License v3.0
*/

#include<sstream>

#include "histogram.h"

namespace data {

	size_t simple_histogram::round(double d) const noexcept {
		return static_cast<size_t>(std::round(d));
	}

	std::string simple_histogram::to_string(double d) {
		std::ostringstream oss;
		oss << d;
		return oss.str();
	}

	void simple_histogram::init_counts() {
		for (size_t i = 0; i < num_bins; ++i) { // at each bin index
			std::string label_low = to_string(min + i * bin_width);
			std::string label_high = to_string(min + (i + 1) * bin_width);
			idx_label_count[i] = std::make_pair(label_low + "-" + label_high, static_cast<size_t>(0));
		}

		// in this case accumulate uses <, returning the max in place of adding to get the max 	
		label_width = std::accumulate(idx_label_count.begin(),
			idx_label_count.end(), static_cast<size_t>(0),
			[](size_t s, const auto& p) {
				const size_t p_str_size = p.second.first.size();
				if (s < p_str_size) { // bigger size 
					return p_str_size;
				}
				else { // not bigger 
					return s;
				}
			});
	}


	simple_histogram::simple_histogram(size_t _num_bins, size_t _num_tokens, double _min, double _max) :
		num_bins(_num_bins), num_tokens(_num_tokens), min(_min), max(_max), bin_width((max - min) / num_bins), sz(0)
	{
		init_counts();
	}

	void simple_histogram::insert(double val) {
		++idx_label_count[assign(val)].second;
		++sz;
	}

	size_t simple_histogram::assign(double val) const {
		if (min < val && val < max) { // normal fitting 
			return static_cast<size_t>((val - min) / bin_width);
		}
		else if (val < max) { // minimal bucket 
			return 0;
		}
		else { // maximal bucket 
			return num_bins - 1;
		}
	}

	void simple_histogram::display(std::ostream& out) const {
		for (const auto& p : idx_label_count) { // go over all histogram bins 
			// how many tokens allocated: fraction of total times total tokens 
			const size_t tokens = round(static_cast<double>(p.second.second) * num_tokens / sz);
			out << std::setw(label_width);
			out << p.second.first << ":";
			out << std::string(tokens, '*') << '\n';
		}
	}

	size_t simple_histogram::size() const noexcept {
		return sz;
	}

}
