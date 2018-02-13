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

int main()
{
	//create vector for candidates
	std::vector<Candidate> CandidateList;

	cout << "------------THE CANDIDATES------------" << endl << endl;

	string line;
	//ifstream myfile("votes.txt");
	//ifstream myfile("votes2.txt");
	//ifstream myfile("votes3.txt");
	ifstream myfile("votes4.txt");
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

	cout << endl << "------------ADD BALLOTS------------" << endl << endl;

	//create a vector for the ballots
	std::vector<BallotPaper> BallotList;
	int lineCount = 0;
	string myArray[100][2];
	

	while (getline(myfile, line) && line != "END")
	{
		if (lineCount == CandidateList.size())
		{
			BallotPaper newBallot = BallotPaper(myArray, CandidateList.size());
			BallotList.push_back(newBallot);
			lineCount = 0;
		}
		else
		{
			string newName = line.substr(0, line.find(":"));
			string newVote = line.substr(line.find(":") + 1);
			myArray[lineCount][0] = newName;
			myArray[lineCount][1] = newVote;
			lineCount++;
		}

	} //end while
	myfile.close();

	vector<BallotPaper>::iterator Biter = BallotList.begin();
	std::vector<VoteCounter> VoteCounterList;
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		VoteCounter newVoteCounter(iter->getName());
		VoteCounterList.push_back(newVoteCounter);
	}

	// loop through the ballotlist and distrubute the votes
	vector<VoteCounter>::iterator Viter = VoteCounterList.begin();

	int numCandidates = VoteCounterList.size();
	std::vector<string> EliminatedList;
	string eliminatedCandidate;
	int lowestVotes = VoteCounterList.at(0).getVotes();
	////  loop here  ////
	int n = 2;
	while (numCandidates > 1)
	{
		cout << "------------Round " << n - 1 << "------------" << endl << endl;

		// create a voteCounter for each candidate
		std::vector<VoteCounter> VoteCounterList;
		for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
		{
			if (!(std::find(EliminatedList.begin(), EliminatedList.end(), iter->getName()) != EliminatedList.end()))
			{
				VoteCounter newVoteCounter(iter->getName());
				VoteCounterList.push_back(newVoteCounter);
			}
		}

		for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
		{
			for (int i = 0; i < CandidateList.size(); i++)
			{
				string checkC = Biter->getPreference(i + 1);
				if (!(std::find(EliminatedList.begin(), EliminatedList.end(), checkC) != EliminatedList.end()))
				{
					for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
					{
						if (Viter->name == checkC)
						{
							Viter->addVote();
							break;
						}
					}
					break;
				}
			}
		}

		cout << endl;
		numCandidates--;
		n++;
		system("pause");

		// find candidate with lowest votes
		eliminatedCandidate = VoteCounterList.at(0).name;
		lowestVotes = VoteCounterList.at(0).getVotes();
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if (!(std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end()))
			{
				eliminatedCandidate = Viter->name;
				lowestVotes = Viter->getVotes();
			}
		}

		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			// if not already in elimintaed list
			if (!(std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end()) && Viter->getVotes() < lowestVotes)
			{
				lowestVotes = Viter->getVotes();
				eliminatedCandidate = Viter->name;
			}
			if (!(std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end()))
			{
				cout << Viter->name << " has " << Viter->getVotes() << " votes" << endl;
			}
		}
		cout << endl << "------------------------" << endl;
		cout << eliminatedCandidate << " has been eliminated" << endl;
		cout << "------------------------" << endl << endl;
		EliminatedList.push_back(eliminatedCandidate);

	}// end of while loop

	cout << endl << "------------Winner is--------------" << endl << endl;
	string winner;
	for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
	{
		if (!(std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end()))
		{
			winner = Viter->name;
		}
	}
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		if ((iter)->getName() == winner)
		{
			cout << (iter)->getName() << " of the " << (iter)->getParty() << " party, gratz" << endl << endl;
		}
	}

	return 0;
}