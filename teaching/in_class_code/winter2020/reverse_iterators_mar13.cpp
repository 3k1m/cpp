#include <iostream>
#include <string>

using namespace std;

int main()
{
  string msg("hello world");
  
  for(auto it=msg.begin(); it != msg.end(); ++it){
    cout << *it;   
  }
  cout << '\n';
  
  for(auto it=msg.rbegin(); it != msg.rend(); ++it){
    cout << *it;   
  }
  cout << '\n';
  
  return 0;
}
