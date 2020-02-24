// Example program
#include <iostream>
#include <string>
#include <vector>

// should define template functions in .h files

// generic
// typename ~ T represents anything
template<typename T>
const T& maxxx(const T& a, const T& b){
 // a and b are REFERENCES to the outside variables
 // no copying done
 
 // save a copy in the return: return a REF to CONST    
 return (a < b) ? b : a;   
}

int maxx(int a, int b){
// (true/false) ? (value if true) : (value if false)    
    return (a < b) ? b : a;
// if(a < b){
//   return b;    
// }
// return a; 
}

double maxx(double a, double b){
    return (a < b) ? b : a;
}

template<typename S>
void print(const S& s){
 for(const auto& e : s){
  std::cout << e;   
 }
 std::cout << '\n';
}

int main()
{
  std::cout << maxx(3,4) << '\n';
  std::cout << maxx(3.99,4.06) << '\n';
  
  std::cout << maxxx(3,4) << '\n';
  std::cout << maxxx(3.99,4.06) << '\n';
  std::cout << maxxx(7ull, 4ull) << '\n';
  // ambiguos: should T be double or int?
  //std::cout << maxxx(5.3, 7)<< '\n';
  std::cout << maxxx<int>(5.3, 7) << '\n';
  std::cout << maxxx<double>(5.3, 7) << '\n';
  
  std::string a("A");
  std::string b("bee");
  
  std::cout << maxxx(a,b) << '\n';
  
  std::vector<char> v{'a', 'b', 'c'};
  std::string s("hello");
  int iarr[] = {5,10,8};
  
  print(v);
  print(s);
  print(iarr);
  print("string lit");
  
  
  return 0;
}
