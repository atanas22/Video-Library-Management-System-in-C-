#ifndef  HELPERFUNCS_H
#define HELPERFUNCS_G

#include <iostream>
#include "VidLibManagSys.h"

void cinFix(); 
void choiceCinCheck(int &choice, const int &maxNum);
bool idCinCheck(const int &entID);
Member initMember();
Cassette initCassette(VidLibManagSys &managSys);
void modifMembData(Member *memb);
void modifCassData(Cassette *cas);
void printMembs(const list<const Member *>& members);
void printCass(const list<const Cassette *> cassettes);
float getDelayOfCas(const Date &usePeriod);

#endif

