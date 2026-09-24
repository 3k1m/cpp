#include "Nice.h"

int main()
{
    nice::print(1,2,3,"Hello World");
    
    int x, y;
    nice::read_vars(x,y);
    
    nice::print(x,y);

    return 0;
}
