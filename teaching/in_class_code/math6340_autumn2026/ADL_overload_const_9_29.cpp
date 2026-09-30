#include<iostream>

// overloading on const
void foo(int *) { std::cout << 1; }
void foo(const int *) { std::cout << 2; }

void bar(int &) { std::cout << 3; }
void bar(const int &) { std::cout << 4; }


int main()
{
    int i = 0;
    const int j = 2;
    
    foo(&i);
    foo(&j);
    
    bar(i);
    bar(j);
    
    
    std::string name;
    std::cout << "\nEnter your name: ";
    
    // ADL : argument dependent lookup
    // since std::cin is part of namespace std, 
    // can find std::getline
    getline( std::cin, name );
    
    std::cout << name;

    return 0;
}
