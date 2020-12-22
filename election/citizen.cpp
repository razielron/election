#include "citizen.h"
#include "district.h"
#include <string.h>
#include <iostream>
using namespace std;
namespace Elections
{

	Citizen::Citizen(char id[10], int yearOfBirth, char* name, District* dis)
		: _yearOfBirth(yearOfBirth) {
		for (int i = 0; i < 9;i++)
			_id[i] = id[i];
		id[9] = '\0';
		_name = new char[strlen(name) + 1];
		memcpy(_name, name, strlen(name)+1);
		_dis = dis;
		_dis->appendToVoters(this);
		_vote = nullptr;
	}

	
	Citizen::~Citizen(){
		delete[] _name;
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

	void Citizen::printCit() const {
		cout << "--------CITIZEN-START-----------" << endl;
		cout << "Name: " << _name << endl;
		cout << "ID: " << _id << endl;
		cout << "Year of birth: " << _yearOfBirth << endl;
		cout << "District: " << _dis->getName() << endl;
		cout << "---------CITIZEN-END------------" << endl;
	}
}