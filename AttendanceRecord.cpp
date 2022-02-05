#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

AttendanceRecord::AttendanceRecord(std::string course_id, std::string student_id, Date time)
: course_id(course_id), student_id(student_id), time(time)
{

}

std::string AttendanceRecord::getCourseID() const {
	return course_id;
}

std::string AttendanceRecord::getStudentID() const {
	return student_id;
}

Date AttendanceRecord::getDate() const {
	return time;
}

std::ostream& operator<<(std::ostream& os, const AttendanceRecord& ar) {
	
	os << ar.getDate().getMonth() << "/"; 
	
	os << ar.getDate().getDay() << "/" << ar.getDate().getYear() << " ";
	
	if (ar.getDate().getHour() < 10) {
		os << "0";
	}
	
	os << ar.getDate().getHour() << ":";
	
	if (ar.getDate().getMin() < 10) {
		os << "0";
	}

	os << ar.getDate().getMin() << ":";
	
	if (ar.getDate().getSec() < 10) {
		os << "0";
	}
	
	os << ar.getDate().getSec() << "," << ar.getCourseID() << "," << ar.getStudentID()  << std::endl;
	
	return os;
}