#pragma once
#include "Candidate.h"

class VoteCounter {


public:

	int numVotes = 0;
	Candidate C;

	VoteCounter(Candidate& c);

	void addVote();
	int getVotes();











};
