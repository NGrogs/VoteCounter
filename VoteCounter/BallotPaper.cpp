// Neil Grogan C00205522
#include "BallotPaper.h"


BallotPaper::BallotPaper()
{

}

BallotPaper::BallotPaper(string myArr[][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ballot[i][j] = myArr[i][j];

		}
	}
}

void BallotPaper::setPreference(int n, const Candidate &c)
{

}

Candidate *BallotPaper::getPreference(int n)
{
	return 0 ;
}