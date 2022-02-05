#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::stoi;

void School::addCourses(std::string filename) {
	
  ifstream ifs2(filename);
  if (!ifs2.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while (!ifs2.eof()) {
    string line;
    getline(ifs2, line);
	if (line == "") {
		break;
	}
	
    istringstream ss(line);
    string id;
    getline(ss, id, ',');
    string startHour;
    getline(ss, startHour, ':');
	string startMinute;
    getline(ss, startMinute, ',');
	string endHour;
    getline(ss, endHour, ':');
	string endMinute;
    getline(ss, endMinute, ',');
	string title;
    getline(ss, title);
	
	Date start(std::stoi(startHour), stoi(startMinute));
	Date end(std::stoi(endHour), stoi(endMinute));
	
    if (!ss.fail()) {
        Course course(id, title, start, end);
        courses.push_back(course);
    }
  }
  ifs2.close();
}

// one method is provided to students; students implement all other methods
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
  ifs.close();
}

bool School::isEnrolled(std::string student_id) const {
	for (size_t i = 0; i < students.size(); ++i) {
		if (students.at(i).get_id() == student_id) {
			return true;
		}
	}
	
	return false;
}

unsigned int School::addAttendanceData(std::string filename) {
  unsigned int invalidAttendance = 0;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addAttendanceData: can't open file");
  }
  while (!ifs.eof()) {
	bool isStudent = false;
	bool isCourse = false;
	  
    string line;
    getline(ifs, line);
	
	if (line == "") {
		break;
	}
	
    istringstream ss(line);
    string year;
    getline(ss, year, '-');
	string month;
    getline(ss, month, '-');
	string day;
    getline(ss, day, ' ');
	string hour;
    getline(ss, hour, ':');
	string minute;
    getline(ss, minute, ':');
	string seconds;
	getline(ss, seconds, ',');
	string course_id;
	getline (ss, course_id, ',');
    string student_id;
    getline(ss, student_id);
    
    for (size_t i = 0; i < students.size(); ++i) {
		if (students.at(i).get_id() == student_id) {
			isStudent = true;
			break;
		}
	}
	
	if (!ss.fail()) {
		Date totalDate(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(minute), stoi(seconds));
			
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses.at(i).getID() == course_id) {
				isCourse = true;
				AttendanceRecord tempAttend(course_id, student_id, totalDate);
				courses.at(i).addAttendanceRecord(tempAttend);
			}
		}
		
		if (!isStudent || !isCourse || !totalDate.isValid()) {
			++invalidAttendance;
		}
	}
  }
  
  return invalidAttendance;
}

void School::listCourses(std::ostream& os) const {
	if (courses.size() == 0) {
		os << "No courses" << std::endl;
	} else {
	
		for (size_t i = 0; i < courses.size(); ++i) {
			os << courses.at(i);
		}
	
	}
}

void School::listStudents(std::ostream& os) const {
	if (students.size() == 0) {
		os << "No students" << std::endl;
	} else {
	
		for (size_t i = 0; i < students.size(); ++i) {
			os << students.at(i) << endl;
		}
	
	}
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const {
	if (courses.size() == 0) {
		std::cout << "No records" << endl;
	}
	
	for (size_t i = 0; i < courses.size(); ++i) {
		if (courses.at(i).getID() == course_id) {
			courses.at(i).outputAttendance(os);
		}
	}
}

void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const {
	bool isStudent = false;
	bool isCourse = false;
	
	for (size_t i = 0; i < students.size(); ++i) {
		if (students.at(i).get_id() == student_id) {
			isStudent = true;
		}
	}
	
	for (size_t i = 0; i < courses.size(); ++i) {
		if (courses.at(i).getID() == course_id) {
			isCourse = true;
		}
	}
	
	if (!isStudent || !isCourse) {
		throw std::invalid_argument("");
	} else {
	
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses.at(i).getID() == course_id) {
				courses.at(i).outputAttendance(std::cout, student_id);
			}
		}
		
	}
}