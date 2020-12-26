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
			os << citArr[i];
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

	Citizen* CitizensArr::getCit(char* id) {
		for (int i = 0; i < _logSize; i++) {
			if (strcmp(_citizens[i]->getId(), id) == 0)
				return _citizens[i];
		}
		return nullptr;
	}

	Citizen* CitizensArr::getCit(int position) {
		return _citizens[position];
	}
}