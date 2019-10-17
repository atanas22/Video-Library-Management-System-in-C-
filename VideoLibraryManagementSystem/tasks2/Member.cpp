#include "Member.h"
#include <set>
#include <iomanip>

#include "Date.h"
#include "Pair.h"
#include "HelperFuncs.h"

Member::Member() : ID(0), name(""), phoneNum(""), address(""), rentedCas(), cardValidity(), monthsCardValid(0) {}

Member::Member(const int &ID, const string& name, const string& phoneNum,
			   const string& address, const int& monthsPeriod) :
	ID(ID), name(name), phoneNum(phoneNum), address(address), monthsCardValid(monthsPeriod), rentedCas() {
	updateCardMonths(monthsPeriod);
}

Member::Member(const Member &rhs) : ID(rhs.ID), name(rhs.name), phoneNum(rhs.phoneNum), address(rhs.address),
									cardValidity(rhs.cardValidity), monthsCardValid(rhs.monthsCardValid){
	for (auto it = rhs.rentedCas.begin(); it != rhs.rentedCas.end(); ++it)
		rentedCas.insert(PairStrDate(it->first, it->second));
}

Member& Member::operator=(const Member&rhs) {
	if (this != &rhs) {
		ID = rhs.ID;
		name = rhs.name;
		phoneNum = rhs.phoneNum;
		address = rhs.address;
		cardValidity = rhs.cardValidity;
		monthsCardValid = rhs.monthsCardValid;
		for (auto it = rhs.rentedCas.begin(); it != rhs.rentedCas.end(); ++it)
			rentedCas.insert(PairStrDate(it->first, it->second));
	}
	return *this;
}

void Member::updateCardMonths(const int& monthsPeriod) {
	Date currDate;
	initCurrDate(currDate);

	if (monthsPeriod > 12) 
		cout << "Can't update a card with more than 12 months!\n\n";
	else if(cardValidity.getBegDay() != "" && earlierEndDate(currDate, cardValidity)) 
		cout << "Can't change card validity - the card is not out of date - " << cardValidity << ".\n\n";
	else {
		monthsCardValid = monthsPeriod;
		cardValidity = currDate;
		string newMonth = currDate.getBegMonth();
		int currMonth = atoi(currDate.getBegMonth().c_str());

		if (currMonth + monthsPeriod > 12) {
			int currYear = atoi(currDate.getBegYear().c_str());
			cardValidity.setEndYear(to_string(currYear + 1));
			int endMonth = monthsPeriod - (12 - currMonth);
			newMonth = to_string(endMonth);
		}
		else newMonth = to_string(monthsPeriod + currMonth);
		if (newMonth.size() < 2) newMonth.insert(newMonth.begin(), '0');
		cardValidity.setEndMonth(newMonth);
	}
}

void Member::display() const {
	int cnt = 1;
	cout << "ID         : " << ID << "\n"
		<< "Name       : " << name << "\n"
		<< "Phone Num. : " << phoneNum << "\n"
		<< "address    : " << address << "\n"
		<< "card val.  : " << cardValidity << "\n"
		<< "rented cas.: ";
	for (auto it = rentedCas.begin(); it != rentedCas.end(); ++it) {
		int delay = getDelayOfCas(it->second);
		cout << cnt++ << ". " << it->Name << ", " << it->Term << fixed << ", delay: "
			 << delay << " days, charge: "<< setprecision(2) << delay*0.50 << "lv\n             ";
	}
}

void Member::addInRentList(const string &cas) { // rent cassette
	rentedCas.insert(PairStrDate(cas, calcSevenDaysPeriod()));
}

void Member::removeFromRentList(const string &cas) { // give back cassette
	for (auto it = rentedCas.begin(); it != rentedCas.end(); ++it)
		if (it->Name == cas) {
			rentedCas.erase(it);
			return;
		}
	throw exception();
}

int Member::showRentedCassOutOfDate() {
	Date currDate;
	initCurrDate(currDate); int cnt = 0;
	for (auto it = rentedCas.begin(); it != rentedCas.end(); ++it)
		if (earlierEndDate(it->second, currDate)) {
			cout << "ID: " << ID << ", " << name << ", ph. num.: " << phoneNum <<
				", rented cas.:" << it->Name << " : " << it->Term << "\n";
			++cnt;
		}
		else break;
	return cnt;
}