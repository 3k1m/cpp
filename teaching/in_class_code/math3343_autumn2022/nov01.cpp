#include <iostream>
#include <fstream>
#include <string>


int main()
{
  /*{
      int x;
      std::string s;
      std::cout << "Enter an int: ";
      std::cin >> x;
      std::cin.ignore();
      std::cout << "Enter a line: ";
      std::getline(std::cin, s);
      std::cout << x << ' ' << s << '\n';
  }*/
 
  std::cout << "Enter a list of numbers and when you are done, type any word."
    <<" I will tell you the sum of the numbers";
   
  double d;
  double tot = 0;
  //std::cin >> d; // expression reads into d and returns std::cin
  while(std::cin >> d){ // could work for any input stream, even file streams
      tot += d;
  }
  std::cout << "The total is: " << tot << '\n';
 
  // plain vanilla basics
  {
      int x;
      std::string s;
      std::ifstream fin{"myfile.txt"};
      fin >> x;
      fin.ignore();
      std::getline(fin, s);
      fin.close(); // sever ties with file
      std::ofstream fout("outputfile.txt");
      fout << x << ' ' << s << '\n';
  } // fout will automatically close before its destruction at closing }
 
 
  // bit safer
  {
      int x;
      std::string s;
      std::ifstream fin{"myfile2.txt"};
      if(fin){ // if stream fails to open file, it will be in a failed state
      // if stream has failed -> false within if/while/etc.
        fin >> x;
        if(!fin) { std::cout << "failed to read x\n"; }
        fin.ignore();
        std::getline(fin, s);
        if(!fin) { std::cout << "failed to read s\n"; }
        fin.close(); // sever ties with file
        std::ofstream fout("outputfile.txt");
        fout << x << ' ' << s << '\n';
      }
      else{
          std::cout << "could not find file\n";
      }
  } // fout will automatically close before its destruction at closing }
 
  //std::string s;
  //std::getline(std::cin, s); // expression sets s, but also returns std::cin
 
  {
      std::cout << "we will print what is in the file.\n";
      std::ifstream fin; // default constructor
      fin.open("lines.txt");
      std::string line;
      // getline reads a line from the file into line
      // if the reading was successful, returns fin -> true
      // when end of file is reached, reading will fail so fin -> false
      while( std::getline(fin, line)){
          std::cout << line << '\n';
      }
  } // stream will close here anyway...



    return 0;
}
