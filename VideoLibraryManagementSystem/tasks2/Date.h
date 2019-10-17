#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Date {
	friend ostream& operator<<(ostream& out, const Date& obj);
	friend bool earlierEndDate(const Date &lhs, const Date& rhs);
	friend void initCurrDate(Date &currDate);

public:
	Date();
	Date(const string& begDay, const string& begMonth, const string& begYear,
		const string& endDay, const string& endMonth, const string& endYear);

	void initDate(const string& bDay, const string& bMonth, const string& bYear,
		const string& eDay, const string& eMonth, const string& eYear);

	string getBegDay() const { return begDay; }
	string getBegMonth() const { return begMonth; }
	string getBegYear() const { return begYear; }

	string getEndDay() const { return endDay; }
	string getEndMonth() const { return endMonth; }
	string getEndYear() const { return endYear; }

	void setBegDay(const string& day) { begDay = day; }
	void setBegMonth(const string& month) { begMonth = month; }
	void setBegYear(const string& year) { begYear = year; }

	void setEndDay(const string& day) { endDay = day; }
	void setEndMonth(const string& month) { endMonth = month; }
	void setEndYear(const string& year) { endYear = year; }

private:
	string begDay, begMonth, begYear;
	string endDay, endMonth, endYear;
};

Date calcSevenDaysPeriod();

#endif // !DATE_H
