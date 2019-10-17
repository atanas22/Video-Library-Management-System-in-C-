#ifndef VIDLIBMANAGSYS_H
#define VIDLIBMANAGSYS_H
// MAHNI NQKOI biblioteki
#include <string> 
#include <utility>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <exception>

#include "Date.h"
#include "Member.h"
#include "Cassette.h"
#include "Pair.h"

class VidLibManagSys {
public:
	VidLibManagSys();

	void addNewMember(const string &name, const string &phoneNum, const string &address, const int& monthsPeriod);
	void addNewCassette(const string &name, const string& info, const int& totalNum);

	void deleteMember(const int &ID);
	void deleteCassette(const string &name);

	Member* searchMemberID(const int& ID);
	list<const Member*> searchMembersName(const string &name);
	list<const Member*> allMembers();

	Cassette* searchCassetteName(const string &casName);
	list<const Cassette*> allCassettes();

	void rentCassette(const int &ID, const string& casName);
	void returnCassette(const int &ID, const string& casName);

	void showRentedCassOutOfDate();
	bool checkID(const int &ID);
	bool checkCassName(const string &casName);

	bool searchCassetteNoComm(const string &casName);
	bool searchIDNoComm(const int &ID);

	void loadData();
	void saveData() const;

private:
	unordered_map<int, Member> Members;
	unordered_map<string, Cassette> Cassettes;
	
	int genNextID;
	queue<int, list<int>> releasedIDS; // by deleted members
};


#endif
