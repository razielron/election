#include "district.h"
#include "party.h"
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;

namespace Elections
{
	int District::_districtSerialNumber = 0;

	District::District(char* name, int numOfRepresentatives):
		_numOfRepresentatives(numOfRepresentatives), _winnerVotes(0),
		_totalVotes(0){
		_name = new char[strlen(name) + 1];
		_winner = nullptr;
		memcpy(_name, name, strlen(name) + 1);
		_representatives = new CitizensArr;
		_voters = new CitizensArr;
		_districtId = _districtSerialNumber++;
	}

	District::~District() {
		delete[] _name;
		delete[] _representatives;
		delete[] _voters;
	}

	int District::getPartyRepNumber(int partyVote) {
		int repNum = round(((float)(partyVote) / (float)(_totalVotes) * (float)(_numOfRepresentatives)));
		int occupiedRep = _representatives->getLogSize();
		if ((repNum + occupiedRep) > _numOfRepresentatives)
			return --repNum;
		return repNum;
	}

	bool District::setNumOfRepresentatives(int numOfRepresentatives) {
		if (numOfRepresentatives <= 0)
			return false;
		_numOfRepresentatives = numOfRepresentatives;
		return true;
	}

	bool District::setWinnerVotes(int winnerVotes) {
		_winnerVotes = winnerVotes;
		return true;
	}

	bool District::setWinnerParty(Party* party) {
		_winner = party;
		return true;
	}

	void District::appendToVoters(Citizen* cit) {
		_voters->appendCitizen(cit);
	}

	void District::appendToRepresentetives(Citizen* cit) {
		_representatives->appendCitizen(cit);
	}

	ostream& operator<<(ostream& os, const District& dis) {
		os << "-------------DISTRICT-START------------" << endl;
		os << "District ID: " << dis.getDistrictNumber() << endl;
		os << "Name of district: " << dis.getDistrictNumber() << endl;
		os << "Number of representetive: " << dis.getNumOfRepresentatives() << endl;
		os << "--------------DISTRICT-END-------------" << endl;
		return os;
	}
}