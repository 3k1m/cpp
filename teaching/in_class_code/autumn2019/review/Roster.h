#ifndef _ROSTER_
#define _ROSTER_

#include<vector>
#include "Student.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<algorithm>

class roster {
private:
	std::vector<int> max_scores;
	std::vector<student> class_list;

public:
	/**
	will make a roster object that has a list of
	all the max possible scores for the HWs
	@param _max_file the file name for what stores
	all the max possible HW scores
	*/
	roster(const std::string& _max_file) {
		// try to open up the file
		std::ifstream fin(_max_file);

		if (fin) { // opening was a success
			int temp; // temp to be overwritten

			while (fin >> temp) { // until fail to reada value
				max_scores.push_back(temp);
			}
		}
		else { // opening failed
			std::cout << "Failed to open file!\n";
		}

		fin.close();
	}

	void read_students(const std::string& _grade_file) {
		// file will be of format
		// NAME [tab] score [tab] score [tab] ...

		std::ifstream fin(_grade_file);

		if (!fin) { // failed to open file
			std::cout << "File not found for grades\n";
			return;
		}

		while (!fin.eof()) { // while not at EOF
			// read an entire line
			std::string line;
			std::getline(fin, line);

			std::istringstream iss(line);

			std::string name;
			std::getline(iss, name, '\t'); // stop at tab

			int uid; // to store id
			iss >> uid; // id is next after name

			student to_add(name, uid);

			for (int max : max_scores) { // for each HW
				int score;
				iss >> score; // read the student's score
				to_add.add_hw(score, max);
			}

			class_list.push_back(to_add); // store the student!!!!
		}

		fin.close();
	}

	void assign_grades() {
		// auto& or student& b/c we want to change the elements
		// of the vector... not make a copy and change the copy
		for (auto& s : class_list) {
			s.compute_grade();
		}
	}

	// can take any output stream we want... file stream, cout, etc.
	void print_grades(std::ostream& out) const {

		std::vector<student> copy_of_list(class_list);

		// (1)
		//std::sort(std::begin(copy_of_list), std::end(copy_of_list),
		//	student_less); // sort based on predicate

		// (2) with <, this is the default way of std::sorting
		std::sort(std::begin(copy_of_list), std::end(copy_of_list));

		for (const auto& s : copy_of_list) { // look at each student
			out << s.get_name() << "---" << s.get_uid() << " earned: " <<
				s.get_grade() << "%\n";
		}
	}
};


#endif
