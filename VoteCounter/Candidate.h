// Neil Grogan C00205522
#pragma once
#include <iostream>
using namespace std;
using std::string;


class Candidate
{


public:

	std::string name;
	std::string party;
	bool eliminated;

	Candidate();
	Candidate(std::string n, std::string p);

	void setName(std::string n);
	void setParty(std::string p);
	std::string getName();
	std::string getParty();
	void eliminate();
	bool isEliminated();


	


};