#include <iostream>
#include <iomanip>
#include <fstream>

#include "Date.h"
#include "Member.h"
#include "Cassette.h"
#include "Pair.h"
#include "VidLibManagSys.h"
#include "HelperFuncs.h"

using namespace std;

int main() {
	Date currDate; initCurrDate(currDate);
	
	VidLibManagSys managSys;
	managSys.loadData();
	int choice = 0;
	do {
		cout << "1. Add/delete members/cassettes\n";
		cout << "2. Search members/cassettes\n";
		cout << "3. Show all cassettes/members\n";
		cout << "4. Rent/return cassettes\n";
		cout << "5. Show out of date rented cassettes " << endl;
		cout << "6. Exit and save\n\n";
		cout << "Enter choice(1 - 6): "; cin >> choice; choiceCinCheck(choice, 6);
		cout << endl;

		if (choice == 1) { // 1
			int choice = 0;
			do {
				cout << "1. Add member\n";
				cout << "2. Delete member\n";
				cout << "3. Add cassette\n";
				cout << "4. Delete cassette\n";
				cout << "5. back\n\n";
				cout << "Enter choice(1 - 5): "; cin >> choice; choiceCinCheck(choice, 5);
				cout << "\n";
				if (choice == 1) { // 1.1
					Member m = initMember();
					managSys.addNewMember(m.getName(), m.getPhoneNum(), m.getAddr(), m.getMonthsCardValid());
				}
				else if (choice == 2) { // 1.2
					int ID;
					cout << "Enter ID of member :"; cin >> ID;
					cout << endl;
					bool flag = idCinCheck(ID);
					if (!flag) {
						cout << endl; continue;
					}
					 managSys.deleteMember(ID);
				}
				else if (choice == 3) { // 1.3
					Cassette c = initCassette(managSys);
					if (c.getTotalNum() == 0) 
						cout << "\nFailed to add new cassette - " 
							    "this cassette is already added: "<< c.getName() << "\n\n";
					else managSys.addNewCassette(c.getName(), c.getInfo(), c.getTotalNum());
				}
				else if (choice == 4) { // 1.4
					string name;
					cout << "Enter name of cassette :";  getline(cin, name);
					 managSys.deleteCassette(name);
				}
				else if (choice == 5) // 1.5
					cout << "--------------\n\n";
			} while (choice != 5);
		}

		else if (choice == 2) { // 2
			int choice = 0;
			do {
				cout << "1. Search member through ID\n";
				cout << "2. Search member through name\n";
				cout << "3. Search cassette\n";
				cout << "4. back\n\n";
				cout << "Enter choice(1 - 4): "; cin >> choice; choiceCinCheck(choice, 4);
				cout << endl;

				if (choice == 1) { // 2.1
					int ID;
					cout << "Enter ID: "; cin >> ID;
					cout << endl;
					bool flag = idCinCheck(ID); 
					if (!flag) {
						cout << endl; continue;
					}
					Member *memb = managSys.searchMemberID(ID);
					if (memb->getName() == "") continue;
					modifMembData(memb);
				}
				else if (choice == 2) { //2.2
					string name;
					cout << "Enter name: ";
					getline(cin, name); cout << "\n";

					list<const Member *> members = managSys.searchMembersName(name);
					if (members.size() == 0) {
						cout << "There are no members with name \"" << name << "\"\n\n";
						continue;
					}
					int n = members.size() + 1;
					int choice = 0;
					do {
						printMembs(members);
						cout << "Enter ID or " << 0 << "(back): ";
						cin >> choice;
						cout << endl;
						bool flag = idCinCheck(choice);
						if (!flag) continue;
						if (choice == 0) continue;

						Member *memb = managSys.searchMemberID(choice);
						if (memb->getName() == "") continue;
						modifMembData(memb);
					} while (choice != 0);
				}
				else if (choice == 3) { // 2.3
					cout << "Enter name of cassete :";
					string name;
					getline(cin, name);

					Cassette* cas = managSys.searchCassetteName(name);
					if (cas->getName() == "") continue;
					modifCassData(cas);
				}
				else if (choice == 4) // 2.4
					cout << "--------------\n\n";
			} while (choice != 4);
		}

		else if (choice == 3) { // 3
			int choice = 0;
			do {
				cout << "1. Show all members\n";
				cout << "2. Show all cassettes\n";
				cout << "3. Back\n\n";
				cout << "Enter choice(1 - 3): "; 
				cin >> choice; choiceCinCheck(choice, 3); cout << endl;
				if (choice == 1) { // 3.1
					list<const Member*> members = managSys.allMembers();
					int choice = 0;
					do {
						printMembs(members);
						cout << "Enter ID of a memb. or " << 0 << "(back)   : ";
						cin >> choice;
						cout << endl;
						bool flag = idCinCheck(choice);
						if (!flag) continue;
						if (choice == 0) {
							cout << "--------------\n\n";
							continue;
						}
						if (managSys.checkID(choice))
							modifMembData(managSys.searchMemberID(choice));
					} while (choice != 0);
				}
				else if (choice == 2) { // 3.2
					list<const Cassette*> cassettes = managSys.allCassettes();
					string choice;
					do {
						printCass(cassettes);
						cout << "Enter name of a cass. or " << 0 << "(back) : ";
						getline(cin, choice);
						if (choice == to_string(0)) {
							cout << "\n--------------\n\n";
							continue;
						}
						if (managSys.checkCassName(choice))
							modifCassData(managSys.searchCassetteName(choice));
					} while (choice != to_string(0));
				}
				else if (choice == 3) // 3.3
					cout << "--------------\n\n";

			} while (choice != 3);
		}
		else if (choice == 4) { // 4
			int choice = 0, ID;
			string casName;
			do {
				cout << "1. Rent cassette\n"; 
				cout << "2. Return cassette\n"; 
				cout << "3. Back\n";
				cout << "Enter choice(1 - 3): "; 
				cin >> choice; choiceCinCheck(choice, 3);
				cout << endl;

				if (choice == 1) { // 4.1
					cout << "Enter ID of member: "; cin >> ID;
					bool flag = idCinCheck(ID);
					if (!flag) { cout << endl; continue; }

					if (!managSys.searchIDNoComm(ID)) {
						cout << "There is no member with ID \"" << ID << "\"\n\n";
						continue;
					}

					cout << "Enter name of cassette: ";
					getline(cin, casName);
					if (!managSys.searchCassetteNoComm(casName)) {
						cout << "\nFailed to rent a cassette, there is no cassete with name \"" << casName << "\"\n\n";
						continue;
					}
					cout << endl;
					managSys.rentCassette(ID, casName);
				}
				else if (choice == 2) {// 4.2
					cout << "Enter ID of member: "; cin >> ID;
					bool flag = idCinCheck(ID);
					if (!flag) { cout << endl; continue; }

					if (!managSys.searchIDNoComm(ID)) {
						cout << "There is no member with ID \"" << ID << "\"\n\n";
						continue;
					}

					cout << "Enter name of cassette: ";
					getline(cin, casName);
					if (!managSys.searchCassetteNoComm(casName)) {
						cout << "\nFailed to return a cassette, there is no cassete with name \"" << casName << "\"\n\n";
						continue;
					}
					cout << endl;
					managSys.returnCassette(ID, casName);
				}
				else if (choice == 3) // 4.3
					cout << "--------------\n\n";
			} while (choice != 3);
		}
		else if (choice == 5) {// 5
			managSys.showRentedCassOutOfDate();
			cout << "1. Back\n";
			int choice = 0;
			cout << "Enter choice(1 - 1): "; cin >> choice; 
			choiceCinCheck(choice, 1);
			
			cout << "\n--------------\n\n";
		}
		else if (choice == 6) {
			managSys.saveData();
		}
	} while (choice != 6);

}

// end of main