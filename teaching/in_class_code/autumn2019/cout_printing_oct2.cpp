// Example program
#include <iostream>

using namespace std;

int main()
{
        
  cout << '\''; // character literal
  cout << "\nhi\n"; // string literal
  cout << 5; // int literal...
  cout  << 3*8 << "...\n";
  
  // endl ( std::endl ) gives us the same effect as a \n
  // but it can be less efficient
  
  cout << endl << endl << endl << "...";
  
  // cout  << 3*8 "...\n";  ERROR
  
  // character literal is ONE SINGLE character: a, !, 0, -, ...
  // string literal can be many charactrs "hello"
  
  return 0;
}
