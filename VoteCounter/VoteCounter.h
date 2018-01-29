#pragma once
#include "Candidate.h"

class VoteCounter {


public:

	int numVotes = 0;
	VoteCounter(Candidate &c);

	void addVote();
	int getVotes();











};
