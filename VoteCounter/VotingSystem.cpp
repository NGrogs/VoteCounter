// Neil Grogan C00205522

#include "Candidate.h"
#include "BallotPaper.h"
#include "VoteCounter.h"
#include <fstream>
#include "string"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;


int main()
{
	//create vector for candidates
	std::vector<Candidate*> CandidateList;


	cout << "------------THE CANDIDATES------------" << endl << endl;

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


	// print vector of candidates
	vector<Candidate*>::iterator iter = CandidateList.begin();
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++) 
	{
		cout << (*iter)->getName() << " of the ";
		cout << (*iter)->getParty() << " party added" << endl;
	}

	// create the ballot papers //
	cout << endl << "------------ADD BALLOTS------------" << endl << endl; 

	//create a vector for the ballots
	std::vector<BallotPaper*> BallotList;
	BallotPaper *newBallot = new BallotPaper;

	int lineCount = 0;

	while (getline(myfile, line) && line != "END")
	{
		if (lineCount == 5)
		{
			// submit the array
			BallotList.push_back(newBallot);

			// reset lineCount 
			lineCount = 0;
			cout << "ballot added" << endl;
		}
		else 
		{

			// get the candidate
			string newName = line.substr(0, line.find("("));

			// get the vote for that candidate
			string newVote = line.substr(line.find(":") + 1);

			// store in 2d array
			newBallot->ballot[lineCount][0] = newName;
			newBallot->ballot[lineCount][1] = newVote;

			// increment lineCount
			lineCount++;
		}

	} //end while
	myfile.close();

	// TEST print the vector of ballots
	vector<BallotPaper*>::iterator Biter = BallotList.begin();
	for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
	{
		cout << (*Biter)->ballot[0][0] << " " << (*Biter)->ballot[0][1] << endl;
		cout << (*Biter)->ballot[1][0] << " " << (*Biter)->ballot[1][1] << endl;
		cout << (*Biter)->ballot[2][0] << " " << (*Biter)->ballot[2][1] << endl;
		cout << (*Biter)->ballot[3][0] << " " << (*Biter)->ballot[3][1] << endl;
		cout << (*Biter)->ballot[4][0] << " " << (*Biter)->ballot[4][1] << endl;
		cout << endl;
	}



	return 0;
}