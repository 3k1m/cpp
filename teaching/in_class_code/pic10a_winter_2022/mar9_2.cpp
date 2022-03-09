#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <sstream>

/**
 * function allows sorting by absolute value 
 * @param x the first parameter
 * @param y the second paramter 
 * @return if |x| < |y|
 */
bool sort_abs_val(int x, int y){
    return x*x < y*y;
}


bool is_even(int i){
    return i % 2 == 0;
}

void print_int(int i){ std::cout << i << ' '; }

int main()
{
    std::vector<int> v{-10,-6,3,4,5};
    
    // usnga const_reverse_iterator
    for(auto it = v.crbegin(); it != v.crend(); ++it){
        std::cout << *it << '\n';
    }
    
    std::sort(std::begin(v), std::end(v), sort_abs_val);
    
    for(int i : v){
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    std::list L{1,2,3,4,5};
    
    auto it3 = std::find(L.begin(), L.end(), 3);
    if(it3 != L.end()){
        std::cout << "found " << *it3 << '\n';
    }
    
    auto third = L.begin();
    ++third;
    ++third; // points to the 3
    
    // in the find below, third is *Not* part of the search 
    auto it_foo = std::find(L.begin(), third, 3);
    if(it_foo != L.end() && it_foo != third){
        std::cout << *it_foo << '\n';
    }
    
    // 1, 2, 3, 4, 5
    auto find_even = std::find_if(L.begin(), L.end(), is_even);
    if(find_even != L.end()){
        std::cout << "found the even value " << *find_even << '\n';
    }
    
    std::for_each(L.begin(), L.end(), print_int);
    std::cout << '\n';
    
    
    std::istringstream iss("hello world ...");
    std::istream_iterator<std::string> it(iss), end;
    auto word = std::find(it, end, "world");
    if(word != end){
        std::cout << *word << '\n';
    }

    return 0;
}
