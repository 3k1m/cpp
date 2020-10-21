#ifndef _LARGEST_VALUE_
#define _LARGEST_VALUE_

class largest_value{
public:
  /**
  initializes the object with an initial maximum value
  @param _init the initial value
  */
  largest_value(double _init);
  
  /**
  looks at a new number and possibly makes this new number
  the largest value 
  @param _val the value 
  */
  void add_value(double _val);
  
  /**
  gives the maximum value so far 
  @return the maximum value among all values considered including 
  the initial value
  */
  double get_max() const;

private:
  double val;
};
