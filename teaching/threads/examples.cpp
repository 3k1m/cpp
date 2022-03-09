/**
To use this file, also download the Timer.h file: https://github.com/3k1m/cpp/blob/master/timing/Timer.h
*/

#include<cstdlib>
#include<ctime>
#include<iostream>
#include<vector>
#include<thread>
#include<mutex>

#include "Timer.h"

/**
sums all consecutive sums over range
@param begin lower position
@param end past end position
@param res pointer to result to write to
*/
void busy_work(const int* begin, const int* end, long long* res);

/**
bad function, has a race condition
@param i an int to print 1000 times
*/
void data_race(int i);

/**
good function, uses mutex to fix race condition
@param i an int to print 1000 times
*/
void data_race_fixed(int i);

std::mutex THE_MUTEX;

int main() {
	std::srand(std::time(nullptr)); // seed

	// check how many threads (approximately) can be run concurrently:
	std::cout << "This implementation supports " << std::thread::hardware_concurrency() <<
		" concurrent threads.\n";

	/* FIRST PART OF DEMO: THREADING THE BUSY_WORK FUNCTION */
	
	constexpr int MAX = 10000; // max int we consider
	constexpr size_t BIG = 1000000; // elements in vector

	std::vector<int> v;
	v.reserve(BIG); // reserve enough space

	for (size_t i = 0; i < BIG; ++i) { // set all the values
		v.push_back(std::rand() % MAX);
	}

	int* const vfirst = &(v[0]); // the first element of v

	long long res1 = 0, res2 = 0; // to store results from the threads

	simple_timer::timer<'u'> tim; // timer class

	tim.tick(); // start timing

	std::thread t1(busy_work, vfirst, vfirst + BIG / 2, &res1); // first half
	std::thread t2(busy_work, vfirst + BIG / 2, vfirst + BIG, &res2); // second half

	t1.join();
	t2.join();

	long long thread_total = res1 + res2;

	auto thread_time = tim.tock(); // store how long it took

	long long no_thread_total = 0;

	tim.tick(); // start timing
	busy_work(vfirst, vfirst + BIG, &no_thread_total);

	auto no_thread_time = tim.tock(); // store how long it took

  // display results
	std::cout << "threads added up to " << thread_total << " and took " << thread_time << '\n';
	std::cout << "no threads added up to " << no_thread_total << " and took " << no_thread_time; 

	/* SECOND PART OF DEMO: DATA RACES */
	
	std::cout << "\nWith races:\n";

	std::thread race1(data_race, 1);
	std::thread race2(data_race, 2);

	race1.join();
	race2.join();
	
	std::cout << "\nNow without data races:\n";

	std::thread no_race1(data_race_fixed, 1);
	std::thread no_race2(data_race_fixed, 2);

	no_race1.join();
	no_race2.join();
	
	
	return 0;
}

/* definitions */

void busy_work(const int* begin, const int* end, long long* res) {
	long long total = 0; // local sum

	for (const int* p = begin; p != end; ++p) { // for every int
		for (int i = 0; i <= *p; ++i) { // add consecutive ints up to *p to total
			total += i;
		}
	}

	*res = total;
}

void data_race(int i) {
	for (int c = 1; c <= 1000; ++c) { // print a lot of i's
		std::cout << i;
	}
}

void data_race_fixed(int i) {
	THE_MUTEX.lock();
	for (int c = 1; c <= 1000; ++c) { // print a lot if i's
		std::cout << i;
	}
	THE_MUTEX.unlock();
}
