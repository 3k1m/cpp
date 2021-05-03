#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

std::vector<int> primes(int up){
    if(up<2){
        return {};
    }
    const size_t num_items = up-1;
    
    std::vector<int> nums;
    nums.reserve(num_items);
    
    std::generate_n( std::back_inserter(nums), num_items,
      [n=2]() mutable {
          return n++;
      });
      
    // nums stores 2, 3, 4, ... 
    auto beg = begin(nums);
    auto end = std::end(nums);
    
    while(beg != end){ // still number to filter
    
        int factor = *beg++; // want to filter items past beg 
        
        // end represents beginning of range that "can be removed"
        end = std::remove_if(beg, end, [factor](int i)->bool{
            return i % factor == 0;
        });
    }
    
    return {begin(nums), beg};
    
}

int main()
{
    std::vector<int> v10 = primes(10);
    std::vector<int> v100 = primes(100);
    
    for(int i: v10){
        std::cout << i << '\n';
    }
    std::cout << "up to 10 there are " << v10.size() << '\n';
    
    for(int i: v100){
        std::cout << i << '\n';
    }
        std::cout << "up to 100 there are " << v100.size() << '\n';

    return 0;
}
