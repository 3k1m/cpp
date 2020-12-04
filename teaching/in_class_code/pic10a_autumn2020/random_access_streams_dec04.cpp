#include<fstream>
#include<iostream>
#include<string>

int main(){

  std::ofstream fout("file2.txt");
  fout << "0123456789";
  fout.close();

  fout.open("file2.txt", std::ios_base::in | std::ios_base::ate );
  std::cout << fout.tellp() << '\n';
  fout.seekp(-2, std::ios::cur);
  fout << 'a';
  fout.close();

/*
  std::ifstream fin("file.txt");

  if( ! fin ) { // something went wrong
    std::cout << "invalid file name!";
    return -1;
  }

  std::string line; // line in the file
  //while( ! fin.eof() ) { // until we reach end of file
  //  std::getline(fin, line);
  //  std::cout << line << '\n';
  //}

  while( std::getline(fin, line) ){ // while stream can read a line...
    std::cout << line << '\n';
  }

  fin.close();  
*/

  return 0;
}
