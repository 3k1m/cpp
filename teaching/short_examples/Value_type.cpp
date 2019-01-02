/**
This file defines a function, display_info, that displays the value category and type of its argument. 

For the most part, the value category is the most important is it can be the least intuitive without practice. Note: the types displayed 
may seem very strange, depending on the compiler: i for int, e for long double, Pk for pointer to const, etc.
*/

#include<string>
#include<iostream>
#include<type_traits>
#include<typeinfo>

/**
This function displays information about an input whose type and value category we want to check
@tparam T1 used to infer cv qualifications and whether input is an lvalue/xvalue/prvalue
@tparam T2 used to infer general type information since T1 turns named variables into references to lvalues, etc.
*/
template<typename T1, typename T2>
void display_info();

#define check_it(x) display_info<decltype((x)), decltype(x)>()

/**
This function returns the value 100, will be prvalue
@return the value 100
*/
int returnsPR_Value();

/**
This function returns the argument passed in as a reference to const, will be lvalue since it spits out an lvalue
reference
@param i an int input
@return that int
*/
const int& returnsL_Value(const int& i);

/**
This function returns the string that was passed in by moving it, will be an xvalue because the return is
an rvalue reference
@param s the input string
@return the string after moving
*/
std::string&& returnsX_Value(std::string& s);

/**
a basic struct S that stores a double
*/
struct S{ 
	double d = 42;
};


int main()
{    
	const int i = 11;
	check_it(i); // lvalue
	
	check_it(&i); // prvalue

    check_it(4.L);	// prvalue

	check_it(returnsL_Value(i)); // lvalue

	check_it(returnsPR_Value()); // prvalue
	
	std::string s;

	check_it(returnsX_Value(s)); // xvalue
	
    check_it(3 + 11); // prvalue
	check_it(S()); // prvalue

	std::string msg("hello");
	check_it(msg); // lvalue

	check_it(std::move(msg)); // xvalue

	int iarr[] = { 2, 3, 4 };
	
	check_it(true ? iarr[2] : iarr[3]); //lvalue

	check_it("string literal is an lvalue"); //lvalue

	check_it(returnsPR_Value); //lvalue
	
	check_it(std::cout); // lvalue
	
	return 0; 

}

/* defining the display_info */

template<typename T1, typename T2>
void display_info(){
	
	if( std::is_rvalue_reference<T1>::value ){ // if T1 is an rvalue reference type
		std::cout << "X-value: ";
	}
	else if( std::is_lvalue_reference<T1>::value ){ // if T1 is an lvalue reference type
		std::cout << "L-value: ";
	}
	else if ( ! std::is_reference<T1>::value ) { // if T1 is not a reference type
		std::cout << "PR-value: ";
	}
    
	// remove reference first and check if T1 is const qualified
	if( std::is_const<typename std::remove_reference<T1>::type>::value ){
		std::cout << "const ";   
	}
  
	// remove reference first and check if T1 is volatile qualified
	if( std::is_volatile<typename std::remove_reference<T1>::type>::value ){
		std::cout << "volatile ";   
	}
    
	// print the 'name'... won't be that intuitive in some cases
	std::cout << typeid(T2).name();
  
	// if T2 is an lvalue reference then we really have lvalue reference
	if ( std::is_lvalue_reference<T2>::value ){
		std::cout << "&";    
	}
	else if ( std::is_rvalue_reference<T2>::value ){ // if T2 is rvalue reference then have rvalue reference
		std::cout << "&&";    
	}
  
	std::cout << '\n';  
}

int returnsPR_Value(){
	return 100;
}

const int& returnsL_Value(const int& i);{
	return i;
}

std::string&& returnsX_Value(std::string& s){
	return std::move(s);
}