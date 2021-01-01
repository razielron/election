#include "district.h"
#include "party.h"
#include "partiesArr.h"
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


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

	District::District(istream& in) :_totalVotes(0), _winnerVotes(0), _winner(nullptr) {
		_representatives = new CitizensArr;
		_voters = new CitizensArr;
		load(in);
	}

	District::~District() {
		delete[] _name;
		_representatives->deleteArrPointer();
		_voters->deleteArrPointer();
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


	void District::save(ostream& out) const {
		out.write(rcastcc(&_districtSerialNumber), sizeof(int));
		int temp = strlen(_name);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(_name), sizeof(char) * temp);
		out.write(rcastcc(&_districtId), sizeof(int));		
		out.write(rcastcc(&_numOfRepresentatives), sizeof(int));
		out.write(rcastcc(&_totalVotes), sizeof(int));
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void District::load(istream& in) {
		int tempSize = 0, tempSerial=0;
		
		in.read(rcastc(&tempSerial), sizeof(int));
		if (tempSerial > _districtSerialNumber)
			_districtSerialNumber = tempSerial;
	
		in.read(rcastc(&tempSize), sizeof(int));
		_name = new char[tempSize + 1];
		in.read(rcastc(_name), sizeof(char) * tempSize);
		_name[tempSize] = '\0';
		in.read(rcastc(&_districtId), sizeof(int));
		in.read(rcastc(&_numOfRepresentatives), sizeof(int));
		in.read(rcastc(&_totalVotes), sizeof(int));

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void District::saveResults(ostream& out) const {
		out.write(rcastcc(&_totalVotes), sizeof(int));

		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void District::loadResults(istream& in, CitizensArr* citizens, PartiesArr* parties) {
		int tempSize = 0, tempId=0;
		in.read(rcastc(&_totalVotes), sizeof(int));

		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}

