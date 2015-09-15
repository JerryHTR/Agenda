#include "Date.h"
#include <sstream>
#include <iostream>

Date::Date() {
  year_ = month_ = day_ = hour_ = minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year_ = year;
}

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getDay(void) const {
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

bool Date::isValid(Date date) {
  int leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int average[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  if (date.year_ >= 1000 && date.year_ <= 9999) {
    if (date.year_ % 400 == 0 || (date.year_ % 4 == 0) && (date.year_ % 100 != 0)) {
      if (date.month_ >= 1 && date.month_ <= 12) {
        if (date.day_ >= 1 && date.day_ <= leap[date.month_ - 1]) {
	  if (date.hour_ >= 0 && date.hour_ <= 23) {
	    if (date.minute_ >= 0 && date.minute_ <= 59) {
	      return true;
	    }
	  }
        }
      }
    } else {
      if (date.month_ >= 1 && date.month_ <= 12) {
        if (date.day_ >= 1 && date.day_ <= average[date.month_ - 1]) {
	  if (date.hour_ >= 0 && date.hour_ <= 23) {
	    if (date.minute_ >= 0 && date.minute_ <= 59) {
	      return true;
	    }
	  }
        }
      }
    }
    return false;
  } else {
    return false;
  }
}

Date Date::stringToDate(std::string dateString) {
  std::stringstream ss;
  int y, m, d, h, mi;
  for (int i = 0; i < dateString.length(); i++) {
    if (dateString[i] == '/' || dateString[i] == '-' || dateString[i] == ':') {
      dateString[i] = ' ';
    }
  }
  ss << dateString;
  ss >> y >> m >> d >> h >> mi;
  Date nd(y, m, d, h, mi);
  return nd;
}

std::string convert(int str) {
  std::string result;
  std::stringstream ss;
  ss << str;
  result = ss.str();
  if (result.length() == 1) {
    result = "0" + result;
  }
  return result;
}

std::string Date::dateToString(Date date) {
  std::string convert(int str);
  std::string str, result;
  str = convert(date.year_);
  result = str + "-";
  str = convert(date.month_);
  result = result + str + "-";
  str = convert(date.day_);
  result = result + str + "/";
  str = convert(date.hour_);
  result = result + str + ":";
  str = convert(date.minute_);
  result = result + str;
  return result;
}

Date &Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;
  return *this;
}

bool Date::operator==(const Date& date) const {
  if (year_ == date.year_ && month_ == date.month_
      && day_ == date.day_ && hour_ == date.hour_
      && minute_ == date.minute_) {
    return true;
  } else {
    return false;
  }
}

bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) {
    return true;
  }
  if (year_ == date.year_ && month_ > date.month_) {
    return true;
  }
  if (year_ == date.year_ && month_ == date.month_ && day_ > date.day_) {
    return true;
  }
  if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_ \
      && hour_ > date.hour_) {
    return true;
  }
  if (year_ == date.year_ && month_ == date.month_ && day_ == date.day_ \
	   && hour_ == date.hour_ && minute_ > date.minute_) {
    return true;
  }
  return false;
}

bool Date::operator<(const Date& date) const {
  return !(*this >= date);
}

bool Date::operator>=(const Date& date) const {
  return (*this > date || *this == date);
}

bool Date::operator<=(const Date& date) const {
  return !(*this > date); 
}

