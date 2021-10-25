#include <iostream>
#include <algorithm>
#include <vector>


std::vector<int> get_primes(std::vector<int> nums){
    auto bad = nums.end();
    auto curr = nums.begin();
    
    while(curr != bad){ // still values to check if others are multiple of said value
        int val = *curr; // the value to remove multiples of 
        ++curr;
        bad = std::remove_if(curr, bad, [val](int x){ return x % val == 0;});
    }
    
    return {nums.begin(), bad};
}

int main()
{
  int num_max = 100;
  std::vector<int> nums(static_cast<size_t>(num_max-1));
  
  std::generate(nums.begin(), nums.end(),
    [n=2]() mutable {
      return n++;   
    }   );
    
  for(int i : nums){ std::cout << i << ' '; }
  std::cout << '\n';
  
  auto primes = get_primes(nums);
  
  for(int i : primes){ std::cout << i << ' '; }
  std::cout << '\n';
    
   
  


  return 0;
}
