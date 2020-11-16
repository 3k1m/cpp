#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

int main(){
    
    std::vector<double> vec{1.1, 2.2, 40.4444, 19.8};
    
    for(size_t i=0; i < vec.size(); ++i){
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
    
    for(auto it = std::begin(vec); it != std::end(vec); ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    
    for(double d : vec){ // range based for-loop
        std::cout << d << ' ';
    }
    std::cout << '\n';
    
    // the loop above (roughly) translates to:
    auto end = std::end(vec);
    for(auto it=std::begin(vec); it != end; ++it){ 
        double d = *it;
        std::cout << d << ' ';
    }
    std::cout << '\n';
    
    // wish to add 1 to all values in vec 
    for(auto& d : vec){ // range based for-loop
        ++d;
    }
    std::cout << "after adding 1...\n";
    for(double d : vec){ // range based for-loop
        std::cout << d << ' ';
    }
    std::cout << '\n';
    
    std::vector<std::string> vec2{"hello", "world", "apple", "dog", "mouse", "aaaah"};
    
    for(const auto& s : vec2){ // range based for-loop
        std::cout << s << ' ';
    }
    std::cout << '\n';
    
    // sorts the vector from positions at the beginning
    // up to but *not including* the past-the-end
    std::sort(vec2.begin(), vec2.end());
    
    // if vec2.end()-1 --- would not sort the "aaah"
    
    for(const auto& s : vec2){ // range based for-loop
        std::cout << s << ' ';
    }
    std::cout << '\n';
    
    return 0;
}













