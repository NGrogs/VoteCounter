// Neil Grogan C00205522

#include "Candidate.h"
#include "BallotPaper.h"
#include "VoteCounter.h"
#include <fstream>
#include "string"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkEliminated(Candidate &c)
{
	if (c.isEliminated() == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	//create vector for candidates
	std::vector<Candidate> CandidateList;


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
		Candidate newCandidate = Candidate(newName, newParty);

		//add candidate to list
		CandidateList.push_back(newCandidate);
	}


	// print vector of candidates
	vector<Candidate>::iterator iter = CandidateList.begin();
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		cout << (iter)->getName() << " of the ";
		cout << (iter)->getParty() << " party added" << endl;
	}

	// create the ballot papers //
	cout << endl << "------------ADD BALLOTS------------" << endl << endl;

	//create a vector for the ballots
	std::vector<BallotPaper> BallotList;
	//BallotPaper newBallot = BallotPaper();

	int lineCount = 0;
	string myArray[5][2];

	while (getline(myfile, line) && line != "END")
	{
		if (lineCount == 5)
		{
			// create newBallot
			BallotPaper newBallot = BallotPaper(myArray);

			// submit the newBallot to list array
			BallotList.push_back(newBallot);

			// reset lineCount 
			lineCount = 0;
		}
		else
		{
			// get the candidate
			string newName = line.substr(0, line.find("("));

			// get the vote for that candidate
			string newVote = line.substr(line.find(":") + 1);

			// store in 2d array
			myArray[lineCount][0] = newName;
			myArray[lineCount][1] = newVote;

			// increment lineCount
			lineCount++;
		}

	} //end while
	myfile.close();

	// print the vector of ballots
	vector<BallotPaper>::iterator Biter = BallotList.begin();
	for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
	{
		cout << "______________" << endl;
		cout << "BALLOT ADDED" << endl;
		cout << "--------------" << endl;
		cout << "+" << (Biter)->ballot[0][0] << " " << (Biter)->ballot[0][1] << endl;
		cout << "+" << (Biter)->ballot[1][0] << " " << (Biter)->ballot[1][1] << endl;
		cout << "+" << (Biter)->ballot[2][0] << " " << (Biter)->ballot[2][1] << endl;
		cout << "+" << (Biter)->ballot[3][0] << " " << (Biter)->ballot[3][1] << endl;
		cout << "+" << (Biter)->ballot[4][0] << " " << (Biter)->ballot[4][1] << endl;
		cout << "______________" << endl;
		cout << endl;

	}


	///// calculate the votes for each candidate /////


	// create a voteCounter for each candidate
	std::vector<VoteCounter> VoteCounterList;
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		VoteCounter newVoteCounter(iter->getName());
		VoteCounterList.push_back(newVoteCounter);
	}
	

	// loop through the ballotlist and distrubute the votes
	vector<VoteCounter>::iterator Viter = VoteCounterList.begin();
	for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
	{
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if (Biter->getPreference(1) == Viter->name)
			{
				Viter->addVote();
			}
		}
	}


	// find candidate with lowest votes
	string eliminatedCandidate;
	int lowestVotes = VoteCounterList.at(0).getVotes();
	for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
	{
		if (Viter->getVotes() < lowestVotes)
		{
			lowestVotes = Viter->getVotes();
			eliminatedCandidate = Viter->name;
		}
		// output the names and votes
		cout << Viter->name << " has " << Viter->getVotes() << " votes" << endl;
	}

	cout << eliminatedCandidate << " has been eliminated" << endl;

	// find ballot where eliminatedCandidate is 1st pref, and assign the 2nd pref 
	for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
	{
		if (Biter->getPreference(1) == eliminatedCandidate)
		{
			for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
			{
				if (Viter->name == Biter->getPreference(2))
				{
					cout << "hi" << endl;
					Viter->addVote();
				}
			}
		}
	}

	// test print (redistrubution works for 1 loop)
	for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
	{
		cout << Viter->name << " has " << Viter->getVotes() << " votes" << endl;
	}




	
	

	// print the winner
	cout << endl << "------------Winner is--------------" << endl << endl;

	// calculate the winner
	string winner = VoteCounterList.at(1).name;
	int mostVotes = VoteCounterList.at(1).getVotes() ;
	for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
	{
		if (Viter->getVotes() > mostVotes)
		{
			mostVotes = Viter->getVotes();
			winner = Viter->name;
		}
	}
	
	// output the winner
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		if ((iter)->getName() == winner)
		{
			cout << (iter)->getName() << " of the ";
			cout << (iter)->getParty() << " party, gratz" << endl;
		}
	}

	

	return 0;
}