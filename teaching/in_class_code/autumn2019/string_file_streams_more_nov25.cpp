#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

template<typename T>
std::string to_string(const T& t){
	std::ostringstream oss; // stores nothing
	oss << t;
	return oss.str(); // get the string in oss
}

template<typename To>
To string_to( const std::string& input ) {
	To x; // make any value of To we want...
	std::istringstream iss(input); 
	iss >> x; // read from the string into x...
	return x;	
}

int main(){

	{ // local scope so can reuse fout 
		std::ofstream fout("file1.txt");
		fout << "123";
		fout.close();
	}
	
	std::ofstream fout("file1.txt");
	fout << "456";
	fout.close();

	
	// specify 'append' mode 
	fout.open("file1.txt", std::ios_base::app );
	// can't construct b/c fout already exists
	//	std::ofstream fout("file1.txt", std::ios_base::app );
	fout << "789";
	fout.close();
	
	double d = 3.14159;
	
	std::string d_as_string = to_string(d);
	
	std::cout << "length of string: " << d_as_string.size() << '\n';	
	
	// try to open a file that does not exist!!!
	std::ifstream fin("does_not_exist.txt");
	
	if(! fin ){ // file opening failed
		std::cout << "no file!\n";
	}
	else{
		std::cout << "file opened!\n";
	}

	fin.close();
	
	fin.open("nums.txt"); // open the file
	
	if(! fin ){ // file opening failed
		std::cout << "no file!\n";
	}
	else{
		int sum;
		int i;
		
		
		// fin >> i reads from fin into i
		// and returns fin!!!
		// if stream fails, fin ~ false, don't use i 
		// if stream succeeds, fin ~ true, use i 
		
		while( fin >> i ){
			sum += i;
		}
		
		std::cout << "The sum is: " << sum << '\n';		
	}
	
	// fin has failed!!!
	fin.clear();
	fin.close();	
	
	fin.open("lines.txt"); // open the file
	
	if(! fin ){ // file opening failed
		std::cout << "no file!\n";
	}
	else{
		
		std::cout << "lines.txt:\n";
		
		std::string line; // to represent a line in the file 
		
		while( !fin.eof() ){ // until we are at end of file 
			std::getline( fin, line );
			std::cout << line << '\n';		
		}		
	
	}
	
	double a = string_to<double>("1.1") + string_to<int>("7");
	
	std::cout << a << '\n';	

	return 0;
}	
