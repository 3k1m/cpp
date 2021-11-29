#include<chrono>
#include<thread>
#include<mutex>
#include<vector>
#include<atomic>
#include<iostream>
#include<numeric>

std::mutex THE_MUTEX;

class nano_timer {
	std::chrono::time_point<std::chrono::steady_clock> start;
public:
	nano_timer() : start(std::chrono::steady_clock::now()) {}

	operator double() const {
		return std::chrono::duration<double, std::nano>{
			std::chrono::steady_clock::now() - start}.count();
	}

	void operator()() {
		start = std::chrono::steady_clock::now();
	}
};



void race_fun(unsigned& x, unsigned times) {
	unsigned a = 1;

	for (unsigned i = 0; i < times; ++i) {
		x += a;
	}
}

void atomic_fun(std::atomic<unsigned>& x, unsigned times) {
	unsigned a = 1;

	for (unsigned i = 0; i < times; ++i) {
		x += a;
	}
}

void better_atomic_fun(std::atomic<unsigned>& x, unsigned times) {
	unsigned a = 1;
	unsigned tot = 0;

	for (unsigned i = 0; i < times; ++i) {
		tot += a;
	}

	x += tot;
}

void mutex_fun(unsigned& x, unsigned times) {
	unsigned a = 1;
	unsigned tot = 0;

	for (unsigned i = 0; i < times; ++i) {
		tot += a;
	}

	std::lock_guard L{ THE_MUTEX };
	x += tot;
}


void adjacent_fun(unsigned* x, unsigned times) {
	unsigned a = 1;

	for (unsigned i = 0; i < times; ++i) {
		*x += a;
	}
}

struct alignas(std::hardware_destructive_interference_size) aligner {
	unsigned int v = 0;
	operator unsigned int() const { return v; }
};

void aligner_fun(aligner* x, unsigned times) {
	unsigned a = 1;

	for (unsigned i = 0; i < times; ++i) {
		x->v += a;
	}
}

int main() {
	constexpr unsigned num_threads = 4;
	constexpr unsigned times = 100000000u;

	// with races
	unsigned a1 = 0;
	std::vector<std::thread> race_vec;
	race_vec.reserve(num_threads);

	nano_timer timer;

	for (size_t i = 0; i < num_threads; ++i) {
		race_vec.emplace_back([&]() { race_fun(std::ref(a1), times); });
	}

	for (auto& t : race_vec) {
		t.join();
	}

	double time_race = timer;

	// with atomic
	std::atomic<unsigned> a2 = 0;
	std::vector<std::thread> atomic_vec;
	atomic_vec.reserve(num_threads);

	timer();

	for (size_t i = 0; i < num_threads; ++i) {
		atomic_vec.emplace_back([&]() { atomic_fun(std::ref(a2), times); });
	}

	for (auto& t : atomic_vec) {
		t.join();
	}

	double time_atomic = timer;

	// with smart atomic
	std::atomic<unsigned> a3 = 0;
	std::vector<std::thread> better_atomic_vec;
	better_atomic_vec.reserve(num_threads);

	timer();

	for (size_t i = 0; i < num_threads; ++i) {
		better_atomic_vec.emplace_back([&]() { better_atomic_fun(std::ref(a3), times); });
	}

	for (auto& t : better_atomic_vec) {
		t.join();
	}

	double time_better_atomic = timer;

	// with mutex 
	unsigned a4 = 0;
	std::vector<std::thread> mutex_vec;
	mutex_vec.reserve(num_threads);

	timer();

	for (size_t i = 0; i < num_threads; ++i) {
		mutex_vec.emplace_back([&]() { mutex_fun(std::ref(a4), times); });
	}

	for (auto& t : mutex_vec) {
		t.join();
	}

	double time_mutex = timer;

	// all adjacent
	unsigned a5[num_threads]{};
	std::vector<std::thread> adjacent_vec;
	adjacent_vec.reserve(num_threads);

	timer();

	for (size_t i = 0; i < num_threads; ++i) {
		adjacent_vec.emplace_back([&a5, i]() { adjacent_fun(a5 + i, times); });
	}

	for (auto& t : adjacent_vec) {
		t.join();
	}

	double time_adjacent = timer;


	// aligned
	aligner a6[num_threads]{};
	std::vector<std::thread> aligner_vec;
	aligner_vec.reserve(num_threads);

	timer();

	for (size_t i = 0; i < num_threads; ++i) {
		aligner_vec.emplace_back([&a6, i]() { aligner_fun(a6 + i, times); });
	}

	for (auto& t : aligner_vec) {
		t.join();
	}

	double time_aligner = timer;

	// no threads
	unsigned a7 = 0;
	race_fun(a7, num_threads * times);

	double time_no_threads = timer;

	std::cout << "race time: " << time_race << " ns\n";
	std::cout << "race a: " << a1 << '\n';
	std::cout << "atomic time: " << time_atomic << " ns\n";
	std::cout << "atomic a: " << a2 << '\n';
	std::cout << "better atomic time: " << time_better_atomic << " ns\n";
	std::cout << "better atomic a: " << a3 << '\n';
	std::cout << "mutex time: " << time_mutex << " ns\n";
	std::cout << "mutex a: " << a4 << '\n';
	std::cout << "adjacent time: " << time_adjacent << " ns\n";
	std::cout << "adjacent a: " << std::accumulate(std::begin(a5), std::end(a5), 0u) << '\n';
	std::cout << "aligner time: " << time_aligner << " ns\n";
	std::cout << "aligner a: " << std::accumulate(std::begin(a6), std::end(a6), 0u) << '\n';
	std::cout << "no_threads time: " << time_no_threads << " ns\n";
	std::cout << "no_threads a: " << a7 << '\n';


	return 0;


}
