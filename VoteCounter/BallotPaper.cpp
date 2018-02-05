// Neil Grogan C00205522
#include "BallotPaper.h"


BallotPaper::BallotPaper()
{

}

BallotPaper::BallotPaper(string myArr[][2])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			ballot[i][j] = myArr[i][j];
		}
	}
}

void BallotPaper::setPreference(int n, Candidate c)
{
	for (int i = 0; i < 5; i++)
	{
		if (ballot[i][0] == c.getName())
		{
			ballot[i][1] = n;
		}
	}
}

string BallotPaper::getPreference(int n)
{

	for (int i = 0; i < 5; i++)
	{
		if (ballot[i][1] == std::to_string(n))
		{
			return ballot[i][0];
		}
	}

	return 0 ;
}