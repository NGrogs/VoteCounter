//Neil Grogan C00205522
#include "VoteCounter.h"

VoteCounter::VoteCounter(string n)
{
	numVotes = 0;
	name = n;
}

void VoteCounter::addVote()
{
	numVotes++;
}

int VoteCounter::getVotes()
{
	return numVotes;
}

