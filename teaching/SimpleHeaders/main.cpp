#include "Functionalities.h"
#include "Writer.h"

int main(){
  // uses the Functionalities.h
  
  double x = 43.8, y = 19.7;
  std::cout << larger(x,y) << '\n';

  std::vector<double> ds{ 1.25, 3.8, 9.76, 0};
  print( "mean = ");
  print( mean(ds) );
  print('\n');

  // uses the Writer.h
  Writer w{"sample.txt"};

  std::cout << w.file_name() << " has " << w.line_count() << " lines\n";
  w.add_line("hello");
  w.add_line("world");
  std::cout << w.file_contents() << '\n';
}
