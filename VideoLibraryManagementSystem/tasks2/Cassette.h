#ifndef CASSETTE_H
#define CASSETTE_H
#include <set>
#include "Date.h"
#include "Member.h"

class Cassette {
public:
	Cassette();
	Cassette(const string& name, const string& info, int totalNum);
	Cassette(const Cassette& rhs);
	Cassette& operator=(const Cassette&rhs);

	string getName() const { return name; }
	string getInfo() const { return info; }
	int getTotalNum() const { return totalNum; }
	int getLeftNum() const { return leftNum; }
	const multiset<PairStrDate, PairComp>& getPplRentedCas() const { return pplRentedCas; }

	void addNewCassettes(const int &num) { leftNum += num; totalNum += num; }
	void reduceCassettes(const int &num) { leftNum -= num; totalNum -= num; }
	void setInfo(const string &info) { this->info = info; }
	void setLeftNum(const int& num) { leftNum = num; }
	void setPplRentedCas(const multiset<PairStrDate, PairComp>& rhs) { pplRentedCas = rhs; }

	void addInRentList(const Member& member);
	void removeFromRentList(const Member& member);
	void display() const;

private:
	string name;
	string info;
	int totalNum;
	int leftNum;
	multiset<PairStrDate, PairComp> pplRentedCas; // people who rent this cassette
};

#endif
