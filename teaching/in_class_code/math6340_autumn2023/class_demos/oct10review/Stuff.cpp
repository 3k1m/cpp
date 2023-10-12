#include "Stuff.h"

#include <iostream>

int add(int a, int b) { return a+b; }

course::course(const std::string& _name, int _hour) : 
  name(_name), hour(_hour) {}
  
const std::string& course::get_name() const {
    return name;
}

int course::get_hour() const {
    return hour;
}


void print_vec(const std::vector<int>& v, size_t len){
    for(size_t i=0, sz = v.size(); i < sz and i < len; ++i){
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
    /*for(int i : v){
        std::cout << i << ' ';
    }
    std::cout << '\n'; */
}
