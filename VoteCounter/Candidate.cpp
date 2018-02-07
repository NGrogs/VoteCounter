// Neil Grogan C00205522
#include "Candidate.h"

Candidate::Candidate()
{
	
}

Candidate::Candidate(string n, string p)
{
	name = n;
	party = p;
}

void Candidate::setName(string n)
{
	name = n;
}

void Candidate::setParty(string p)
{
	party = p;
}

string Candidate::getName()
{
	return name;
}

string Candidate::getParty()
{
	return party;
}


