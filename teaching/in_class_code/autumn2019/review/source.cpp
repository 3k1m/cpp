#include "Roster.h"
#include "Student.h"

int main() {

	// set the max scores
	roster fake_class("max.txt");

	// read in the file
	fake_class.read_students("grades.txt");

	fake_class.assign_grades(); // have all grades assigned

	fake_class.print_grades(std::cout);

	std::ofstream fout("results.txt");
	fake_class.print_grades(fout);
	fout.close();

	std::cin.get();

	return 0;
}
