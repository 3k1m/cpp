#include "Student.h"

student::student(const std::string& _name, int _uid) :
	name(_name), uid(_uid), overall_percent(0) {}

int student::get_uid() const {
	return uid;
}

// returns a const string&
// second const is that get_name is accessor
const std::string& student::get_name() const {
	return name;
}

void student::add_hw(int score, int max) {
	homework hw;
	hw.score = score;
	hw.max = max;
	homeworks.push_back(hw);
}

void student::compute_grade() {
	double total = 0;

	for (const homework& h : homeworks) {
		total += static_cast<double>(h.score) / h.max;
	}

	overall_percent = total / homeworks.size() * 100;
}

double student::get_grade() const {
	return overall_percent;
}

// (1)
bool student_less(const student& stu1, const student& stu2) {
	return stu1.get_grade() < stu2.get_grade();
}

// (2)
bool operator<(const student& stu1, const student& stu2) {
	return stu1.get_grade() < stu2.get_grade();
}
