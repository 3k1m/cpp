#include "Matrix.h"

#include<iostream>
#include<vector>
#include<numbers>
#include<cmath>

namespace math = basic_math;

int main() {
	const char* sep = "==========\n";

	// linear space x: Nx+1 points on [0,1]
	const size_t Nx = 12;
	auto x = math::linspace(0., 1., Nx + 1);
	std::cout << "x and X^T:\n" << x << '\n' << x.T() << '\n';
	x = x.T(); // update x to row vector
	std::cout << sep;

	// just for fun to see different useful elementwise ops
	std::cout << "x+1:\n" << x + 1 << '\n'; // adds/subtracts scalar elementwise
	std::cout << "2+x:\n" << 2 + x << '\n';
	std::cout << "x-1:\n" << x - 1 << '\n';
	std::cout << "1-x:\n" << 1 - x << '\n';
	std::cout << "x*3:\n" << x * 3 << '\n'; // multiplication by scalar
	std::cout << "3*x:\n" << 3 * x << '\n';
	std::cout << "x % (1-x):\n" << x % (1 - x) << '\n'; // % elementwise multiplication and division when using scalars
	std::cout << "x/2:\n" << x / 2 << '\n';
	std::cout << "1/(x+1):\n" << 1 / (x + 1) << '\n';

	std::cout << sep;

	// working with functions
	// % can invoke a function, too!
	auto cube = [](const auto& p) { return p * p * p; };

	// functions acting elementwise
	std::cout << "apply_to(cube, x):\n" << apply_to(cube, x) << '\n'; // direct function call elementwise
	std::cout << "cube % (2*x):\n" << cube % (2 * x) << '\n'; // % overloads to invoke a function
	std::cout << "inline lambda acting on x:\n" << [](auto x) { return x * x; } % x << '\n';

	std::cout << sep;

	// diag and trace features
	math::matrix m(2, 2);
	m(0, 0) = 7;
	m(0, 1) = 8;
	m(1, 0) = -1;
	m(1, 1) = 4;
	std::cout << "m:\n" << m << '\n'; // m
	std::cout << "m.tr():\n" << m.tr() << '\n'; // trace
	std::cout << "m.diag():\n" << m.diag() << '\n'; // diagonal as column, default
	std::cout << "m.diag(true):\n" << m.diag(true) << '\n'; // diagonal as column
	std::cout << "m.diag(false):\n" << m.diag(false) << '\n'; // diagonal as row
	std::cout << "7x7 identity:\n" << math::make_identity<float>(7) << '\n'; // a 7x7 identity matrix of float

	// check determinant
	printline("m.det():\n",m.det());

	std::cout << sep;

	math::matrix v1(1, 3), v2(3, 1), v3(2, 4);
	v1(0, 2) = 7;
	v2(0, 0) = 4;
	v2(1, 0) = 8;
	v2(2, 0) = 3;
	std::cout << "v1, v2, and v3\n" << v1 << '\n' << v2 << '\n' << v3 << '\n';
	std::cout << "diag(v1):\n" << diag(v1) << '\n'; // row vector to matrix	
	std::cout << "diag(v2):\n" << diag(v2) << '\n'; // col vector to matrix
	try { // not a row/col vector, get error
		std::cout << diag(v3) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << "diag(3,3.2):\n" << math::diag(3, 3.2) << '\n'; // diagonal with repeat
	std::cout << "diag(3,3.2).det()\n" << math::diag(3, 3.2).det() << '\n'; // determinant of that diagonal with repeat

	std::cout << sep;

	math::matrix m2(5, 5);
	for (size_t i = 0, rows = m2.size(0); i < rows; ++i) {
		for (size_t j = 0, cols = m2.size(1); j < cols; ++j) {
			if (i != j) {
				m2(i, j) = static_cast<double>(5 * i + j);
			}
		}
	}
	for (size_t i = 0, rows = m2.size(0), col = 0; i < rows; ++i) {
		m2(i, col) *= -1;
	}
	std::cout << "m2:\n" << m2 << '\n';


	// select works like this: (start_row, stop_row, step_row, start_col, stop_col, step_col)
	// where the stops are not inclusive
	// select rows [1,2,3) -> [1,2]
	// select cols [0,2,4,5) -> [0,2,4]
	std::cout << "submatrix of m2:\n" << m2.select(1, 3, 1, 0, 5, 2);

	std::cout << "m2.det():\n" << m2.det(); // correct!

}
