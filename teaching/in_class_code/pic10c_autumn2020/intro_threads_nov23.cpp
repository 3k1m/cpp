#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <chrono>
#include <vector>

void add(int *low, int *up, long long int* sum){
    *sum = std::accumulate(low, up, 0LL);
}

int main()
{
    std::cout << "approximately " << std::thread::hardware_concurrency() << 
      " threads are supported\n";
      
    constexpr size_t N = 10000000;
    
    std::vector<int> vec(N);
    int* const arr = vec.data();
    std::generate_n(arr, N, std::rand);
    
    // want to sum all the values... -- direct 
    
    auto curr = std::chrono::steady_clock::now();
    long long int sum1 = std::accumulate(arr, arr+N, 0LL);
    auto time1 = (std::chrono::steady_clock::now() - curr).count();
    std::cout << sum1 << '\n';
    
    
    // want to sum two halves separately...
    curr = std::chrono::steady_clock::now();
    long long int x1 = 0, x2 = 0; // sums of two halves 
    
    std::thread t1(add, arr, arr+N/2, &x1);
    std::thread t2(add, arr+N/2, arr+N, &x2);
    
    t1.join();
    t2.join();
    
    long long int tot = x1 + x2;
    auto time2 = (std::chrono::steady_clock::now() - curr).count();
    std::cout << tot << '\n';
    
    std::cout << "with 1 thread (default), it took " << time1 << " ticks\n";
    std::cout << "with 2 threads, it took " << time2 << " ticks\n";

    return 0;
}
