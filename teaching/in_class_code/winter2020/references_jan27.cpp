#include <iostream>
#include <string>

int main() {
  int x = 9;
  int y = x;
  int& z = x;

  // references are lvalues
  int& a = z;

  // references must always be
  // initialized
  //int &b;

  std::cout << x << " " <<
    y << " " << z << '\n';

  z *= 3;

  std::cout << x << " " <<
    y << " " << z << '\n';

  a += 1;

  std::cout << x << " " <<
    y << " " << z << '\n';

  // error: cannot make & 
  // lvalue refernce to
  // 450, rvalue
  // int& w = 450;  

  // lvalue reference to const
  // can be made with an rvalue 
  const double& w = 4.111;

  // references and const...
  std::string s("XYZ");
  const std::string& t = s;

  s[0] = 'A';

  std::cout << s << " " << t <<
   '\n';

  //t[1] = 'B';  

  // if this were allowed...
  //std::string& u = t;
  // then we could
  //u[2] = 'R';

  const std::string& v = t;

  // q is a COPY of t
  // can change q w/o changing
  // t.
  std::string q = t;

  const double e = 2.718281;
  // double& f = e; // no!!
  const double& f = e;

  return 0;
}
