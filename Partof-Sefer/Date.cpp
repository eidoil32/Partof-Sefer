#include <iostream>
using namespace std;

#include "Date.h"
#include "Services.h"

void Date::settime(int day, int month, int year, int hour, int min)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->min = min;
}

void Date::showdate() const
{
	cout << day << "/" << month << "/" << year;
}

void Date::showtime() const
{
	cout << hour << ":" << min;
}

bool Date::operator<(const Date&compare) const
{
	if(year < compare.getYear())
		return true;
	else if(year > compare.getYear())
		return false;
	else
	{
		if(month < compare.getMonth())
			return true;
		else if(month > compare.getMonth())
			return false;
		else{
			if(day < compare.getDay())
				return true;
			else if(day > compare.getDay())
				return false;
			else
			{
				if(hour< compare.getHour())
					return true;
				else if(hour > compare.getHour())
					return false;
				else
				{
				if(min <= compare.getMin())
					return true;
				else
					return false;
				}
			}
		}
	}
}