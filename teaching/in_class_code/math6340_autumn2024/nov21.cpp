/*
* (C1) 
 * - Write a sum_unique function that will add up all the unique values in an std::vector<double>
 * 
 * - Now modify this so now it can add up all the values in any std::vector type 
*/

#include<vector>
#include<set>
#include<numeric>
#include<iostream>
#include<string>

double sum_unique1(const std::vector<double>& vec){
    std::set<double> myset;
    
    for(double d : vec){
        myset.insert(d);
    }
    
    return std::accumulate(myset.begin(), myset.end(), 0.0);
}

template<typename T>
T sum_unique2(const std::vector<T>& vec){
    std::set<T> myset;
    
    for(const T& t : vec){
        myset.insert(t);
    }
    
    //return std::accumulate(myset.begin(), myset.end(), static_cast<T>(0));
    return std::accumulate(myset.begin(), myset.end(), T{});
}

 //Determine the printouts or if there is a compiler error. Explain.
 
 void foo(int,bool) { std::cout << 0 << '\n'; }
  
 void bar(int,float,long double) { std::cout << 1  << '\n'; }
 void bar(double,double,int) { std::cout << 2 << '\n'; }
 
 void baz(int,float,double) { std::cout << 3 << '\n'; }
 void baz(double,double,int) { std::cout << 4 << '\n'; }

int main(){
    
     foo(false,19); 
     // false -> promoted to int (0)
     // 19 -> converted to bool (true)
     // print 0 
     
     // 6.5 -> int conversion, 6.5->double exact: #2 wins 
     // 8 -> float conversion, 8->double conversion: tie 
     // 0.f -> long double: conversion, 0.f->int conversion: tie 
     // prints 2 
     bar(6.5, 8, 0.f);
     
     // 6.5 -> int conversion, 6.5->double exact: #4 wins 
     // 8 -> float conversion, 8->double conversion: tie 
     // 0.f -> double: promotion, 0.f->int: conversion: #3 wins 
     //baz(6.5,8,0.f); // ERROR
    
    
    std::vector v1{1.2, 2.4, 1.2, 2.4, 0.1};
    std::cout << sum_unique1(v1) << '\n';
    
    std::vector v2{1,2,1,2,3,4,1,2};
    std::cout << sum_unique2(v2) << '\n';
    std::cout << sum_unique2(v1) << '\n';
    
    std::vector<std::string> v3{"cat","dog","cat"};
    std::cout << sum_unique2(v3) << '\n';
    
    int x{};
    double y{};
    std::cout << x << ' ' << y << '\n';
}
