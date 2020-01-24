#include<iostream> // C++ standard get < >
#include "Accumulator.h" // our own get " "

#include<string>

using namespace std;


int main() {

	// common error
	//Accumulator a();

	Accumulator a; // will start at 0

	Accumulator b(12); // starts at 12

	// add 5 and 10 to both and b
	a.add(5);
	a.add(10);

	b.add(5);
	b.add(10);

	// "add" and "get_total" are 
	// member functions and as such
	// are accessed with a .

	cout << "a total: " << a.get_total() << '\n';
	cout << "b total: " << b.get_total() << '\n';

	cin.get();

	return 0;
}
