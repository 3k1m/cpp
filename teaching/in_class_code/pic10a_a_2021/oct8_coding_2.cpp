#include <iostream>
#include <string>

using namespace std;

int main()
{
    char c = 'a';
    
    // adds empty std::string to 'a'
    string s1 = string() + 'a';
    string s2(1,'t');
    
    string pic(10, c);
    
    cout << s1 << '\n' << s2 << '\n' << pic << '\n';

    return 0;
}
