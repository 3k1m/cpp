#include<iostream>
#include<vector>
#include<string>
#include<set>

int main(){
    
    std::vector<double> vec{1.1, 2.2, 4.4, 8.8};
    
    std::vector<double>::iterator it = std::begin(vec);
    
    std::cout << *it << '\n';
    
    for(auto it = std::begin(vec);
      it != std::end(vec); ++it){
          std::cout << *it << ' ';
      }
      std::cout << '\n';
    
    
    // print set values easily with iterators, same syntax as vectors 
    std::set<double> vals{8.8, 4.4, 2.2, 1.1};
    
    for(auto it = std::begin(vals);
      it != std::end(vals); ++it){
          std::cout << *it << ' ';
      }
      std::cout << '\n';
      
      // no [] for sets!
    //for(size_t i=0; i < vals.size();++i){
    //    std::cout << vals[i] << ' ';
    //}
    
    std::vector<double> vec2{1.1, 2.2, 4.4, 8.8};
    
    // want to insert the value 0.5 before 4.4
    vec2.insert(vec2.begin()+2, 0.5);
    
    for(auto it = std::begin(vec2);
      it != std::end(vec2); ++it){
          std::cout << *it << ' ';
      }
      std::cout << '\n';
      
    // want to remove the value 4.4 at index 3, iterator position begin(vec2)+3 
    
    vec2.erase(vec2.begin()+3);
    
    for(auto it = std::begin(vec2);
      it != std::end(vec2); ++it){
          std::cout << *it << ' ';
      }
      std::cout << '\n';
    
    
    return 0;
}
