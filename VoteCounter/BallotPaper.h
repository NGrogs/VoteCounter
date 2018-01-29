// Neil Grogan C00205522
#pragma once
#include "Candidate.h"
#include "string"

class BallotPaper {


public:

	string ballot[5][2];

	BallotPaper();

	BallotPaper(string myArr[][5]);

	void setPreference(int n, const Candidate &c);

	string getPreference(int n);



};