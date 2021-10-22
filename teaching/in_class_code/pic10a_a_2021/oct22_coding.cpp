#include<iostream>
#include<string>

/*
1. The code below is an attempt to print an std::string in reverse but there are logical errors. 
Using a debugger, identify the problem.

2. Write code that prints rows of asterisks, increasing by length one each time, 
which stops printing asterisks after N asterisks are printed.

int N = 13;

// code

desired output:

*
**
***
****
***

(note how the last row only has 3, not 5 because at that point, 13 *'s have been printed)

*/

int main() {
	/*std::string s("Hello"); 

	for (size_t i = s.size() - 1; i != -1; --i) {
		std::cout << s[i];
	}*/

	int N = 13;

	int num_asts = 0; // how many asterisks

	int row = 1; // the row number, each row has at most this many *'s

  /* THE LOGIC HERE WAS NOT COMPLETED IN CLASS -- THERE IS STILL A SMALL BUG */
  
	while (num_asts < N) { // need to print N
		num_asts = num_asts + row;
		if (num_asts > N) {
			// some care is needed 
			std::cout << std::string(static_cast<size_t>(num_asts-N), '*') << '\n';
		}
		else { // enough space to print
			std::cout << std::string(static_cast<size_t>(row), '*') << '\n';
		}

		++row;
	}

	// i is the number of asterisks
	//for (int i = 0; i < N; ++i) {

	//}

	return 0;
}
