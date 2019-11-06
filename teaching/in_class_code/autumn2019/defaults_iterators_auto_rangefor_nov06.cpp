// Example program
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <set>

// default arguments
void def(int a, int b = 7, double c = 9.38);
// specify default values in declaration

double max_double(double a, double b){
 if(a < b){
  return b;   
 }
 return a;
}

double max_double2(double a, double b){
    // ternary conditional operator
    // (something that evaluates to a bool) ? ( value if true ) : (value if false)
  return ( a < b) ? b : a;
}


int main()
{
    // doing the maxs
    std::cout << max_double(3.3, 6.6) << '\n';
    std::cout << max_double2(3.3, 6.6) << '\n';
    
    
    int a[5] = {2, 4, 6, 8, 10};
    
    int* ia = a; // points to first element
    ++ia; // points to second element
    *ia = 40;
    std::cout << a[1] << '\n';
    

    std::cout << *a << '\n';
    // pointer arithmetic: +4 shifts 4 from first
    // element of array
    std::cout << *(a+4) << '\n';

        std::cout << "---\n";
    
    std::vector<int> v {2, 4, 6, 8, 10};
    
    // std::vector<int>::iterator is a data type
    // a generalized pointer for a vector
    std::vector<int>::iterator first = std::begin(v);
    
    std::vector<int>::iterator last = first + 4;
    *last = 100; // modify the last element
    
    // std::begin is a function that returns
    // an iterator to the first element of the container
    
    std::cout << *first << '\n';
    std::cout << *(first+4) << '\n';
    
    // let's print out the vector (or array)
    std::cout << "vector:\n";
    
    // auto: automatically determines the type of the
    // right-hand side of initialization/definition
    
    // end: returns an iterator/pointer just PAST the end
    
    for( auto itr = std::begin(v); itr != std::end(v); ++itr){
      std::cout << *itr << ' ';   
    }
    std::cout << '\n';
    
    for( auto itr = std::begin(a); itr != std::end(a); ++itr){
      std::cout << *itr << ' ';   
    }
    std::cout << '\n';
    
    std::set<int> s{ 2, 4, 6, 800, 10};
    // tempting... but FAILS - NO []
    /*for(size_t i=0; i < s.size(); ++i){
     std::cout << s[i] << ' ';   
    } */
    
      // std::set<int>::iterator
    for( auto itr = std::begin(s); itr != std::end(s); ++itr){
      std::cout << *itr << ' ';   
    }
    std::cout << '\n';
    
    // intermediate step...
    
    for( auto itr = std::begin(s); itr != std::end(s); ++itr){
        int i = *itr;
      std::cout << i << ' ';   
    }
    std::cout << '\n';
        
    // Rewrite with range based for loop...
    
    for(int i : s){ // simple, elegant, range-based for loop
       std::cout << i << ' ';   
    }
    std::cout << '\n';
    
    std::vector<std::string> vstrings {"hello", " ", "world\n"};
    
    // efficient and robust
    // whereas for ( std::string s : vstrings ) is not
    for(const std::string& s : vstrings){
     std::cout << s;   
    }
    
    // same as ....
    
    for( auto itr = std::begin(vstrings); itr != std::end(vstrings); ++itr){
       // std::string s = *itr;  // inefficient
       const std::string& s = *itr;
       std::cout << s;   
    }
    std::cout << '\n';
    
    // can even... - very generic. works FOR ALL containers
    for(const auto& s : vstrings){
     std::cout << s;   
    }
    
    for(const auto& i : a){
     std::cout << i << ' ';   
    }
    std::cout << '\n';
    
    // std::begin, std::end as FREE functions work on arrays (as we saw)
    
    // std::vector, std::set have member functions .begin, .end
    auto it2 = v.begin() + 2;
    
    
    
    
    // iterators allow for general traversals of all containers!
    
    
    // default args 
    /*def(1, 22, 3.14);
    def(4, 99);
    def(5); */
    
  return 0;
}

// but don't repeat argument values in definition
void def(int a, int b, double c){
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
    std::cout << "c: " << c << '\n';
}
