//Neil Grogan C00205522
#include "VoteCounter.h"

VoteCounter::VoteCounter(Candidate &c)
{
	numVotes = 0;
}

void VoteCounter::addVote()
{
	numVotes++;
}

int VoteCounter::getVotes()
{
	return numVotes;
}

