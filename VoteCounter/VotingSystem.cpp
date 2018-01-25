// Neil Grogan C00205522

#include "Candidate.h"
#include "BallotPaper.h"
#include "VoteCounter.h"
#include <fstream>
#include "string"
#include <cstdlib>
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
	//create vector for candidates
	std::vector<Candidate*> CandidateList;



	string line;
	ifstream myfile("votes.txt");
	while (getline(myfile, line) && line != "")
	{
		// create the candidates
		string newName = line.substr(0, line.find("("));
		int start = line.find("(");
		int end = line.find(")") - start + 1;
		string newParty = line.substr(start, end);
		Candidate *newCandidate = new Candidate(newName, newParty);

		//add candidate to list
		CandidateList.push_back(newCandidate);
	}

	myfile.close();

	// print vector of candidates
	vector<Candidate*>::iterator iter = CandidateList.begin();
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++) 
	{
		cout << (*iter)->getName();
		cout << (*iter)->getParty() << endl;
	}





	return 0;
}