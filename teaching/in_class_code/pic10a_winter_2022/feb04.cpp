#include <iostream>
#include <string>

using namespace std;

int main()
{
    int a = 42;
    
    int& ar = a; // ar is a reference to a: ar didn't exist yet so & makes it a reference 
    int* ap = &a; // ap points to a, and &a is the address: ap didn't exist yet, so * makes it a pointer
    // and a does exist so &a is its address 
    
    cout << a << '\n'; // a and ar are the same object 
    cout << ar << '\n';
    cout << ap << '\n'; // pointer on its own here is just the address 
    cout << *ap << '\n'; // dereference to get to the pointed to objet
    // ap exists so *ap is dereferencing to get the poitned to entity
    
    string s = "hello world, it is Friday!";
    string* sp = &s;
    
    cout << (*sp).substr(5) << '\n';
    cout << sp->substr(5) << '\n'; // operator arrow 
    
    int iarr[] = {2,4,6,8,10};
    cout << iarr << '\n';
    cout << *iarr << '\n'; // iarr points to the first entry 

    return 0;
}
