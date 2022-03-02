#include<sstream>
#include <iostream>
#include<string>
#include <iomanip>
#include <vector>
#include <fstream>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
  for(int i : v){
    out << i << ' ';
  }
  return out;
}

int main(){

  std::ofstream fout1("myfile.txt", std::ios_base::app);
  fout1 << "hi";
  fout1.close();

  // ostringstream: make a string
  std::ostringstream oss; // ""
  int x = 42;
  double pi = 3.14159;
  
  oss << x << ' ' << std::setprecision(2) << std::fixed <<
	pi << '\n';

  // to access the string within the ostringstream
  // use .str
  std::string rep = oss.str();
  std::cout << rep;

  std::string string_int = "553";
  //int x = string_int;
  int y = std::stoi(string_int); // works...

  std::istringstream iss(string_int); // so "553"
  int z;
  iss >> z; // so z == 553
  std::cout << y << ' ' << z << '\n';

  std::vector<int> v{2,4,6,8};
  std::ofstream fout("file.dat");
  fout << v;
  fout.close();

  return 0;
}
