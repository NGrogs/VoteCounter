// Neil Grogan C00205522
#pragma once
#include "Candidate.h"
#include "string"

class BallotPaper {


public:

	string ballot[100][2];
	int ballotSize;

	BallotPaper();

	BallotPaper(string myArr[][2], int size);

	void setPreference(int n, Candidate c);

	string getPreference(int n);

};