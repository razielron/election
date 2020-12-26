#pragma once
#include "election.h"
#include <iostream>
using namespace std;

namespace Elections
{
	class NormalElection : public Election
	{
	public:
		NormalElection(int day, int month, int year) : Election(day, month, year) {}

	public:
		//prints all uniform district's election results
		//AND prints all divided district's election results
		void printResults() const;
	};
}