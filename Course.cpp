#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl;

Course::Course(std::string id, std::string title, Date startTime, Date endTime)
: id(id), title(title), startTime(startTime), endTime(endTime), attendanceRecords({})
{
	
}

std::string Course::getID() const {
	return id;
}

std::string Course::getTitle() const {
	return title;
}

Date Course::getStartTime() const {
	return startTime;
}

Date Course::getEndTime() const {
	return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar) {
	if (ar.getDate().getHour() > endTime.getHour() || ar.getDate().getHour() < startTime.getHour()) {
		throw std::invalid_argument("");
	} else if (ar.getDate().getHour() < endTime.getHour() && ar.getDate().getHour() > startTime.getHour()) {
		attendanceRecords.push_back(ar);
	} else {
		
		if (ar.getDate().getHour() == endTime.getHour() && ar.getDate().getHour() > startTime.getHour()) {
			if (ar.getDate().getMin() < endTime.getMin()) {
				attendanceRecords.push_back(ar);
			} else if (ar.getDate().getMin() == endTime.getMin()) {
				if (ar.getDate().getSec() <= endTime.getSec()) {
					attendanceRecords.push_back(ar);
				} else {
					throw std::invalid_argument("");
				}
			} else {
				throw std::invalid_argument("");
			}	
		} else if (ar.getDate().getHour() < endTime.getHour() && ar.getDate().getHour() == startTime.getHour()) {
			if (ar.getDate().getMin() > startTime.getMin()) {
				attendanceRecords.push_back(ar);
			} else if (ar.getDate().getMin() == startTime.getMin()) {
				if (ar.getDate().getSec() >= startTime.getSec()) {
					attendanceRecords.push_back(ar);
				} else {
					throw std::invalid_argument("");
				}
			} else {
				throw std::invalid_argument("");
			}
		} else if (ar.getDate().getHour() == endTime.getHour() && ar.getDate().getHour() == startTime.getHour()) {
			if (ar.getDate().getMin() > endTime.getMin() || ar.getDate().getMin() < startTime.getMin()) {
				throw std::invalid_argument("");
			} else if (ar.getDate().getMin() < endTime.getMin() && ar.getDate().getMin() > startTime.getMin()) {
				attendanceRecords.push_back(ar);
			} else {
				if (ar.getDate().getMin() == endTime.getMin() && ar.getDate().getMin() > startTime.getMin()) {
					if (ar.getDate().getSec() <= endTime.getSec()) {
						attendanceRecords.push_back(ar);
					} else {
						throw std::invalid_argument("");
					}
				} else if (ar.getDate().getMin() < endTime.getMin() && ar.getDate().getMin() == startTime.getMin()) {
					if (ar.getDate().getSec() >= startTime.getSec()) {
						attendanceRecords.push_back(ar);
					} else {
						throw std::invalid_argument("");
					}
				} else if (ar.getDate().getMin() == endTime.getMin() && ar.getDate().getMin() == startTime.getMin()) {
					if (ar.getDate().getSec() > endTime.getSec() || ar.getDate().getSec() < startTime.getSec()) {
						throw std::invalid_argument("");
					} else if (ar.getDate().getSec() <= endTime.getSec() && ar.getDate().getSec() >= startTime.getSec()) {
						attendanceRecords.push_back(ar);
					}
				}
			}	
		}
	}
}

void Course::outputAttendance(std::ostream& os) const {
	if (attendanceRecords.size() == 0) {
		os << "No records\n";
	} else {
	
		for (size_t i = 0; i < attendanceRecords.size(); ++i) {
			
			
			os << attendanceRecords.at(i).getDate().getMonth() << "/"; 
			
			os << attendanceRecords.at(i).getDate().getDay() << "/" << attendanceRecords.at(i).getDate().getYear() << " ";
			
			if (attendanceRecords.at(i).getDate().getHour() < 10) {
				os << "0";
			}
			
			os << attendanceRecords.at(i).getDate().getHour() << ":";
			
			if (attendanceRecords.at(i).getDate().getMin() < 10) {
				os << "0";
			}

			os << attendanceRecords.at(i).getDate().getMin() << ":";
			
			if (attendanceRecords.at(i).getDate().getSec() < 10) {
				os << "0";
			}
			
			os << attendanceRecords.at(i).getDate().getSec() << "," << attendanceRecords.at(i).getCourseID() << "," << attendanceRecords.at(i).getStudentID()  << std::endl;

		}
	
	}
}

void Course::outputAttendance(std::ostream& os, std::string student_id) const {
	bool isValid = false;
	
	if (attendanceRecords.size() == 0) {
		os << "No records" << endl;
		return;
	} else {
	
		for (size_t i = 0; i < attendanceRecords.size(); ++i) {
			if (attendanceRecords.at(i).getStudentID() == student_id) {
				os << attendanceRecords.at(i);
				isValid = true;
			}
		}
	
	}
	
	if (!isValid) {
		os << "No records" << endl;
	}
}

std::ostream& operator<<(std::ostream& os, const Course& c) {
	os << c.getID() << ",";
	
	if (c.getStartTime().getHour() < 10) {
		os << "0";
	}
	
	os << c.getStartTime().getHour() << ":";
	
	if (c.getStartTime().getMin() < 10) {
		os << "0";
	}
	
	os << c.getStartTime().getMin() << ",";
	
	if (c.getEndTime().getHour() < 10) {
		os << "0";
	}

	os << c.getEndTime().getHour() << ":"; 
	
	if (c.getEndTime().getMin() < 10) {
		os << "0";
	}
	
	os << c.getEndTime().getMin() << "," << c.getTitle() << endl;
	
	return os;
}