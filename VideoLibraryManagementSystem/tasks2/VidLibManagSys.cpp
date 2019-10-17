#include <iomanip>
#include <fstream>
#include "VidLibManagSys.h"
#include "HelperFuncs.h"

VidLibManagSys::VidLibManagSys() : Members(), Cassettes(), releasedIDS(), genNextID(0) {}

void VidLibManagSys::addNewMember(const string &name, const string &phoneNum, const string &address, const int& monthsPeriod) {
	if (monthsPeriod > 12) {
		cout << "Failed to add a new member - month period can't be more than 12 months\n\n";
		return;
	}
	int ID;
	if (releasedIDS.empty())
		ID = ++genNextID;
	else {
		ID = releasedIDS.front();
		releasedIDS.pop();
	}
	Members.insert(pair<int, Member>(ID, Member(ID, name, phoneNum, address, monthsPeriod)));
	cout << "\nMember with ID \""<< ID << "\" added successfully!\n\n";
}

void VidLibManagSys::addNewCassette(const string &name, const string& info, const int& totalNum) {
	auto it = Cassettes.find(name);
	if (it != Cassettes.end()) {
		cout << "Failed to add new cassette - this cassette is already added: " << name << "\n\n";
		return;
	}
	Cassettes.insert(pair<string, Cassette>(name, Cassette(name, info, totalNum)));
	cout << "Cassette with name \"" << name << "\" was added successfully!\n\n";
}

void VidLibManagSys::deleteMember(const int &ID) {
	auto it = Members.find(ID);
	if (it == Members.end()) {
		cout << "Failed to delete a member - there is no member with ID: " << ID << "\n\n";
		return;
	}
	auto rCass = it->second.getRentedCas();
	if (rCass.size() != 0) {
		cout << "Can't delete member with ID \"" << ID << "\" - there are cassettes which he must return\n\n";
		return;
	}
	releasedIDS.push(ID);
	Members.erase(it);
	cout << "Member with ID \""<< ID << "\" deleted successfully\n\n";
}

void VidLibManagSys::deleteCassette(const string &name) { 
	auto it = Cassettes.find(name);
	if (it == Cassettes.end()) {
		cout << "Failed to delete cassette - there is no cassette with name \"" << name << "\"\n\n";
		return;
	}
	Cassettes.erase(name);
	cout << "Cassette with name \"" << name << "\" was deleted successfully\n\n";
}

Member* VidLibManagSys::searchMemberID(const int& ID) { 
	auto it = Members.find(ID);
	if (it == Members.end()) {
		cout << "Failed to find a member - there is no member with ID \"" << ID << "\"\n\n";
		return &Member();
	}
	return &(it->second);
}

list<const Member*> VidLibManagSys::searchMembersName(const string &name) { 
	list<const Member*> members;
	for (auto it = Members.begin(); it != Members.end(); ++it)
		if (it->second.getName() == name) members.push_back(&it->second);
	return members;
}

list<const Member*> VidLibManagSys::allMembers() { 
	list<const Member*> members;
	for (auto it = Members.begin(); it != Members.end(); ++it)
		members.push_back(&it->second);
	return members;
}

Cassette* VidLibManagSys::searchCassetteName(const string &casName) {
	auto it = Cassettes.find(casName);
	if (it == Cassettes.end()) {
		cout << "Failed to find a cassette - there is no cassette with name \"" << casName << "\"\n\n";
		return &Cassette();
	}
	return &(it->second);
}

list<const Cassette*> VidLibManagSys::allCassettes() { 
	list<const Cassette*> cassettes;
	for (auto it = Cassettes.begin(); it != Cassettes.end(); ++it)
		cassettes.push_back(&it->second);
	return cassettes;
}

void VidLibManagSys::rentCassette(const int &ID, const string& casName) { 
	auto member = Members.find(ID);
	Date currDate; initCurrDate(currDate);

	if (member == Members.end()) {
		cout << "Failed to rent a cassette - there is no member with ID \"" << ID << "\"\n\n";
		return;
	}
	if (earlierEndDate(member->second.getCardValidity(), currDate)) {
		cout << "Failed to rent a cassette - the member card is out of date with ID \"" << ID << "\"\n\n";
		return;
	}
	auto cassette = Cassettes.find(casName);
	if (cassette == Cassettes.end()) {
		cout << "Failed to rent a cassette - there is no cassette with name \"" << casName << "\"\n\n";
		return;
	}
	if (cassette->second.getLeftNum() == 0) {
		cout << "Failed to rent a cassette - there are no cassttes \""<< casName << "\" left in the library \n\n";
		return;
	}

	member->second.addInRentList(casName);
	cassette->second.addInRentList(member->second);
	cout << "Successfully rented cassette \"" << casName << "\" from member with ID \"" << ID << "\"\n\n";
}

