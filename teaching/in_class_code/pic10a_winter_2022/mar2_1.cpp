#include<iostream>
#include<vector>
#include<string>
#include<fstream>

int main() {

	std::vector v{ 1,2,3,4 };

	//std::ofstream fout("myFile.txt");

	//for (int i : v) {
	//	fout << i << '\n';
	//}

	//fout.close();

	std::ifstream fin("myFile.txt");

	std::string name;
	std::getline(fin, name);
	int year;
	fin >> year;

	fin.close();

	std::cout << name << ' ' << year << '\n';

	fin.open("myFile.txt");
	std::string word;
	fin >> word;
	std::cout << word << '\n';
	fin.close();



	return 0;
}
