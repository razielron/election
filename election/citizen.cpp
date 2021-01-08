#include "citizen.h"
#include "election.h"

namespace Elections
{
	Citizen::Citizen(istream& in, Election* election): _vote(nullptr) {
		load(in, election);
	}

	Citizen::Citizen(string id, int yearOfBirth, string name, District* dis)
		: _yearOfBirth(yearOfBirth) {
		if (_yearOfBirth < 1 || id.size() != 9 || !dis) {
			throw CitizenException(id);
		}

		_id = id;
		_name = name;
		_dis = dis;
		_vote = nullptr;
		_dis->appendToVoters(this);
	}

	ostream& operator<<(ostream& os, const Citizen& cit) {
		if (!cit) {
			throw invalid_argument("Citizen, operator<<, parameter issue");
		}

		os << "--------CITIZEN-START-----------" << endl;
		os << "Name: " << cit.getName() << endl;
		os << "ID: " << cit.getId() << endl;
		os << "Year of birth: " << cit.getYearOfBirth() << endl;
		os << "District: " << cit.getDistrict()->getName() << endl;
		os << "---------CITIZEN-END------------" << endl;

		return os;
	}
	
	bool Citizen::setDistict(District* dis){
		if (!dis) {
			throw invalid_argument("Citizen, setDistict, parameter issue");
		}

		_dis = dis;
		return true; 
	}

	void Citizen::vote(Party* party) {
		if (!party) {
			throw invalid_argument("Citizen, vote, parameter issue");
		}

		_vote = party;
		_dis->addVote();
		party->addVote(_dis);
	}
	
	void Citizen::saveId(ostream& out) const {
		if (!out || !out.good()) {
			throw invalid_argument("Citizen, saveId, parameter issue");
		}

		out.write(rcastcc(&_id), sizeof(_id));

		if (!out.good()) {
			throw iostream::failure("Citizen, saveId, save didn't work");
		}
	}

	void Citizen::save(ostream& out) const {
		int temp;
		if (!out || !out.good()) {
			throw invalid_argument("Citizen, save, parameter issue");
		}

		out.write(rcastcc(&_name), sizeof(_name));
		out.write(rcastcc(&_id), sizeof(_id));
		out.write(rcastcc(&_yearOfBirth), sizeof(int));

		temp = _dis->getId();

		out.write(rcastcc(&temp), sizeof(int));

		if (!out.good()) {
			throw iostream::failure("Citizen, save, save didn't work");
		}
	}

	void Citizen::load(istream& in, Election* election) {
		int idTemp = -1, lengthTemp = 0;

		if (!in || !in.good() || !election) {
			throw invalid_argument("Citizen, load, parameter issue");
		}

		DistrictsArr* districts = election->getDistricts();

		in.read(rcastc(&_name), sizeof(_name));
		in.read(rcastc(&_id), sizeof(_id));
		in.read(rcastc(&_yearOfBirth), sizeof(int));
		in.read(rcastc(&idTemp), sizeof(int));

		if (!in.good()) {
			throw iostream::failure("Citizen, load, load didn't work");
		}

		_dis = districts->find(idTemp);
		_dis->appendToVoters(this);

	}

	void Citizen::saveVote(ostream& out) const {
		int temp = -1;

		if (!out || !out.good()) {
			throw invalid_argument("Citizen, saveVote, parameter issue");
		}

		if (_vote) {
			temp = _vote->getId();
		}

		out.write(rcastcc(&temp), sizeof(int));
			
		if (!out.good()) {
			throw iostream::failure("Citizen, saveVote, save vote didn't work");
		}
	}

	void Citizen::loadVote(istream& in, PartiesArr* parties) {
		int idTemp = -1;

		if (!in || !in.good() || !parties) {
			throw invalid_argument("Citizen, loadVote, parameters issue");
		}

		in.read(rcastc(&idTemp), sizeof(int));
		if (idTemp != -1) {
			_vote = parties->find(idTemp);
		}

		if (!in.good()) {
			throw iostream::failure("Citizen, loadVote, load vote didn't work");
		}
	}
}