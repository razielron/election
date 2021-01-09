#pragma once
#include "CitizensArr.h"
using namespace std;

namespace Elections
{
	class District;
	class CandidatesData
	{
	public:
		District* _dis;
		CitizensArr* _partyCandidates;
		int _numOfVotes;
		int _numOfElectors;

	public:
		CandidatesData(District* dis, CitizensArr* partyCandidates, int numOfVotes, int numOfElectors) :
			_dis(dis), _partyCandidates(partyCandidates), _numOfVotes(numOfVotes), _numOfElectors(numOfElectors) {}

		~CandidatesData() {
			
		}
	};
}