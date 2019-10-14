#include <iostream>

using namespace std;

int main()
{
    // g is of type: const double
    // it cannot be changed in error
    // makes code more robust b/c we can get
    // compiler errors rather than logic errors
    const double g = 9.8; // gravity: m/s^2 
    
    // g above is an Lvalue (has a name)
    
    cout << "How long does the object fall in s? ";
    
    //time is Lvalue (has a name)
    double time = 0;
    // cin >> g; // ERROR
    cin >> time; // read in the time
    
    // right hand side here is an Rvalue
    // distance is Lvalue (has a name)
    double distance = 0.5*g*time*time;
    
    cout << "It fell: " << distance << "m.";

    return 0;
}
