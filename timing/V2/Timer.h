#include <iostream>

/**
@file Timer.h
@version 2.0
@author Mike Lindstrom
@date Apr 2022
@brief This file defines a simple class that can do highly accurate timings for events in seconds, milliseconds, microseconds, or nanoseconds.
C++17 is required!

@details This header file can be used to define a timer class to time C++ code very accurately.
Times can be measured in seconds (s), milliseconds (m), microseconds (u), or nanoseconds (n), and
precision for those times can be done using float, double, or long double.
The templated class timer is templated by the time duration and precision.
Once created, it has a tick function to restart timing,
and a tock function function to stop timing returning an interval object representing a time duration which can be printed.
The interval also has a function get_value to retrieve a pair with the raw data (number and units).

Examples:
1)
simple_timer::timer<'s'> t; // measure time in seconds, with default float precision, time starts now!
do_code();
std::cout << t.tock(); // will display the time used
2)
simple_timer::timer<'u', double> t2; // measure time in microseconds with double precision
do_work();
t2.tick(); // start timing
do_code();
std::cout << t2.tock(); // will display time in microseconds
3)
simple_timer::timer<> t3; // will measure in milliseconds with float precision - all defaults! time starts now!
do_code1();
auto measured1 = t3.tock(); // measured stores the time duration for do_code1
t3.tick();
do_code2();
auto measured2 = t3.tock(); // measures time duration for do_code2
std::cout << measured1 << ' ' << measured2.get_value().first << 
  measured2.get_value().second;
*/

#ifndef _SIMPLE_TIMER__TIMER_
#define _SIMPLE_TIMER__TIMER_

#include<chrono>
#include<iostream>
#include<utility>

namespace simple_timer {

	// alias for a steady period
	using duration_type = std::chrono::steady_clock::duration;

	// only evaluates to type void* if correct units for seconds 
	// and valid floating point type for duration
	template<char timer_type, typename precision>
	using time_sfinae =
		std::enable_if_t< (timer_type == 's' || timer_type == 'm' || timer_type == 'u' || timer_type == 'n')
		&& std::is_floating_point_v<precision>, void* >;

	/**
	@struct duration_to_time helper class to convert duration_types to desired time with precision
	@tparam timer_type the type of time: 's', 'm', 'u', or 'n'
	@tparam precision the level of precision we want
	*/
	template<char timer_type, typename precision>
	struct duration_to_time;

	/**
	@class timer, by default it times in milliseconds with float precision
	@tparam timer_type the type of time: 's', 'm', 'r', or 'n' - input MUST be one of those chars
	@tparam precision the level of precision we want - input MUST be a floating type
	*/
	template<char timer_type = 'm',
		typename precision = float,
		time_sfinae<timer_type, precision> = nullptr >
		class timer {
		private:
			std::chrono::steady_clock::time_point init; // when time begins
			duration_type duration; // how long

		public:
			/**
			Default constructor, will initialize init to current time and duration to 0
			*/
			timer() noexcept : init(std::chrono::steady_clock::now()), duration() {}

			/**
			This function starts the timer
			*/
			void tick() noexcept {
				init = std::chrono::steady_clock::now();
			}

			/**
			This function returns the proper symbol for the time type
			@return "s" for seconds, "ms" for milliseconds, "us" for microseconds, and "ns" for nanoseconds
			*/
			static const char* symbol() noexcept;

			/**
			@class interval represents a time interval that the timer has measured
			*/
			class interval {
			private:
				precision len; // stores a length of time given requested precision

			public:
				/**
				Constructor for the class to store length of time
				@param _len the length of time
				*/
				interval(const precision& _len) noexcept : len(_len) {}

				/**
				This allows for the intervals to be printed
				@param o an ostream
				@param measured the interval
				@return the stream
				*/
				friend std::ostream& operator<<(std::ostream& o, const interval& measured) {
					return o << measured.len << timer<timer_type, precision>::symbol();
				}

				/**
				retrieve the raw data for the interval
				@return a pair whose first value is the measured length (without units)
				and whose second value stores the units of measure
				*/
				std::pair<precision, const char*> get_value() const noexcept {
					return { len, timer<timer_type, precision>::symbol() };
				}
			};

			/**
			This function stops the timer
			@return a time interval from tick to tock
			*/
			interval tock() noexcept {
				duration = std::chrono::steady_clock::now() - init; // calculate duration
				return interval(duration_to_time<timer_type, precision>::format_duration(duration)); // give interval
			}
	};

	/*
	specializations of the duration_to_time class for s, m, u, and n
	*/

	template<typename precision>
	struct duration_to_time<'s', precision> {
		static precision format_duration(duration_type duration) {
			return std::chrono::duration<precision>(duration).count(); // get seconds
		}
	};

	template<typename precision>
	struct duration_to_time<'m', precision> {
		static precision format_duration(duration_type duration) {
			return std::chrono::duration<precision, std::milli>(duration).count(); // get milliseconds
		}
	};

	template<typename precision>
	struct duration_to_time<'u', precision> {
		static precision format_duration(duration_type duration) {
			return std::chrono::duration<precision, std::micro>(duration).count(); // get microseconds
		}
	};

	template<typename precision>
	struct duration_to_time<'n', precision> {
		static precision format_duration(duration_type duration) {
			return std::chrono::duration<precision, std::nano>(duration).count(); // get nanoseconds
		}
	};

	// definition of the symbol function
	template<char timer_type, typename precision, time_sfinae<timer_type, precision> p>
	const char* timer<timer_type, precision, p>::symbol() noexcept {
		switch (timer_type) {
		case 's': return "s"; // seconds
		case 'm': return "ms"; // milliseconds
		case 'u': return "us"; // microseconds (can't write mu)
		case 'n': return "ns"; // nanoseconds
		default: return ""; // never happens
		}
	}
}

#endif
