#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
string to_string_(const T& t){
  ostringstream oss;
  oss << t;
  return oss.str();
}

int main()
{
 int x = 10, y = 20;
 cout << to_string_(x) + to_string_(y) << '\n';
 
 istringstream iss("579");
 
 //char c = iss.get();
 char c = iss.peek();
 cout << c << '\n';
 int i;
 iss >> i;
 cout << i << '\n';
 
 cout << "enter a number: ";
 int num;
 cin.ignore(300,'2'); 
 cin >> num; // enter something like 111253
 
 cout << "You entered: " << num;
 
 
 
 
 
 
 return 0;
 
 
}
