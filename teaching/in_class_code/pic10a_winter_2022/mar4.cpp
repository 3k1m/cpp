#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "I will tell you the sum of numbers. Enter NO when no more numbers are needed.\n";
    
    int sum = 0;
    int temp;
    while( cin >> temp){
        sum += temp;
    }
    cout << "The sum is: " << sum;
    
    // cin is failed!
    cin.clear(); // now not failed 
    
    // have some bad characters in buffer -- need to get past them 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Let's do this again but with multiplication!\n";
    
    int prod = 1;
    while( cin >> temp){
        prod *= temp;
    }
    cout << "The product is: " << prod;
    

    return 0;
}
