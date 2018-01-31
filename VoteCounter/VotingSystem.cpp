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

bool isEliminated(Candidate &c)
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
	string myArray[5][5];

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

	// create a voteCounter for each candidate
	std::vector<VoteCounter> VoteCounterList;
	for (int i = 0; i < 5; i++)
	{
		VoteCounter newVoteCounter = VoteCounter(CandidateList.at(i));
		VoteCounterList.push_back(newVoteCounter);
	}


	vector<VoteCounter>::iterator Viter = VoteCounterList.begin();
	bool winnerFound = false;
	int loopNum = 1;
	// get the first candidate to assign lowest votes to
	int lowestVotes = VoteCounterList.begin()->getVotes();
	while (winnerFound == false)
	{
		// loop through the ballotList and add votes for the candidates in the VoteCounterList
		for (Biter = BallotList.begin(); Biter != BallotList.end(); Biter++)
		{
			for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
			{
				// if the names match and they recieved 1st preference & still running
				if ((Biter)->getPreference(loopNum) == (iter)->getName() && (iter)->isEliminated() == false)
				{
					// increment votes for that person
					for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
					{
						if ((Viter)->C.getName() == (iter)->getName())
						{
							(Viter)->addVote();
						}
					}
				}
			}
		}

		// test votes
		cout << endl << "------------Votes after round------------" << endl << endl;
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if (Viter->C.isEliminated() == false)
			{
				cout << (Viter)->C.getName() << " has " << (Viter)->getVotes() << endl;
			}
		}

		// decide who to eliminate (lowest votes)
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if ((Viter)->getVotes() < lowestVotes)
			{
				lowestVotes = (Viter)->getVotes();
			}
		}

		//set that candidate to be eliminated
		for (Viter = VoteCounterList.begin(); Viter != VoteCounterList.end(); Viter++)
		{
			if ((Viter)->getVotes() == lowestVotes)
			{
				for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
				{
					if ((iter)->getName() == (Viter)->C.getName())
					{
						(iter)->eliminate();
						cout << (iter)->getName() << " has been eliminated" << endl;
					}
				}
			}
		}

		system("pause");

		// remove the eliminated candidates from the VoteCounterList
		for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
		{
			if (iter->isEliminated() == true)
			{
				CandidateList.erase(remove_if(CandidateList.begin(), CandidateList.end(), isEliminated), CandidateList.end());
			}
		}
		

		// check for a winner
		int count = 0;
		for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
		{
			if ((iter)->isEliminated() == false)
			{
				count++;
			}
		}
		if (count == 1)
		{
			winnerFound = true;
		}

		// redistribute the votes
		loopNum++;

	}// end of while
	

	// print the winner
	cout << endl << "------------Winner is...------------" << endl << endl;
	for (iter = CandidateList.begin(); iter != CandidateList.end(); iter++)
	{
		if ((iter)->isEliminated() == false)
		{
			cout << (iter)->getName() << " of the ";
			cout << (iter)->getParty() << " party, gratz" << endl;
		}
	}
	



	return 0;
}