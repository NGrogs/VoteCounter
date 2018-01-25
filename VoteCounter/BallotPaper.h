// Neil Grogan C00205522
#pragma once
#include "Candidate.h"

class BallotPaper {


public:

	BallotPaper();

	void setPreference(int n, const Candidate &c);

	Candidate *getPreference(int n);



};