void VidLibManagSys::returnCassette(const int &ID, const string& casName) {
	auto member = Members.find(ID);
	if (member == Members.end()) {
		cout << "Failed to return a cassette - there is no member with ID \"" << ID << "\"\n\n";
		return;
	}
	auto cassette = Cassettes.find(casName);
	if (cassette == Cassettes.end()) {
		cout << "Failed to return a cassette - there is no cassette with name \"" << casName << "\"\n\n";
		return;
	}
	try {
		auto rentCass = member->second.getRentedCas();
		Date period;
		for (auto it = rentCass.begin(); it != rentCass.end(); ++it) 
			if (it->first == casName) {
				period = it->second;
				break;
			}

		float charge = getDelayOfCas(period) * 0.50;
		member->second.removeFromRentList(casName);
		cassette->second.removeFromRentList(member->second);
		cout << "Successfully returned cassette \"" << casName << "\" from member with ID  \"" << ID << "\"\n";
		cout << "The member owes: " << fixed << setprecision(2) << charge << "lv\n\n";
	}
	catch (...) {
		cout << "Failed to return cassette, \"" << member->second.getName() << "\" has not rented \"" << casName << "\"\n\n";
	}
}

void VidLibManagSys::showRentedCassOutOfDate() {
	bool outdatedCas = false; int cnt = 0;
	for (auto it = Members.begin(); it != Members.end(); ++it) {
		cnt += it->second.showRentedCassOutOfDate();
	}
	if (outdatedCas == 0) cout << "There are no outdated cassettes.\n\n";
	else cout << "There are " << cnt << " outdated cassettes\n\n";
}

bool VidLibManagSys::checkID(const int &ID) {
	Member * memb = searchMemberID(ID);
	if (memb->getName() == "") return 0;
	return 1;
}

bool VidLibManagSys::checkCassName(const string &casName) {
	Cassette * cass = searchCassetteName(casName);
	if (cass->getName() == "") return 0;

	return 1;
}

bool VidLibManagSys::searchCassetteNoComm(const string &casName) {
	auto it = Cassettes.find(casName);
	if (it == Cassettes.end()) return 0;
	return 1;
}

bool VidLibManagSys::searchIDNoComm(const int &ID) {
	auto it = Members.find(ID);
	if (it == Members.end()) return 0;
	return 1;
}

