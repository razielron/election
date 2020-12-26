#pragma once
#include "election.h"
#include <iostream>
using namespace std;

namespace Elections
{
	class SimpleElection : public Election
	{
	public:
		SimpleElection(int day, int month, int year) : Election(day, month, year) {}

	public:
		void printResults() const;
	};
}