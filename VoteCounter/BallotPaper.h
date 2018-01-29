// Neil Grogan C00205522
#pragma once
#include "Candidate.h"

class BallotPaper {


public:

	string ballot[5][5];

	BallotPaper();

	BallotPaper(string myArr[][5]);

	void setPreference(int n, const Candidate &c);

	Candidate *getPreference(int n);



};