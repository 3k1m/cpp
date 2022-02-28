#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class weight{
private:
  double lbs;
public:
  weight(double _lbs) : lbs(_lbs) {}
  
  double get_weight() const { return lbs; }
    
};

std::ostream& operator<<(std::ostream& out, const weight& w){
    out << w.get_weight() << " lbs";
    return out;
}

bool operator<(const weight& w1, const weight& w2){
    return w1.get_weight() < w2.get_weight();
}


/*std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
    out << "[ ";
    for(int i : v) { out << i << ' '; }
    out << "]";
    return out;
}*/

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    out << "[ ";
    for(const auto& e : v) { out << e << ' '; }
    out << "]";
    return out;
}

/*
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& v){
    out << "[ ";
    for(const auto& e : v) { out << e << ' '; } // need operator<< for std::vector<double>
    out << "]";
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<double>& v){
    out << "[ ";
    for(const auto& e : v) { out << e << ' '; } // need operator<< for std::vector<double>
    out << "]";
    return out;
}

*/


int main()
{
   weight w(150);
   std::cout << w << '\n';
   
   std::vector<weight> weights;
   weights.push_back( weight(150 ));
   weights.push_back( weight(250 ));
   weights.push_back( weight(125 ));
   weights.push_back( weight(190 ));
   weights.emplace_back(225);
   
   std::sort(weights.begin(), weights.end());
   
   std::cout << "====\n";
   for(weight w : weights){
       std::cout << w << '\n';
   }
   std::cout << "====\n";
   
   std::cout << weights << '\n';
   
   std::cout << "====\n";
   
   std::vector<int> v {1,2,3,4};
   
   std::cout << v << '\n';
   
   std::vector<std::vector<double>> doubles{{1.1, 2.2}, {2.2, 9.8}, {7.7}};
   std::cout << doubles << '\n';
   

    return 0;
}
