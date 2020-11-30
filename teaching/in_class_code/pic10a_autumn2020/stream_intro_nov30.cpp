#include<fstream>
#include<iomanip>
#include<string>
#include<iostream>
#include<sstream>

int main() {
	// output file stream: can specify file to open
	std::ofstream fout("file.txt");

	fout << "hello world\n" << std::setprecision(1) << std::fixed <<
		0.9998 << '\n';

	fout.close();

	std::string first_line;
	double num;

	// input file stream, default then open
	std::ifstream fin;
	fin.open("file.txt");

	std::getline(fin, first_line);
	fin >> num;

	fin.close();

	std::cout << first_line << '\n';
	std::cout << num << '\n';

	std::string num_str = "123";

	// input string stream: construct from a string
	std::istringstream iss(num_str);
	int val;
	iss >> val;

	double pi = 3.14159;
	std::ostringstream oss; // output string stream, starts with empty buffer
	oss << pi; // oss' buffer stores 3.14159
	std::string pi_str = oss.str();




	return 0;
}
