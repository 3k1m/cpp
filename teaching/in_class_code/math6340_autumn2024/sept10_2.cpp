#include <iostream>
#include <vector>
#include <string>

#include "Nice.h"

auto main() -> int
{
    // >> : does one reading into a variable 
    // getline : extract a line of text ...
    // get: member function, returns the int value of the next char in the buffer and moves forward
    
    std::cout << "enter two numbers: ";
    int a;
    double b;
    std::cin >> a >> b;
    std::cout << a << ' ' << b << '\n';
    
    /* int new_line = static_cast<int>('\n');
    std::cout << "new line has value: " << new_line << '\n';
    
    std::cout << "Hello, what class is this? ";
    std::string the_class;
    std::getline(std::cin, the_class);
    std::cout << "You are in: " << the_class << '\n';
    
    int i;
    std::cout << "Give me an integer: ";
    std::cin >> i;
    std::cout << "You entered: " << i << '\n';
    
    double x, y;
    std::cout << "Enter two real numbers: ";
    std::cin >> x >> y;
    std::cout << "Values are: " << x << ' ' << y << '\n';
    
    std::cout << "Hello, what class is this again? ";
    std::cin >> the_class;
    std::cout << "You are in: " << the_class << '\n';
    
    int discard;
    std::cin >> discard;
    std::cout << discard << '\n';
    
    // after >>, there is usually a newline character in the buffer
    // this can be extracted with a std::cin.get()
    // or std::cin.ignore()
    std::cout << "int value of next char in buffer: " << std::cin.get() << '\n';
    
    std::cout << "What is the meaning of life? ";
    std::string meaning;
    std::getline(std::cin, meaning);
    std::cout << "The meaning of life is: " << meaning << '\n';
    
    int num1, num2;
    nice::read_vars(num1,num2);
    nice::print("their sum is", num1+num2);
    std::string s;
    nice::print("say something");
    std::getline(std::cin, s);
    std::cout << s << '\n'; */

    return 0;
}
