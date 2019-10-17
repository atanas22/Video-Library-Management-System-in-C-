#include "HelperFuncs.h"

void cinFix() {// errors fix
	cin.clear();
	string bin;
	getline(cin, bin);
}

void choiceCinCheck(int &choice, const int &maxNum) {
	string bin;
	getline(cin, bin);

	if (bin.size() > 0 || choice < 1 || choice > maxNum) cout << endl;
	while (bin.size() > 0 || choice < 1 || choice > maxNum) {
		cout << "Wrong entered value.\n";
		if (!cin) cinFix();
		cout << "Enter choice(1 - " << maxNum << "): "; cin >> choice;
		cin.clear();
		getline(cin, bin);
	}
}

bool idCinCheck(const int &entID) {
	if (!cin) cin.clear();
	string bin;
	getline(cin, bin);
	if (bin.size() > 0) {
		cout << "Wrong entered value.\n";
		return 0;
	}
	return 1;
}

Member initMember() {
	string name, phoneNum, addr;
	int monthsPeriod = 0;
	cout << "Name                    : "; getline(cin, name);
	cout << "PhoneNum                : "; getline(cin, phoneNum);
	cout << "Address                 : "; getline(cin, addr);
	cout << "Card valid.(1 - 12mnts) : "; cin >> monthsPeriod;

	bool f = !idCinCheck(monthsPeriod); cout << endl;
	while (f || monthsPeriod < 1 || monthsPeriod > 12) {
		if (!f) cout << "Wrong entered value.\n";
		cout << "Card valid.(1 - 12mnts) : "; cin >> monthsPeriod;
		f = !idCinCheck(monthsPeriod);
	}
	return Member(0, name, phoneNum, addr, monthsPeriod);
}

Cassette initCassette(VidLibManagSys& managSys) {
	string name, info = "";
	int totalNum = 0;
	cout << "Name                    : "; getline(cin, name);
	if (managSys.searchCassetteNoComm(name))
		return Cassette(name, " ", totalNum);
	cout << "Info                    : "; getline(cin, info);
	cout << "Number of cassettes     : "; cin >> totalNum;

	bool f = !idCinCheck(totalNum);
	cout << endl;
	while (f || totalNum < 0) {
		if (!f) cout << "Wrong entered value.\n";
		cout << "Number of cassettes     : "; cin >> totalNum;
		f = !idCinCheck(totalNum);
	}
	return Cassette(name, info, totalNum);
}

void modifMembData(Member *memb) {
	int choice = 0;
	do {
		memb->display(); cout << "\n\n";
		cout << "1.Change phone number\n";
		cout << "2.Change address\n";
		cout << "3.Update card validity\n";
		cout << "4.Back\n\n";
		cout << "Enter choice(1 - 4)     : ";
		cin >> choice; choiceCinCheck(choice, 4); cout << endl;

		if (choice == 1) {
			string newPhoneNum;
			cout << "Enter new Phone num     : ";
			getline(cin, newPhoneNum);
			memb->setPhoneNum(newPhoneNum);
		}
		else if (choice == 2) {
			string newAddress;
			cout << "Enter address           : ";
			getline(cin, newAddress);
			memb->setAddr(newAddress);
		}
		else if (choice == 3) {
			int newValidPeriod;
			cout << "Enter period(1 - 12mnts): ";
			cin >> newValidPeriod; cout << endl;

			bool f = !idCinCheck(newValidPeriod);
			while (f || newValidPeriod < 1 || newValidPeriod > 12) {
				if (!f) cout << "Wrong entered value.\n";
				cout << "Card valid.(1 - 12mnts) : "; cin >> newValidPeriod;
				f = !idCinCheck(newValidPeriod);
			}
			memb->updateCardMonths(newValidPeriod);
		}
		else if (choice == 4) {
			cout << "--------------\n";
		}
		cout << endl;
	} while (choice != 4);
}

void modifCassData(Cassette *cas) {
	int choice = 0;
	do {
		cout << endl;
		cas->display(); cout << endl;
		cout << "1. Add cassettes\n";
		cout << "2. Reduce cassettes\n";
		cout << "3. Change information\n";
		cout << "4. Back\n\n";
		cout << "Enter choice(1 - 4): ";
		cin >> choice; choiceCinCheck(choice, 4); cout << endl;

		if (choice == 1) {
			cout << "Enter num. cassettes to add: ";
			int num; cin >> num;

			if (!cin) cin.clear();
			string bin; getline(cin, bin);

			while ((bin.size() > 0) || (num < 0)) {
				bin.erase();
				cout << "Wrong entered value.\n";
				cout << "Enter num. of cassettes to add: "; cin >> num;
				if (!cin) cin.clear();
				bin; getline(cin, bin);
			}
			cas->addNewCassettes(num);
		}
		else if (choice == 2) {
			cout << "Enter num. cassettes to reduce: ";
			int num; cin >> num;

			if (!cin) cin.clear();
			string bin; getline(cin, bin);

			while ((bin.size() > 0) || (num < 0) || (num > cas->getLeftNum())) {
				bin.erase();
				cout << "Wrong entered value.\n";
				cout << "Enter num. of cassettes to reduce: "; cin >> num;
				if (!cin) cin.clear();
				bin; getline(cin, bin);
			}
			cas->reduceCassettes(num);
		}
		else if (choice == 3) {
			cout << "Enter new information : ";
			string info;
			getline(cin, info);
			cas->setInfo(info);
		}
		else if (choice == 4)
			cout << "--------------\n\n";
	} while (choice != 4);
}

void printMembs(const list<const Member *>& members) {
	int cnt = 1;
	for (auto it = members.begin(); it != members.end(); ++it)
		cout << cnt++ << ". ID: " << (*it)->getID() << ", " << (*it)->getName()
		<< ", phone num.: " << (*it)->getPhoneNum() << endl;
	cout << "Num. of members: " << members.size() << "\n\n";
}

void printCass(const list<const Cassette *> cassettes) {
	int cnt = 1;
	for (auto it = cassettes.begin(); it != cassettes.end(); ++it)
		cout << cnt++ << ". " << (*it)->getName() << ", " << (*it)->getInfo() << ", " << (*it)->getLeftNum() << "/" << (*it)->getTotalNum() << "\n";
	cout << "Num. of cassettes: " << cassettes.size() << "\n\n";
}

float getDelayOfCas(const Date &usePeriod) {
	int endDay = stoi(usePeriod.getEndDay());
	int endMonth = stoi(usePeriod.getEndMonth());
	int endYear = stoi(usePeriod.getEndYear());

	Date currDate; initCurrDate(currDate);
	int currDay = stoi(currDate.getEndDay());
	int currMonth = stoi(currDate.getEndMonth());
	int currYear = stoi(currDate.getEndYear());

	int passedDays = 0, midMonths = 0;

	if (earlierEndDate(usePeriod, currDate)) {
		if (endYear < currYear) {
			int midYears = currYear - endYear - 1; // num of years between endYear and currYear
			midMonths = 12 * midYears; // num of the months betw. endYear and currYear

			midMonths = midMonths +
				(12 - endMonth); // the rest months to the end year  
			midMonths = midMonths +
				currMonth - 1; // the months before current month
		}
		else if (endMonth < currMonth)
			midMonths = currMonth - endMonth - 1;

		passedDays = midMonths * 30; // 30 = (avarage num)days in a month
		passedDays = passedDays + (30 - endDay) + currDay; /*the rest days of the last day of the period of
																usage to the last days of the month +
																the current day of the current month*/
	}
	return passedDays;
}
