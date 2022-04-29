#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <sstream>

// extract all the primes from nums which 
// is an inclusive range of ints starting at 2 
std::vector<int> primes(std::vector<int> nums){
    auto curr = nums.begin(), end = nums.end();
    
    // still values to search 
    while(curr != end){
        int val = *curr;
        
        // end points to beginning of "bad" numbers
        end = std::remove_if(curr+1,end,
        [val](int j){ return j % val == 0;});
        ++curr;
    }
    
    return {nums.begin(), end};
    
}


int main()
{
    constexpr size_t rng = 100;
    
   std::vector<int> nums;
   nums.resize(rng);
   // starting at going to 101
   std::iota(nums.begin(), nums.end(), 2);
   
   auto prime_nums = primes(nums);
   
   //for(int i : prime_nums){
//       std::cout << i << '\n';
  // }
   
   //std::ostream_iterator<int> o{std::cout, "\n"};
   std::copy(prime_nums.begin(), prime_nums.end(), 
     std::ostream_iterator<int>{std::cout, "\n"});
     
        
    std::istringstream iss{"hello world it is firday"};
    std::istream_iterator<std::string> i(iss), end;
    
    //while(i != end){
    //    std::cout << *i++;
    //}
    
    auto world = std::find(i,end,"world");
    std::cout << *world << '\n';
   

    return 0;
}
