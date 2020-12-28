#include "citizen.h"
#include "district.h"
#include "districtsArr.h"
#include "partiesArr.h"
#include <string>
#include <iostream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{

	Citizen::Citizen(): _yearOfBirth(0) {
		_id = nullptr;
		_name = nullptr;
		_dis = nullptr;
		_dis->appendToVoters(this);
		_vote = nullptr;
	}

	Citizen::Citizen(istream& in, DistrictsArr* districts): _vote(nullptr) {
		load(in, districts);
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
		out.write(rcastcc(strlen(_id)), sizeof(int));
		out.write(rcastcc(_id), sizeof(_id));

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::save(ostream& out) const {
		out.write(rcastcc(strlen(_name)), sizeof(int));
		out.write(rcastcc(_name), sizeof(_name));
		out.write(rcastcc(strlen(_id)), sizeof(int));
		out.write(rcastcc(_id), sizeof(_id));
		out.write(rcastcc(_yearOfBirth), sizeof(int));
		out.write(rcastcc(_dis->getDistrictNumber()), sizeof(int));

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::load(istream& in, DistrictsArr* districts) {
		int idTemp = -1, lengthTemp = 0;

		in.read(rcastc(lengthTemp), sizeof(int));
		_name = new char[lengthTemp + 1];
		in.read(rcastc(_name), sizeof(_name));
		in.read(rcastc(lengthTemp), sizeof(int));
		_id = new char[lengthTemp + 1];
		in.read(rcastc(_id), sizeof(_id));
		in.read(rcastc(_yearOfBirth), sizeof(int));
		in.read(rcastc(idTemp), sizeof(int));
		_dis = districts->getDistrict(idTemp);
		_dis->appendToVoters(this);

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void Citizen::saveResults(ostream& out) const {
		if (_vote) {
			out.write(rcastcc(_vote->getId()), sizeof(int));
		}
		else {
			out.write(rcastcc(-1), sizeof(int));
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void Citizen::loadResults(istream& in, PartiesArr* parties) {
		int idTemp = -1;

		in.read(rcastc(idTemp), sizeof(int));
		if (idTemp != -1) {
			_vote = parties->getParty(idTemp);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}