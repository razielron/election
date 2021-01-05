#include "citizen.h"
#include "election.h"
//#include "district.h"
//#include "districtsArr.h"
//#include "partiesArr.h"

namespace Elections
{
	Citizen::Citizen(istream& in, Election* election): _vote(nullptr) {
		load(in, election);
	}

	Citizen::Citizen(char* id, int yearOfBirth, char* name, District* dis)
		: _yearOfBirth(yearOfBirth) {
		_id = new char[strlen(id) + 1];
		memcpy(_id, id, strlen(id) + 1);
		_name = new char[strlen(name) + 1];
		memcpy(_name, name, strlen(name)+1);
		_dis = dis;
		_dis->appendToVoters(this);
		_vote = nullptr;
	}

	Citizen::~Citizen(){
		delete[] _id;
		delete[] _name;
	}

	ostream& operator<<(ostream& os, const Citizen& cit) {
		os << "--------CITIZEN-START-----------" << endl;
		os << "Name: " << cit.getName() << endl;
		os << "ID: " << cit.getId() << endl;
		os << "Year of birth: " << cit.getYearOfBirth() << endl;
		os << "District: " << cit.getDistrict()->getName() << endl;
		os << "---------CITIZEN-END------------" << endl;
		return os;
	}
	
	bool Citizen::setDistict(District* dis){
		_dis = dis;
		return true; 
	}

	void Citizen::vote(Party* party) {
		_vote = party;
		_dis->addVote();
		party->addVote(_dis);
	}
	
	void Citizen::saveId(ostream& out) const {
		int temp = strlen(_id);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(_id), sizeof(char) * temp);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::save(ostream& out) const {
		int temp = strlen(_name);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(_name), sizeof(char) * temp);
		temp = strlen(_id);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(_id), sizeof(char) * temp);
		out.write(rcastcc(&_yearOfBirth), sizeof(int));
		temp = _dis->getId();
		out.write(rcastcc(&temp), sizeof(int));

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::load(istream& in, Election* election) {
		int idTemp = -1, lengthTemp = 0;
		DistrictsArr* districts = election->getDistricts();

		in.read(rcastc(&lengthTemp), sizeof(int));
		_name = new char[lengthTemp + 1];
		in.read(rcastc(_name), sizeof(char) * lengthTemp);
		_name[lengthTemp] = '\0';
		in.read(rcastc(&lengthTemp), sizeof(int));
		_id = new char[lengthTemp + 1];
		in.read(rcastc(_id), sizeof(char) * lengthTemp);
		_id[lengthTemp] = '\0';
		in.read(rcastc(&_yearOfBirth), sizeof(int));
		in.read(rcastc(&idTemp), sizeof(int));
		_dis = districts->find(idTemp);
		_dis->appendToVoters(this);

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void Citizen::saveVote(ostream& out) const {
		int temp = -1;

		if (_vote) {
			temp = _vote->getId();
		}
		out.write(rcastcc(&temp), sizeof(int));

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::loadVote(istream& in,PartiesArr* parties) {
		int idTemp = -1;

		in.read(rcastc(&idTemp), sizeof(int));
		if (idTemp != -1) {
			_vote = parties->find(idTemp);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}