void VidLibManagSys::loadData() {
	
	unordered_map<int, Member> Membs;
	ifstream in("MembersData.txt");
	if (in.fail()) { return; }

	int numMembs; in >> numMembs;
	string bin;
	string begDay, begMonth, begYear;
	string endDay, endMonth, endYear;
	for (int i = 0; i < numMembs; ++i) {
		int ID; in >> ID; getline(in, bin);
		string name; getline(in, name);
		string phoneNum; getline(in, phoneNum);
		string address; getline(in, address);
		int monthsCardValid; in >> monthsCardValid; getline(in, bin);
		
		getline(in, begDay); getline(in, begMonth); getline(in, begYear);
		getline(in, endDay); getline(in, endMonth); getline(in, endYear);
		
		Date cardValidity(begDay, begMonth, begYear, endDay, endMonth, endYear);
		Member memb(ID, name, phoneNum, address, monthsCardValid);
		memb.setCardValidity(cardValidity);

		int numMembRentCas; in >> numMembRentCas; getline(in, bin);
		multiset<PairStrDate, PairComp> rentCas;
		for (int i = 0; i < numMembRentCas; ++i) {	
			string casName; getline(in, casName);
			getline(in, begDay); getline(in, begMonth); getline(in, begYear);
			getline(in, endDay); getline(in, endMonth); getline(in, endYear);
			Date period(begDay, begMonth, begYear, endDay, endMonth, endYear);
			rentCas.insert(PairStrDate(casName, period));
		}
		memb.setRentedCas(rentCas);
		Membs.insert(pair<int, Member>(ID, memb));
	}
	Members = Membs;
	in.close(); // close membData file

	unordered_map<string, Cassette> Cass;
	
	in.open("CassettessData.txt");
	if (in.fail()) { return; }
	int numCass; in >> numCass; getline(in, bin);

	for (int i = 0; i < numCass; ++i) {
		string name; getline(in, name);
		string info; getline(in, info);
		int totalNum; in >> totalNum; getline(in, bin);
		int leftNum; in >> leftNum; getline(in, bin);

		Cassette cas(name, info, totalNum);
		cas.setLeftNum(leftNum);

		int numMembsRentCas; in >> numMembsRentCas; getline(in, bin);
		multiset<PairStrDate, PairComp> membsRentedCas;
		for (int i = 0; i < numMembsRentCas; ++i) {
			string membName; getline(in, membName);
			getline(in, begDay); getline(in, begMonth); getline(in, begYear);
			getline(in, endDay); getline(in, endMonth); getline(in, endYear);
			Date period(begDay, begMonth, begYear, endDay, endMonth, endYear);
			membsRentedCas.insert(PairStrDate(membName, period));
		}
		cas.setPplRentedCas(membsRentedCas);
		Cass.insert(pair<string, Cassette>(name, cas));
	}
	Cassettes = Cass;
	in.close(); // close cassData file
	
	in.open("ReleasedIDsData.txt");
	if (in.fail()) { return; }
	queue<int, list<int>> releasIDS;
	in >> genNextID; getline(in, bin); // genNextID = gnNxtID;
	int numReIDS; in >> numReIDS;

	for (int i = 0, x; i < numReIDS; ++i) {
		in >> x;
		releasIDS.push(x);
	}
	releasedIDS = releasIDS;
	in.close();
}

void VidLibManagSys::saveData() const {
	ofstream out("MembersData.txt");
	
	out << Members.size() << endl;
	for (auto it = Members.begin(); it != Members.end(); ++it) {
		out << it->second.getID() << endl;
		out << it->second.getName() << endl;
		out << it->second.getPhoneNum() << endl;
		out << it->second.getAddr() << endl;
		out << it->second.getMonthsCardValid() << endl;
		
		Date cardValid = it->second.getCardValidity();
		out << cardValid.getBegDay() << endl << cardValid.getBegMonth() << endl << cardValid.getBegYear() << endl; 
		out << cardValid.getEndDay() << endl << cardValid.getEndMonth() << endl << cardValid.getEndYear() << endl;

		auto membRentCas = it->second.getRentedCas();
		out << membRentCas.size() << endl;
		for (auto it = membRentCas.begin(); it != membRentCas.end(); ++it) {
			out << it->first << endl;
			out << it->second.getBegDay() << endl <<  it->second.getBegMonth() << endl <<  it->second.getBegYear() << endl;
			out << it->second.getEndDay() << endl <<  it->second.getEndMonth() << endl <<  it->second.getEndYear() << endl;
		}
	}

	out.close();
	out.open("CassettessData.txt");

	out << Cassettes.size() << endl;
	for (auto it = Cassettes.begin(); it != Cassettes.end(); ++it) {
		out << it->second.getName() << endl;
		out << it->second.getInfo() << endl;
		out << it->second.getTotalNum() << endl;
		out << it->second.getLeftNum() << endl;

		auto pplRentedCas = it->second.getPplRentedCas();
		out << pplRentedCas.size() << endl;
		for (auto it = pplRentedCas.begin(); it != pplRentedCas.end(); ++it) {
			out << it->first << endl;
			out << it->second.getBegDay() << endl << it->second.getBegMonth() << endl << it->second.getBegYear() << endl;
			out << it->second.getEndDay() << endl << it->second.getEndMonth() << endl << it->second.getEndYear() << endl;
		}
	}

	out.close();
	out.open("ReleasedIDsData.txt");
	
	out << genNextID << endl;
	out << releasedIDS.size() << endl;
	auto releasIDS = releasedIDS;
	for (int i = 0; i < releasIDS.size(); ++i) {
		out << releasIDS.front() << endl;
		releasIDS.pop();
	}

	out.close();
}