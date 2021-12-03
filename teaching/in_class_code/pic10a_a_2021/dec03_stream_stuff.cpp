#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<set>
#include<algorithm>

int main() {
	std::ofstream fout("myfile.txt");
	fout << "hello world cat dog computer \n\ndog mouse \tairplane cat cat cat!\n";
	fout.close();
	std::set<std::string> s;
	std::string temp;
	std::ifstream fin("myfile.txt");
	while (fin >> temp) {
		std::cout << temp << '\n';
		s.insert(temp);
	}
	fin.close();

	std::cout << "The words in the set are: ";
	for (const auto& a : s) {
		std::cout << a << ' ';
	}
	std::cout << '\n';

	bool more_user_input = true;

	while (more_user_input) {
		std::cout << "Enter a word to look for in the file: ";
		std::string word;
		std::cin >> word;

		// find will return an iterator to the word if found 
		// or past the end if not 

		// version 1
		//auto it = std::find(s.begin(), s.end(), word);
		//bool found = (it != s.end());

		auto it = s.find(word);
		bool found = (it != s.end());

		if (found) { // word was found in the file
			std::cout << "word found in the file\n";
		}
		else { // other case word was not
			std::cout << "word not found in the file\n";
		}

		std::cout << "more lookups? ";
		char c = 'y';
		std::cin >> c;
		if (c == 'n') {
			more_user_input = false;
		}
	}
	
	//int temp2;
	//while (std::cin >> temp2) {
	//	std::cout << temp2 << '\n';
	//}

	std::ostringstream oss;
	oss << "hello" << " world" << '!' << '\n';
	std::string oss_storage = oss.str();
	std::cout << oss_storage << '\n';

	std::string myNum = "42";
	std::istringstream iss(myNum);
	int num;
	iss >> num;
	std::cout << num << '\n';

	std::cout << "Enter name [first and last] and weight [lbs]: ";
	std::string line;
	std::getline(std::cin, line);
	std::istringstream user_stream(line);
	std::string first, last;
	double weight;
	user_stream >> first >> last >> weight;
	std::cout << "First name: " << first << ", last name: " << last <<
		", weight: " << weight << '\n';




	return 0;
}
