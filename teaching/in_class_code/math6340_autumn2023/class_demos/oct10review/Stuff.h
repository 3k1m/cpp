#ifndef _STUFF_
#define _STUFF_ 

#include <string>
#include <vector>

/**
 * add will add two numbers 
 * @param a the first
 * @param b the second
 * @return the sum 
 */
int add(int a, int b);

void print_vec(const std::vector<int>& v, size_t len = -1);

class course{
private:
  std::string name;
  int hour;
  
public:
  /**
   * constructs a course  
   * @param _name the name of the course
   * @param _hour the hour of the day 
   */
  course(const std::string& _name, int _hour);
  
  int get_hour() const;
  
  const std::string& get_name() const;
  
  void set_hour(int h);
};


#endif 
