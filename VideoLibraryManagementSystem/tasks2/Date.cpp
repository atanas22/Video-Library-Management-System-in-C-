#include "Date.h"
#include <string>
#include <iostream>
#include <sstream>

// friend methods
ostream& operator<<(ostream& out, const Date& obj) {
	return out << obj.begDay << "/" << obj.begMonth << "/" << obj.begYear << " - "
		<< obj.endDay << "/" << obj.endMonth << "/" << obj.endYear;
}

bool earlierEndDate(const Date &lhs, const Date& rhs) {
	if (lhs.endYear < rhs.endYear) return 1;
	else if (lhs.endYear > rhs.endYear) return 0;
	else
		if (lhs.endMonth < rhs.endMonth) return 1;
		else if (lhs.endMonth > rhs.endMonth) return 0;
		else
			if (lhs.endDay < rhs.endDay) return 1;
			else if (lhs.endDay > rhs.endDay) return 0;
	return 0;
}

void initCurrDate(Date &currDate) {
	stringstream ss;
	ss << __DATE__;
	ss.rdbuf();

	string month, day, year;
	ss >> month >> day >> year;

	string endDay, endMonth, endYear;
	endDay = day;
	endYear = year;
	if (month == "Jan") endMonth = "01"; else if (month == "Feb") endMonth = "02"; else if (month == "Mar") endMonth = "03";
	else if (month == "Apr") endMonth = "04"; else if (month == "May") endMonth = "05"; else if (month == "Jun") endMonth = "06";
	else if (month == "Jul") endMonth = "07"; else if (month == "Aug") endMonth = "08"; else if (month == "Sep") endMonth = "09";
	else if (month == "Oct") endMonth = "10"; else if (month == "Nov") endMonth = "11"; else if (month == "Dec") endMonth = "12";

	if (endDay.size() == 1) {
		char c = endDay[0];
		endDay[0] = '0';
		endDay.push_back(c);
	}
	currDate.initDate(endDay, endMonth, endYear, endDay, endMonth, endYear);
}
//end of friend methods


// member methods
Date::Date() :  begDay("00"), begMonth("00"), begYear("00"), endDay("00"), endMonth("00"), endYear("00") {}

Date::Date(const string& begDay, const string& begMonth, const string& begYear,
	const string& endDay, const string& endMonth, const string& endYear) : begDay(begDay), begMonth(begMonth), begYear(begYear),
	endDay(endDay), endMonth(endMonth), endYear(endYear) {}

void Date::initDate(const string& bDay, const string& bMonth, const string& bYear,
	const string& eDay, const string& eMonth, const string& eYear) {
	begDay = bDay; begMonth = bMonth; begYear = bYear;
	endDay = eDay; endMonth = eMonth; endYear = eYear;
}

// end of memb methods

Date calcSevenDaysPeriod() {
	Date currDate;
	initCurrDate(currDate);

	int currDay = atoi(currDate.getBegDay().c_str());		string endDay;
	int currMonth = atoi(currDate.getBegMonth().c_str());	string endMonth = currDate.getBegMonth();
	int currYear = atoi(currDate.getBegYear().c_str());		string endYear = currDate.getBegYear();

	if ((currDay + 7) > 30) {
		if (currMonth == 12) {
			endYear = to_string(currYear + 1);
			endMonth = "01";
		}
		else {
			int m = atoi(currDate.getBegMonth().c_str());
			++m;
			endMonth = to_string(m);
			if (m < 10) endMonth.insert(endMonth.begin(), '0');
		}
		int day = 7 - (30 - currDay);
		endDay = "0" + to_string(day);
	}
	else {
		int day = currDay + 7;
		endDay = to_string(day);
		if (day < 10) endDay.insert(endDay.begin(), '0');
	}
	return Date(currDate.getBegDay(), currDate.getBegMonth(), currDate.getBegYear(), endDay, endMonth, endYear);
}

