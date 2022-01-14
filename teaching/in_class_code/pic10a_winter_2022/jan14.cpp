
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int year = 0;
    cout << "What year is it? ";
    cin >> year;
    cout << "The year is: " << year << '\n';
    
    cin.ignore(); // ignore 1 char from the buffer: \n
    
    cout << "Enter your name: ";
    string name;
    //cin >> name;
    getline(cin, name);
    cout << "Your name is " << name << '\n';
    
    /*double d = 7.36;
    double e = d+1;
    char x = 'x';
    
    cin >> d >> x;
    
    cout << d << ' ' << x << '\n'; */

    return 0;
}
