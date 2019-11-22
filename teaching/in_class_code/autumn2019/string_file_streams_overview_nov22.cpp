#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>

using namespace std;

struct X{
	X() : i(0) {}
	int i;
};

ostream& operator<<(ostream& out, const X& x){
	out << "X: " << x.i;
	return out;
}

int main(){
	
	srand(time(nullptr));

	cout << "Hello World!\n";	
	
	// writing to a file 
	ofstream fout("foo.txt");
	fout << "Hello World!\n";
	fout.close(); // close after use
	
	ifstream fin("num.txt");
	int num1, num2;
	fin >> num1 >> num2;
	fin.close(); // close after use 
	
	cout << "The numbers are: " << num1 << ' ' << num2 << '\n';
	
	string init = "Foo Bar\n123\n";	
	istringstream sin(init); // input string stream, initially storing init
	
	string s; int x;
	getline(sin, s);
	sin >> x; // extract a NUMBER out of a string...
	
	cout << "s: " << s << '\n' << "x: " << x << '\n';
	
	// want a random int N
	// then write to a file fileN.txt where N is just the int directly

	int N = rand(); // want N to become a string 
	
	ostringstream sout; // an output string stream 
	
	// pushes the value of N into an internal string stored by N 
	sout << "file" << N << ".txt"; 
	cout << "file" << N << ".txt\n";
	
	string file_name = sout.str(); // str returns the string being stored 
	
	fout.open(file_name); // now open with fileN.txt 
	
	X y;
	
	fout << y << '\n';
	
	fout.close();
	

	return 0;
}	
