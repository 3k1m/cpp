/**
* @file stream_buffer.cpp
* @author Mike Lindstrom
* @date Nov 2019
* @brief: this file illustrates how input streams work with
* their buffers
*
* @details: there is a class in_wrap that wraps around
* in input string stream
*
* the input string stream (iss) in the example should be
* initialized to a sequence of user input where \n
* indicates [ENTER]/[RETURN]
*
* then the in_wrap object (in) in the example is initialized
* from the stream
*
* in can be used to write to variables just like cin would
* and we can examine what is in the buffer
*
*/
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

/**
* @class in_wrap wraps around an input string stream to show how
* streams work internally
*/
class in_wrap {
private:
	std::istringstream& i;  // stream it owns

	/**
	* will print a string but replace new lines, tabs, and
	* spaces with \n, \t, and \s literally
	* @param s the string to print
	*/
	void print_buffer_string(const std::string& s) const;

public:
	/**
	* constructor is given stream to manage
	* @param _i the input string stream to manipulate
	*/
	explicit in_wrap(std::istringstream& _i);

	/**
	* displays the stream data in format
	* [[[position: stream index & buffer:what is in the buffer]]]
	*/
	void print() const;

	/**
	* performs >> for the stream
	* @tparam T the data type being written to
	* @param t the variable being written to
	* @return the stream wrapper
	*/
	template<typename T>
	in_wrap& operator>>(T& t);

	/**
	* gets a char from the stream
	* @return the char
	*/
	char get();

	/**
	* ignores next parts of the stream
	* @param n the maximum number of chars to ignore
	* @param end where to end if n is not exceeded
	*/
	void ignore(
		std::streamsize n = 1, char end = EOF);

	/**
	* clears the failed state
	*/
	void clear();

	/**
	* does a getline
	* @param w the wrapper stream
	* @param s the string to write to
	* @return the stream itself
	*/
	friend in_wrap& getline(in_wrap& w, std::string& s,
		char end = '\n');

	/**
	* converts the wrapper to a bool
	* @return the bool value of the stream
	*/
	explicit operator bool() const;

	/**
	* returns ! for the stream
	* @return true if an error has occurred
	*/
	bool operator!() const;

	/**
	* returns if the stream is good
	* @return true if the stream is not bad, not eof, not fail
	*/
	bool good() const;

	/**
	* returns if the stream has failed
	@ return true if failed
	*/
	bool fail() const;

	/**
	* returns if the stream is in a bad state
	* @return true if in a bad state
	*/
	bool bad() const;

	/**
	* returns eof if the end of file is triggered
	* @return true if at EOF
	*/
	bool eof() const;
};



int main()
{
	// hypothetical user enters:
	// 123.456[ENTER]
	// foo bar baz[ENTER]
	// .86[ENTER]
	// 86[ENTER]
	//
	std::istringstream iss("123.456\nfoo bar baz\n.86\n86\n4 5 6\n");

	// make a wrapper object to handle this sequence of inputs
	in_wrap in(iss);

	// show what is originally there
	// new lines are \n, tabs are \t, and space is \s here
	in.print();

	int a;
	double b;
	in >> a >> b;
	std::cout << "a: " << a << '\n' << "b: " << b << '\n';
	std::string c;
	in >> c;
	std::cout << "c: " << c << '\n';
	std::string d;
	getline(in, d);
	std::cout << "d: " << d << '\n';
	int e;
	std::cout << "------------------------\n";
	in >> e; // will fail!
	in.clear();

	// ignore until new line or max stream size skipped
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	in >> e;
	std::cout << "e: " << e << '\n';

	
	char f = in.get();
	std::cout << "f: " << f << "done"; // f is a new line character

	std::cin.get();

	return 0;
}

void in_wrap::print_buffer_string(const std::string& s) const {
	for (char c : s) { // go over every char separately
		switch (c) {
		case '\n': std::cout << "\\n"; break; // newline
		case '\t': std::cout << "\\t"; break; // tab
		case ' ': std::cout << "\\s"; break; // space character
		default: std::cout << c; break; // all else
		}
	}
}

in_wrap::in_wrap(std::istringstream& _i) : i(_i) {}

void in_wrap::print() const {
	if (i.fail()) { // if it failed say so
		std::cout << "[[[FAILED]]]" << '\n';
	}
	else { // otherwise give the printout
		std::cout << "[[[position:" << i.tellg() << " & buffer:";
		print_buffer_string(i.str().substr(i.tellg()));
		std::cout << "]]]\n";
	}
}


template<typename T>
in_wrap& in_wrap::operator>>(T& t) {
	std::cout << "operator>>";
	i >> t;
	print();
	return *this;
}

char in_wrap::get() {
	std::cout << "get";
	char c = i.get();
	print();
	return c;
}

void in_wrap::ignore(
	std::streamsize n, char end) {
	std::cout << "ignore";
	i.ignore(n, end);
	print();
}

in_wrap& getline(in_wrap& w, std::string& s, char end) {
	std::cout << "getline";
	std::getline(w.i, s, end);
	w.print();
	return w;
}

void in_wrap::clear() {
	std::cout << "clear";
	i.clear();
	print();
}

in_wrap::operator bool() const {
	return static_cast<bool>(i);
}

bool in_wrap::operator!() const {
	return !i;
}

bool in_wrap::good() const {
	return i.good();
}

bool in_wrap::fail() const {
	return i.fail();
}

bool in_wrap::bad() const {
	return i.bad();
}

bool in_wrap::eof() const {
	return i.eof();
}
