#ifndef PAIR_H
#define PAIR_H
#include "Date.h"

#define PairStrDate pair<string, Date>
#define Name PairStrDate::first
#define Term PairStrDate::second


class PairComp {
public:
	bool operator()(const PairStrDate& lhs, const PairStrDate& rhs) {
		return earlierEndDate(lhs.Term, rhs.Term);
	}
};

#endif // !PAIR_H


