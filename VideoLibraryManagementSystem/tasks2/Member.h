#ifndef MEMBER_H
#define MEMBER_H

#include <set>
#include "Date.h"
#include "Pair.h"

class Member {
public:
	Member();
	Member(const int &ID, const string& name, const string& phoneNum, const string& address, const int& monthsPeriod);
	Member(const Member &rhs);
	Member& operator=(const Member&rhs);

	void setID(const int& rhs) { ID = rhs; }
	void setName(const string& rhs) { name = rhs; }
	void setPhoneNum(const string& rhs) { phoneNum = rhs; }
	void setAddr(const string& rhs) { address = rhs; }
	void setMonthsCardValid(const int& rhs) { monthsCardValid = rhs; }
	void setCardValidity(const Date& rhs) { cardValidity = rhs; }
	void setRentedCas(const multiset<PairStrDate, PairComp>& rhs) { rentedCas = rhs; }
	
	void updateCardMonths(const int& monthsPeriod);

	int getID() const { return ID; }
	string getName() const { return name; }
	string getPhoneNum() const { return phoneNum; }
	string getAddr() const { return address; }
	Date getCardValidity() const { return cardValidity; }
	int getMonthsCardValid() const { return monthsCardValid; }
	const multiset<PairStrDate, PairComp>& getRentedCas() const { return rentedCas; }

	void display() const;
	void addInRentList(const string &cas);
	void removeFromRentList(const string &cas);
	int showRentedCassOutOfDate();


private:
	int ID;
	string name;
	string phoneNum;
	string address;

	int monthsCardValid;
	Date cardValidity;
	
	multiset<PairStrDate, PairComp> rentedCas;
};


#endif
