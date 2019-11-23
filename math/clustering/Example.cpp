/**
@file Example.cpp
@author Mike Lindstrom
@date November 2019

@brief This illustrates the use of the kmeans algorithm defined in kmeans.h

@details There are 2 examples:
first - cluster points in R^3 into two clusters adding points as coordinates
second - cluster points in R^1 into three clusters, adding points directly
*/

#include "kmeans.h"

#include<sstream>

int main() {
	// first example just add points manually

	basic_math::kmeans<2, 3> a;
	a.add_point({ 1, 1, 1});
	a.add_point({ 2, 2, 2 });
	a.add_point({ 7, 7, 7 });
	a.add_point({ 8, 8, 8 });
	a.add_point({ 0,0,0 });
	a.do_clustering(100);

	a.print_clusters();
	
	std::cout << '\n';

	// here we add points one at a time through processing
	basic_math::kmeans<3, 1, float> b;

	std::istringstream iss("-10 17 -9 -5  7 -4 -3 -3 -3.2 -8 -2 6.23 7.1 14 0");

	basic_math::array_vector<1, float> p;

	while (iss >> p) { // keep reading
		b.add_point(p);
	}


	b.do_clustering(20);
	b.print_clusters();

	std::cin.get();

	return 0;

}
