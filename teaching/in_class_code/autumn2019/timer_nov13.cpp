#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// time accepts a time_t* argument
// nullptr is a pointer to null, works for any data type

int main()
{
    cout << "Press ENTER to start and stop timing. ";
    cin.get(); // starting
    time_t start = time(nullptr);
    cin.get(); // press enter again to stop
    time_t end = time(nullptr);
    
    cout << "The elapsed time was " << end - start << " sec.";
    return 0;
}
