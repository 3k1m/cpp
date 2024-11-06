#include <iostream>
#include<string>
#include<vector>
#include<algorithm>

struct Good{
    std::string s = "hello";
    const std::string& get_s() const { return s; }
};

struct date{
    int day, month, year;
    date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {}
};

// to do <<, we define a function called operator<<

std::ostream& operator<<(std::ostream& out, const date& d){
    out << d.day << "/" << d.month << "/" << d.year;
    return out;
}

bool operator<(const date& d1, const date& d2){
    if(d1.year < d2.year){
        return true;
    }
    if(d1.year > d2.year){
        return false;
    }
    if(d1.month < d2.month){
        return true;
    }
    if(d1.month > d2.month){
        return false;
    }
    return d1.day < d2.day;
}

std::ostream& operator<<(std::ostream& out, const std::vector<date>& dates){
    for(const auto& d : dates){
        out << d << '\n';
    }
    return out;
}


int main()
{
    date today{5,11,2024};
    
    //       #1         #2     
    std::cout << today << '\n';
    // std::cout is of type std::ostream 
    // std::cout << today -> write the 5/11/2024 to the buffer
    // and evaluates to std::cout (returns a reference to std::cout)
    // this then gets fed in again into operator << 
    // to print the '\n', which after writing that, returns std::cout 

    // same as above
    operator<<(operator<<(std::cout, today),'\n');
    
    std::vector<date> dates;
    dates.emplace_back(5,11,2024);
    dates.emplace_back(6,11,2024);
    dates.emplace_back(4,11,2024);
    
    std::sort(dates.begin(), dates.end()); // requries <
    
    for(const auto& d : dates){
        std::cout << d << '\n';
    }
    
    std::cout << dates;
    
    Good g;
    const std::string& a = g.get_s();
    std::cout << g.get_s() << '\n';
    std::cout << a << '\n';
    g.s = "goodbye";
    std::cout << a << '\n';
    
    std::cout << (7u << 2) << '\n';

    return 0;
}
