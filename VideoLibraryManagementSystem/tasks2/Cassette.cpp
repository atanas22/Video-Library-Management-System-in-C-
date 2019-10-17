#include <iomanip>
#include "Cassette.h"
#include "HelperFuncs.h"

Cassette::Cassette() : name(""), info(""), totalNum(0), leftNum(0), pplRentedCas() {}
	
Cassette::Cassette(const string& name, const string& info, int totalNum) :
		name(name), info(info), totalNum(totalNum), leftNum(totalNum), pplRentedCas() {}

Cassette::Cassette(const Cassette& rhs) : name(rhs.name), info(rhs.info), leftNum(rhs.leftNum), totalNum(rhs.totalNum) {
	for (auto it = rhs.pplRentedCas.begin(); it != rhs.pplRentedCas.end(); ++it)
		pplRentedCas.insert(PairStrDate(it->first, it->second));
}

Cassette& Cassette::operator=(const Cassette&rhs) {
	if (this != &rhs) {
		name = rhs.name;
		info = rhs.info;
		leftNum = rhs.leftNum;
		totalNum = rhs.totalNum;
		for (auto it = rhs.pplRentedCas.begin(); it != rhs.pplRentedCas.end(); ++it)
			pplRentedCas.insert(PairStrDate(it->first, it->second));
	}
	return *this;
}

void Cassette::addInRentList(const Member& member) {
	string person = "ID: " + to_string(member.getID()) + " - " + member.getName(); // if change person str, then change X0258 fun.
	pplRentedCas.insert(PairStrDate(person, calcSevenDaysPeriod()));
	--leftNum;
}

void Cassette::removeFromRentList(const Member& member) {
	string person = "ID: " + to_string(member.getID()) + " - " + member.getName(); //X0258
	for (auto it = pplRentedCas.begin(); it != pplRentedCas.end(); ++it)
		if (it->first == person) {
			pplRentedCas.erase(it);
			break;
		}
	++leftNum;
}

void Cassette::display() const {
	cout << "Name          : " << name << "\n"
		<< "Info          : " << info << "\n"
		<< "Total num.    : " << totalNum << "\n"
		<< "Left num.     : " << leftNum << "\n"
		<< "People rented : ";

	for (auto it = pplRentedCas.begin(); it != pplRentedCas.end(); ++it) {
		int delay = getDelayOfCas(it->second);
		cout << it->first << ", " << it->second << fixed << ", delay: " << delay
		     << " days, charge: " << setprecision(2) << delay * 0.50 << "lv\n                ";
	}

	cout << "\n";
}