// Neil Grogan C00205522
#pragma once
#include "Candidate.h"
#include "string"

class BallotPaper {


public:

	string ballot[5][2];

	BallotPaper();

	BallotPaper(string myArr[][2]);

	void setPreference(int n, Candidate c);

	string getPreference(int n);



};