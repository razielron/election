#pragma once
#include "election.h"


namespace Elections
{
	class NormalElection : public Election
	{
	public:
		NormalElection(int day, int month, int year) : Election(day, month, year) {}
		NormalElection(istream& in) : Election(in) {}
		friend ostream& operator<<(ostream& os, const NormalElection& election);

	};
}