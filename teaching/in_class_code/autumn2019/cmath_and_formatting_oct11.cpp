#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> // allows some formatting

using namespace std;

int main()
{
    // basic math...    
  double pi = 3.14159265358979;
  
  cout << sin(pi/2) << '\n';
  cout << cos(pi/2) << '\n';
  cout << min( sin(pi/2), cos(pi/2) ) << '\n';
  
  double one = sin(pi/2);
  
  string one_as_string = to_string(one);
  
  cout << one_as_string + "!\n";
  
  string x = "3.14";  
  double x_as_double = stod(x);  
  cout << x_as_double << '\n';
  
  // manipulators
  
  double fav_num = sqrt(2)/100;
  
  cout << "default\n";
  cout << fav_num << '\n';
  
  // default level of precsion for cout
  int default_precision = cout.precision();
  
  // fixed
  cout << "fixed:\n";
  cout << fixed; // fixed format
  cout << setprecision(10) << fav_num << '\n';
  cout << setprecision(1) << fav_num << '\n';
  
// scientific
  cout << "scientific:\n";
  cout << scientific; // scientific notation
  cout << setprecision(10) << fav_num << '\n';
  cout << setprecision(1) << fav_num << '\n';
  
  // go back...
  cout << "try to go back...\n";
  cout << fav_num << '\n';
  cout << setprecision(default_precision);
  cout << fav_num << '\n';
  
  // should work!
  //cout << defaultfloat;
  cout.unsetf(ios_base::floatfield);
  
  cout << fav_num << '\n';
  
  // padding
  cout << "padding stuff\n";
  cout << setw(20) << fav_num << '\n';
  
  // extra space is filled with *'s
  cout << setfill('*');
  
  // make the printout have a width of 20
  // output is right justified by default
  cout << setw(20) << fav_num << '\n';
  
  // notice padding stays the same
  cout << left; // now make outputs left justified
  cout << setw(20) << fav_num << '\n';
  
  // setw only applies to the next output
  cout << fav_num << '\n';
  
  cout << setfill(' '); // resets the fill


  return 0;
}
