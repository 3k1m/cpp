#include <iostream>

using namespace std;

class weight{
  double lbs;
  
public:
  weight(double _lbs) : lbs(_lbs) {}
  
  double get_weight() const { return lbs; }
};

ostream& operator<<(ostream& out, const weight& w){
    out << w.get_weight() << " lbs";
    return out;
}


int main()
{
    weight w(200);
    cout << w << '\n';
    
    operator<<(cout, w);

    return 0;
}
