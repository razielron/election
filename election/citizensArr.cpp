#include "districtsArr.h"
#include "partiesArr.h"
#include "citizensArr.h"
#include "citizen.h"
#include <string>
#include <string.h>
#include <iostream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	CitizensArr::CitizensArr() : _logSize(0), _phySize(1) {
		_citizens = new Citizen*[_phySize];
	}

	CitizensArr::CitizensArr(Citizen* cit) : _logSize(1), _phySize(2) {
		_citizens = new Citizen*[_phySize];
		_citizens[0] = cit;
	}

	CitizensArr::CitizensArr(istream& in, Election* election) {
		load(in, election);
	}

	CitizensArr::CitizensArr(istream& in, CitizensArr* citizens) {
		loadById(in, citizens);
	}

	CitizensArr::~CitizensArr() {
		for (int i = 0;i < _logSize;i++) {
			delete _citizens[i];
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

	void CitizensArr::deleteArrPointer() {
		delete[] _citizens;
	}

	void CitizensArr::appendCitizen(Citizen* cit) {
		if (_phySize <= _logSize) {
			increaseCitizensArr();
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

	void CitizensArr::save(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_citizens[i]->save(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::load(istream& in, Election* election) {
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_citizens = new Citizen* [_phySize];
		for (int i = 0; i < _phySize; i++) {
			_citizens[i] = new Citizen(in, election);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::saveId(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_citizens[i]->saveId(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::loadById(istream& in, CitizensArr* citizens) {
		int tempSize = 0;
		char* tempCitId;
		
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_citizens = new Citizen * [_phySize];

		for (int i = 0; i < _logSize; i++) {
			in.read(rcastc(&tempSize), sizeof(int));
			tempCitId = new char[tempSize + 1];
			in.read(rcastc(tempCitId), sizeof(char) * tempSize);
			tempCitId[tempSize] = '\0';
			_citizens[i] = citizens->getCit(tempCitId);
			delete[] tempCitId;

			//next ex we will implament try&catch
			if (!in.good()) {
				cout << "Citizen load issue" << endl;
				exit(-1);
			}
		}
	}

	void CitizensArr::saveVotes(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_citizens[i]->saveVote(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::loadVotes(istream& in, PartiesArr* parties) {
		for (int i = 0; i < _logSize; i++) {
			_citizens[i]->loadVote(in, parties);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}