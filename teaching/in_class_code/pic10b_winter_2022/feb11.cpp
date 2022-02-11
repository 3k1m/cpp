#include <iostream>
#include <vector>


// location = position within vector whose value we want to set 
void print_perms(std::vector<int>& nums, size_t location = 0){
    // want to go one location at at a time and 
    // give every number an opportunity to be placed there 
    // as we place a value, want to move to the next position and give 
    // all remaining unplaced numbers a chance to be there ...
    const size_t sz = nums.size();
    
    // BASE CASE 
    if(location==sz){ // so all locations are filled 
        for(int i : nums) { std::cout << i << ' '; }
        std::cout << '\n';
        return;
    }
    
    
    // i tracks the positions of values that should be given a placement 
    // at location 
    for(size_t i=location; i < sz; ++i){
        std::swap(nums[location], nums[i]); // so value at i is now at location 
        print_perms(nums, location+1); // place values right of location 
        std::swap(nums[location], nums[i]); // clean up: 
    }
    
}


int main()
{
    std::vector v{1,2,3,4};
    print_perms(v); // print all 6 orderings of 1,2,3 

    return 0;
}
