//Neil Grogan
#pragma once
#include "Candidate.h"

class VoteCounter {

	
public:

	int numVotes = 0;
	string name;

	VoteCounter(string n);

	void addVote();
	int getVotes();

};
