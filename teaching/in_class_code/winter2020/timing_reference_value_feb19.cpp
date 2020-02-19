#ifndef _SIMPLE_TIMER__TIMER_
#define _SIMPLE_TIMER__TIMER_

#include<chrono>
#include<iostream>

namespace simple_timer {

	// alias for a high resolution period
	using duration_type = std::chrono::high_resolution_clock::duration;

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
		typename = typename std::enable_if< (timer_type == 's' || timer_type == 'm' || timer_type == 'u' || timer_type == 'n')
		&& std::is_floating_point<precision>::value > >
		class timer {
		private:
			std::chrono::high_resolution_clock::time_point init; // when time begins
			duration_type duration; // how long

		public:
			/**
			Default constructor, will initialize init to current time and duration to 0
			*/
			timer() : init(std::chrono::high_resolution_clock::now()), duration() {}

			/**
			This function starts the timer
			*/
			void tick() {
				init = std::chrono::high_resolution_clock::now();
			}

			/**
			This function returns the proper symbol for the time type
			@return "s" for seconds, "ms" for milliseconds, "us" for microseconds, and "ns" for nanoseconds
			*/
			static constexpr const char* symbol();

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
				interval(const precision& _len) : len(_len) {}

				/**
				This allows for the intervals to be printed
				@param o an ostream
				@param measured the interval
				@return the stream
				*/
				friend std::ostream& operator<<(std::ostream& o, const interval& measured) {
					o << measured.len << timer<timer_type, precision>::symbol();
					return o;
				}
			};

			/**
			This function stops the timer
			@return a time interval from tick to tock
			*/
			interval tock() {
				duration = std::chrono::high_resolution_clock::now() - init; // calculate duration
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
	template<char timer_type, typename precision, typename unused>
	constexpr const char* timer<timer_type, precision, unused>::symbol() {
		// looks ugly to preserve C++11 support...
		return timer_type == 's' ? "s" : // s for seconds
			timer_type == 'm' ? "ms" :  // m for milliseconds
			timer_type == 'u' ? "us" : // u for microseconds
			timer_type == 'n' ? "ns" : // n for nanoseconds
			""; // never happens due to SFINAE
	}	
}

#endif





// get the file here: https://github.com/3k1m/cpp/blob/master/timing/Timer.h

#include <iostream>
#include <string>

// string in by value
void foo( std::string s ){
 std::cout << s[50] << ' ' << s.size() << '\n';   
}

// string by reference: MUST FASTER
void bar( const std::string& s ){
 std::cout << s[50] << ' ' << s.size() << '\n';   
}



int main()
{
  simple_timer::timer<'n'> timer;

  char c;
  std::cin >> c;
  
  std::string big_string(100000, c);
  
  timer.tick();
  foo(big_string);
  std::cout << timer.tock() << '\n'; // how many ns
  
  timer.tick();
  bar(big_string);
  std::cout << timer.tock(); // how many ns
  
  
  return 0;
}
