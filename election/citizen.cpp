#include "citizen.h"
#include "district.h"
#include <string.h>
#include <iostream>
using namespace std;
namespace Elections
{

	Citizen::Citizen(): _yearOfBirth(0) {
		_id = nullptr;
		_name = nullptr;
		_dis = nullptr;
		_dis->appendToVoters(this);
		_vote = nullptr;
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
}