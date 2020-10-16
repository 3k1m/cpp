#include<iostream>
#include<string>

using namespace std;

int main() {
	int x = 4, y = 3, z = 2;
	cin >> x >> y >> z;
	cout << x << ' ' << y << ' ' << z << '\n';


	/*cout << "enter a number: ";
	int num;
	cin >> num; // there will be a '\n' left in the user input buffer
	cin.ignore();
	//char c = cin.get();
	cout << "you entered: " << num << '\n';
	//cout << "c is " << c << '\n';

	string sentence;
	cout << "enter a message: ";
	getline(cin, sentence);
	cout << "your sentence is: " << sentence << '\n';
	
//	std::string s1, s2;
//	std::cin >> s1 >> s2;   
//	std::cout << s1 << ' ' << s2;
	
	
	/*cout << "enter two numbers ";
	int num1;
	double num2;
	char c;
	cin >> num1 >> num2 >> c; // 5.933

	cout << num1 << ' ' << num2 << ' ' << c;*/

	return 0;
}
