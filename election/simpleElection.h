#pragma once
#include "election.h"


namespace Elections
{
	class SimpleElection : public Election
	{
	public:
		SimpleElection(int day, int month, int year) : Election(day, month, year) {}
		SimpleElection(istream& in) : Election(in) {}
		friend std::ostream& operator<<(std::ostream& os, const SimpleElection& election);

	};
}