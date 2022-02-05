#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include "Date.h"

using std::string, std::stringstream, std::setw,  std::setfill;

// TODO: implement the two constructors
Date::Date(int year, int month, int day, int hour, int min, int sec)
: year(year), month(month), day(day), hour(hour), min(min), sec(sec)
{
	
}

Date::Date(int hour, int min, int sec) 
: year(0), month(0), day(0), hour(hour), min(min), sec(sec)
{
	
}

// TODO: implement the < comparison operator
bool Date::operator<(const Date& rhs) const {
    if (this->year > rhs.getYear()) {
		return false;
	} else if (this->year < rhs.getYear()) {
		return true;
	}
	
	if (this->month > rhs.getMonth()) {
		return false;
	} else if (this->month < rhs.getMonth()) {
		return true;
	}
	
	if (this->day > rhs.getDay()) {
		return false;
	} else if (this->day < rhs.getDay()) {
		return true;
	}
	
	if (this->hour > rhs.getHour()) {
		return false;
	} else if (this->hour < rhs.getHour()) {
		return true;
	}
	
	if (this->min > rhs.getMin()) {
		return false;
	} else if (this->min < rhs.getMin()) {
		return true;
	}
	
	if (this->sec > rhs.getSec()) {
		return false;
	} else if (this->sec < rhs.getSec()) {
		return true;
	}
	
	return false;
}

// methods below are provided to students

string Date::getDateTime() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year << " ";
  ss << setw(2) << setfill('0') << hour << ":"; 
  ss << setw(2) << setfill('0') << min << ":";
  ss << setw(2) << setfill('0') << sec;
  return ss.str();
}

string Date::getDate() const {
  stringstream ss;
  ss << month << "/" << day << "/" << year;
  return ss.str();
}

string Date::getTime(bool withSeconds) const {
  stringstream ss;
  ss << setw(2) << setfill('0') << hour << ":"; 
  ss << setw(2) << setfill('0') << min;
  if (withSeconds)
    ss << ":" << setw(2) << setfill('0') << sec;
  return ss.str();
}



bool Date::operator>(const Date& rhs) const {
    return rhs < *this;
}

bool Date::operator<=(const Date& rhs) const {
    return !(*this > rhs);
}

bool Date::operator>=(const Date& rhs) const {
    return !(*this < rhs);
}

bool leap_year(unsigned int year) {
  /* From wikipedia: year which is a multiple of 4 (except for years evenly divisible by 100, 
   * which are not leap years unless evenly divisible by 400).
   */
  if (year % 400 == 0 
      || (year % 4 == 0 && year % 100 != 0)) {
    return true;
  }
  return false;
}

bool Date::isValid() const {
  if (day == 0 || month == 0) {
    return false;
  }
  if (month > 12) {
    return false;
  }
  int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31,
                                    31, 30, 31, 30, 31};
  if (leap_year(year)) {
    days_in_month[2] = 29;
  } 

  if (day > days_in_month[month]) {
    return false;
  }
  return true;
}