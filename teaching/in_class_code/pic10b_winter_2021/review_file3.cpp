#include<deque>
#include<list>
#include<iostream>

int main(){
    std::deque<int> d {1,2,3,4}; // like a vector, can grow on both ends, has []
    d.push_back(7);
    d.push_back(8);
    d.push_front(3);
    d.push_front(0);
    std::cout << d[2] << '\n'; // will be the 3rd element
    d.pop_front();
    d.pop_back();
    
    for(int i : d){ std::cout << i << ' '; }
    std::cout << '\n';
    
    std::list<double> L; // like deque, but no [], need iterators
    L.push_back(3.14);
    L.push_front(2.09);
    L.push_front(1.111);
    // L: 1.111 2.09 3.14
    auto it = std::end(L); // will point past the end
    --it; // will point to the 3.14
    
    L.insert(it, 7);
    
    for(double d : L){ std::cout << d << ' '; }
    std::cout << '\n';
    
    it = std::begin(L); // it points to the 1.111
    L.erase(it);
    
    for(double d : L){ std::cout << d << ' '; }
    std::cout << '\n';
    
    
    
    
    
    return 0;
    
}
