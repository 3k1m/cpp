#include<iostream>
#include<string>

double maxx(double a, double b){
    return (a<b) ? b : a;
}

int maxx(int a, int b){
    return (a<b) ? b : a;
}


int main(){
    
    std::cout << maxx(5,7) << '\n';
    
    std::cout << maxx(4.9, 4.8) << '\n';
    
    std::string s1("abc"), s2("def");
    
    std::cout << maxx(s1, s2);
    
    
    return 0;
}
