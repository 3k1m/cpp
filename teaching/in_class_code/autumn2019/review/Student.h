#ifndef _STUDENT_
#define _STUDENT_

#include<string>
#include<vector>

struct homework {
	int score = 0;
	int max = 0;
};

class student {
private:
	std::string name;
	int uid;
	std::vector<homework> homeworks;
	double overall_percent;

public:
	/**
	constructor makes a new student object with given name,
	UID, and makes the letter grade unset
	@param _name the student name
	@param _uid the UID
	*/
	student(const std::string& _name, int _uid);

	/**
	this function returns the uid of the student
	@return the uid
	*/
	int get_uid() const;

	const std::string& get_name() const;

	void add_hw(int score, int max);

	void compute_grade();

	double get_grade() const;

};

// (1) - as predicate
bool student_less(const student& stu1, const student& stu2);

// (2)
bool operator<(const student& stu1, const student& stu2);


#endif
