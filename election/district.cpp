#include "district.h"

namespace Elections
{
	int District::_districtSerialNumber = 0;

	District::District(string name, int numOfRepresentatives):
		_name(name), _numOfRepresentatives(numOfRepresentatives), _winnerVotes(0),
		_totalVotes(0){
		_winner = nullptr;
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
		delete[] _representatives->getArr();
		delete[] _voters->getArr();
	}

	int District::getPartyRepNumber(int partyVote) {
		int repNum = round(((float)(partyVote) / (float)(_totalVotes) * (float)(_numOfRepresentatives)));
		int occupiedRep = _representatives->size();
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
		_voters->push_back(cit);
	}

	void District::appendToRepresentetives(Citizen* cit) {
		_representatives->push_back(cit);
	}

	ostream& operator<<(ostream& os, const District& dis) {
		os << "-------------DISTRICT-START------------" << endl;
		os << "District ID: " << dis.getId() << endl;
		os << "Name of district: " << dis.getId() << endl;
		os << "Number of representetive: " << dis.getNumOfRepresentatives() << endl;
		os << "--------------DISTRICT-END-------------" << endl;
		return os;
	}

	void District::save(ostream& out) const {
		out.write(rcastcc(&_districtSerialNumber), sizeof(int));
		out.write(rcastcc(_name), sizeof(string));
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
		in.read(rcastc(_name), sizeof(string));
		in.read(rcastc(&_districtId), sizeof(int));
		in.read(rcastc(&_numOfRepresentatives), sizeof(int));
		in.read(rcastc(&_totalVotes), sizeof(int));

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}

