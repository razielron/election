#include "district.h"
#include "party.h"
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;

namespace Elections
{
	int District::_districtSerialNumber = 0;

	District::District(int type, char* name, int numOfRepresentatives):
		_type(type), _numOfRepresentatives(numOfRepresentatives), _winnerVotes(0),
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

	void District::printDistrict() const {
		cout << "-------------DISTRICT-START------------" << endl;
		cout << "District ID: " << _districtId << endl;
		cout << "Name of district: " << _name << endl;
		cout << "Number of representetive: " << _numOfRepresentatives << endl;
		cout << "--------------DISTRICT-END-------------" << endl;
	}

	void District::printResults() {
		cout << "-------------DISTRICT-RESULTS-START------------" << endl;
		cout << "Name of district: " << _name << endl;
		cout << "Number of representetive: " << _numOfRepresentatives << endl;
		cout << "District candidate winner: " << _winner->getCandidate()->getName() << endl;
		cout << "District voters Percentage: " << getVotersPresentage() << "%" << endl;
		cout << "--------------DISTRICT-RESULTS-END-------------" << endl;
	}

}