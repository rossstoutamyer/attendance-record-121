#include <iostream>
#include <string>
#include "Student.h"

Student::Student(std::string student_id, std::string name)
: id(student_id), name(name)
{
	
}

std::string Student::get_id() const {
	return id;
}

std::string Student::get_name() const {
	return name;
}

void Student::addCourse(std::string course_id) {
	bool isPresent = false;
	
	for (size_t i = 0; i < course_ids.size(); ++i) {
		if (course_ids.at(i) == course_id) {
			isPresent = true;
		}
	}
	
	if (!isPresent) {
		course_ids.push_back(course_id);
	} else {
		throw std::invalid_argument("");
	}
}

void Student::listCourses(std::ostream& os) const {
	std::cout << "Courses for " << id << std::endl;
	
	if (course_ids.size() == 0) {
		std::cout << "No courses" << std::endl;
	} else {
	
		for (size_t i = 0; i < course_ids.size(); ++i) {
			std::cout << course_ids.at(i) << std::endl;
		}
	
	}
}
  
std::ostream& operator<<(std::ostream& os, const Student& s) {
	os << s.get_id() << "," << s.get_name() << std::endl;
	
	return os;
}