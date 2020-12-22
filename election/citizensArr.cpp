#include "citizensArr.h"
#include "citizen.h"
#include <string.h>
#include <iostream>
using namespace std;

namespace Elections
{
	CitizensArr::CitizensArr() : _logSize(0), _phySize(1) {
		_citizens = new Citizen*[_phySize];
	}

	CitizensArr::CitizensArr(Citizen* cit) : _logSize(1), _phySize(2) {
		_citizens = new Citizen*[_phySize];
		_citizens[0] = cit;
	}

	CitizensArr::~CitizensArr() {
		for (int i = 0;i < _logSize;i++) {
			_citizens[i]->~Citizen();
		}
		delete[] _citizens;
	}

	void CitizensArr::operator=(const CitizensArr& citArr) {
		if (&citArr != this) {
			delete[] _citizens;
			_logSize = _phySize = citArr.getLogSize();
			_citizens = new Citizen * [_logSize];
			for (int i = 0;i < _logSize;i++) {
				_citizens[i] = citArr[i];
			}
		}
	}

	ostream& operator<<(ostream& os,const CitizensArr& citArr) {
		for (int i = 0; i < citArr.getLogSize(); i++) {
			os << "--------CITIZEN-START-----------" << endl;
			os << "Name: " << citArr[i]->getName() << endl;
			os << "ID: " << citArr[i]->getId() << endl;
			os << "Year of birth: " << citArr[i]->getYearOfBirth() << endl;
			os << "District: " << citArr[i]->getDistrict() << endl;
			os << "---------CITIZEN-END------------" << endl;
		}
		return os;
	}



	void CitizensArr::increaseCitizensArr() {
		_phySize *= 2;
		Citizen** temp = new Citizen*[_phySize];
		memcpy(temp, _citizens, sizeof(Citizen*)*_logSize);
		delete[] _citizens;
		_citizens = new Citizen*[_phySize];
		memcpy(_citizens, temp, sizeof(Citizen*)*_logSize);
		delete[] temp;
	}

	void CitizensArr::appendCitizen(Citizen* cit) {
		if (_phySize <= _logSize) {
			CitizensArr::increaseCitizensArr();
		}
		_citizens[_logSize++] = cit;
	}

	Citizen* CitizensArr::getCit(char id[10]) {
		bool flag;
		for (int i = 0; i < _logSize; i++) {
			flag = true;
			for (int j = 0; j < 9 && flag; j++) {
				if (_citizens[i]->getId()[j] != id[j])
					flag = false;
			}
			if (flag)
				return _citizens[i];
		}
		return nullptr;
	}

	Citizen* CitizensArr::getCit(int position) {
		return _citizens[position];
	}
	
	void CitizensArr::printCitizens() const {
		for (int i = 0; i < _logSize; i++) {
			_citizens[i]->printCit();
		}
	}
}