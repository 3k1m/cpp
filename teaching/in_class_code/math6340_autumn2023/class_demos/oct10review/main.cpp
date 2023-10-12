#include <iostream>
#include "Stuff.h"

int main()
{
    std::cout << add(3,4) << '\n';
    
    course math{"Math 6340", 20};
    
    std::cout << math.get_name() << " happens at " << math.get_hour() << '\n';
    
    std::vector w{1,2,3,4,5};
    print_vec(w);
    
    print_vec(w, 3); // 1 2 3 -- only print indices 0, 1, 2 

    return 0;
}
