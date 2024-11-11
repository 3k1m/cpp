#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
    out << "[";
    for(int i : v){
        out << i << ' ';
    }
    return out << "]";
}

template<typename T>
void swap(T& x, T& y){
   T temp{x};
   x=y;
   y=temp;
}

template<typename T>
const T& Max(const T& a, const T& b){
    if(a<b){
        return b;
    }
    return a;
}

template<typename T>
T string_to(const std::string& s){
    T t;
    std::istringstream iss{s};
    iss >> t;
    return t;
}

/*
Write a function to_vec that will read the contents of an std::string of
values separated by spaces into a vector of arbitrary type. For example,
to_vec<int>("1 2 3"); should return an std::vector with values 1, 2, and 3.
*/

template<typename T>
std::vector<T> to_vec(const std::string& str){
    std::istringstream iss{str};
    std::vector<T> vec;
    T t;
    while(iss >> t){
        vec.push_back(t);
    }
    return vec;
}


int main()
{
    std::cout << to_vec<int>("4 5 8") << '\n';
    
    
    int p = 7, q = 9;
    swap(p,q);
    std::cout << p << ' ' << q << '\n';
    std::string s1{"dog"}, s2{"cat"};
    swap(s1,s2);
    std::cout << s1 << ' ' << s2 << '\n';
    
    std::cout << Max(8,3) << '\n';
    std::cout << Max(s1,s2) << '\n';
    std::cout << Max<int>(6, 9.8) << '\n';
    std::cout << Max<double>(6, 9.8) << '\n';
    
    std::string a{"600"};
    int i = string_to<int>(a);
    std::cout << i << '\n';
    
    return 0;
    
    
    
    
    std::cout<<"Hello World. Give me an int: ";
    int x;
    std::cin >> x;
    std::cout << "You entered: " << x << '\n';
    
    // file streams: to read from (input) or write to (output) a file
    
    std::cout << "I'm going to read from number.txt.\n";
    std::ifstream fin{"number.txt"};
    fin >> x;
    fin.close(); // we don't need this anymore, so close the file 
    std::cout << "The file stored: " << x << '\n';
    
    std::cout << "I'm going to write x to a file output.txt\n";
    std::ofstream fout{"output.txt"};
    fout << x;
    fout.close();
    
    // string streams: convert to (output) or read from (input) a string  
    std::string number{"108.6"};
    std::istringstream iss{number}; // iss stores "108.6"
    double d;
    iss >> d;
    std::cout << "The value of number is " << d << '\n';
    
    std::vector<int> v{1,-1,2,-2,3,-3};
    std::ostringstream oss;
    oss << v; // since std::ostringstream is an std::ostream (inherits from)
    std::string v_as_string = oss.str();
    std::cout << v_as_string << '\n';
    
    

    return 0;
}
