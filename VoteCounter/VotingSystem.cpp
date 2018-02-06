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
	/*for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
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

	}*/


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

	int numCandidates = VoteCounterList.size();
	std::vector<string> EliminatedList;
	string eliminatedCandidate;
	int lowestVotes = VoteCounterList.at(0).getVotes();
	////  loop here  ////
	int n = 2;
	while (numCandidates > 1)
	{
		cout << "------------Round " << n-1 << "------------" << endl << endl;

		// find candidate with lowest votes
		eliminatedCandidate = VoteCounterList.at(0).name;
		lowestVotes = VoteCounterList.at(0).getVotes();
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
			{
			}
			else
			{
				eliminatedCandidate = Viter->name;
				lowestVotes = Viter->getVotes();
			}
		}


		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{	
			// if not already in elimintaed list
			if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
			{
			}
			else if(Viter->getVotes() < lowestVotes)
			{
				lowestVotes = Viter->getVotes();
				eliminatedCandidate = Viter->name;
			}

			// output the names and votes
			if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
			{
			}
			else
			{
				cout << Viter->name << " has " << Viter->getVotes() << " votes" << endl;
			}
		}
		cout << "------------------------" << endl;
		cout << eliminatedCandidate << " has been eliminated" << endl;
		cout << "------------------------" << endl;
		//push to vector
		EliminatedList.push_back(eliminatedCandidate);

		// find ballot where eliminatedCandidate is 1st pref, and assign the *nd pref 
		for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
		{			
			if (EliminatedList.back() == Biter->getPreference(n - 1))
			{
				for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
				{
					// issue
					bool found = true;
					do 
					{
						for (int i = 0; i < CandidateList.size(); i++)
						{
							if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
							{
								// do nothing if their eliminated
							}
							else if (Viter->name == Biter->getPreference(n))
							{
								Viter->addVote();
								found = true;
								break;
							}
						}
					} while (found == false);
				}
			}
		}
		
	//	std::find(EliminatedList.begin(), EliminatedList.end(), Biter->getPreference(n - 1)) != EliminatedList.end()
		


		// output votes
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
			{
			}			
			else
			{
				cout << Viter->name << " has " << Viter->getVotes() << " votes" << endl;
			}
		}
		
		cout << endl;
		numCandidates--;
		n++;
		
		system("pause");

	}// end of while loop

	// print the winner
	cout << endl << "------------Winner is--------------" << endl << endl;

	// calculate the winner
	string winner;
	
	for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
	{
		if (std::find(EliminatedList.begin(), EliminatedList.end(), Viter->name) != EliminatedList.end())
		{
		}
		else
		{
			winner = Viter->name;
		}
	}

	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		if ((iter)->getName() == winner)
		{
			cout << (iter)->getName() << " of the " << (iter)->getParty() << " party, gratz" << endl;
		}
	}

	return 0;
}