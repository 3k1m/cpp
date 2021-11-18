#include<thread>
#include<chrono>
#include<iostream>
#include<algorithm>

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

constexpr size_t byte_root(size_t bytes){
  size_t b = 0;
  while(b*b < bytes){
    ++b;
  }
  return b;
}

int main(){

	constexpr size_t int_bytes = sizeof(int);	
	constexpr size_t bytes_per_Kb = 1024;
	constexpr size_t kB_in_cache = 64;
	constexpr size_t cache_bytes = kB_in_cache * bytes_per_Kb;
	constexpr size_t num_to_escape_L1 = cache_bytes/int_bytes;

	std::cout << "ints to surpass L1: " << num_to_escape_L1 << '\n';

	constexpr size_t dim_in_L1 = byte_root(num_to_escape_L1);
 
	constexpr size_t sizes[] = { dim_in_L1/8, dim_in_L1/4, dim_in_L1/2, dim_in_L1, 2*dim_in_L1, 4*dim_in_L1, 8*dim_in_L1  };
 
	for(size_t sz : sizes){

		std::cout << sz << ":\n";

 		std::unique_ptr<int[]> A{new int[sz*sz]()};
		std::unique_ptr<int[]> B{new int[sz*sz]()};
		
		float f = 0;
		constexpr float df = 0.025f;

		for (size_t i = 0; i < sz; ++i) {
			for (size_t j = 0; j < sz; ++j) {
				A[i*sz+j] = f;
				f+=df;
			}
		}

		for (size_t i = 0; i < sz; ++i) {
			for (size_t j = 0; j < sz; ++j) {
				B[i*sz+j] = f;
				f+=df;
			}
		}

		// compute the sum of all the columns

		std::unique_ptr<float[]> sum_fast(new float[sz]());
		std::unique_ptr<float[]> sum_slow(new float[sz]());		

		nano_timer timer;

		for(size_t i=0; i < sz; ++i){
			for(size_t j=0; j < sz;++j){ // local for j
				sum_fast[i] += A[i*sz+j];
			}
		}		

		double sum_fast_time = timer;
		timer();

		for (size_t j = 0; j < sz; ++j) {
			for (size_t i = 0; i < sz; ++i) { // not local
				sum_slow[i] += A[i*sz+j];
			}
		}			

		double sum_slow_time = timer;

		std::cout << "column sum times (slow/fast) in ns: " << sum_slow_time << ' ' << sum_fast_time << '\n';

		std::unique_ptr<int[]> AB_fast{new int[sz*sz]()};
		std::unique_ptr<int[]> AB_middle{new int[sz*sz]()};
		std::unique_ptr<int[]> AB_slow{new int[sz*sz]()};

		timer();

		for(size_t i=0; i < sz; ++i){
			for(size_t j=0; j < sz; ++j){
				for(size_t k=0; k < sz; ++k){ // local in k for A, not local for B, unchanging for AB
					AB_middle[i*sz+j] += A[i*sz+k]*B[k*sz+j];
				}
			}
		}

		double AB_middle_time = timer;
		timer();

		for(size_t k=0; k < sz; ++k){
			for(size_t j=0; j < sz; ++j){
				for(size_t i=0; i < sz; ++i){ // not local for AB or A, unchanging for B
					AB_slow[i*sz+j] += A[i*sz+k]*B[k*sz+j];
				}
			}
		}

		double AB_slow_time = timer;

		timer();
		for(size_t i=0; i < sz; ++i){
			for(size_t k=0; k < sz; ++k){
				for(size_t j=0; j < sz; ++j){ // local in j for AB and B, unchanging for A
					AB_fast[i*sz+j] += A[i*sz+k]*B[k*sz+j];
				}
			}
		}

		double AB_fast_time = timer;

		std::cout << "matrix multiplications (slow/middle/fast) in ns: " << AB_slow_time
			 << ' ' << AB_middle_time << ' ' << AB_fast_time << '\n';		

	}

	return 0;

}
