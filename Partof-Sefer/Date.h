#pragma once

#include <ctime>

const int MONCONV = 1, YEARCONV = 1900;
const int MAX_DAY = 31, MAX_MONTH = 12, CURRENT_YEAR = 2019;

class Date
{
	int day, month, year, hour, min;
	//Date(const Date&date) - the default copy c'tor is good enough
public:
	Date(int day, int month, int year, int hour = 0, int min = 0) { settime(day, month, year, hour, min); } //no default c'tor!
	void settime(int day, int month, int year, int hour, int min);
	void showdate()						const;
	void showtime()						const;
	int getDay() 						const {return day;}    
	int getMonth() 						const {return month;}
	int getYear() 						const {return year;}
	int getHour() 						const {return hour;}
	int getMin() 						const {return min;}
	bool operator<(const Date&compare)	const;
};