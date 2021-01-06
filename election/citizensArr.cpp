#include "citizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{

	CitizensArr::CitizensArr(istream& in, Election* election) {
		load(in, election);
	}

	CitizensArr::CitizensArr(istream& in, CitizensArr* citizens) {
		loadById(in, citizens);
	}

	void CitizensArr::save(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_array[i]->save(out);
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
		_array = new Citizen* [_phySize];
		for (int i = 0; i < _phySize; i++) {
			_array[i] = new Citizen(in, election);
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
			_array[i]->saveId(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::loadById(istream& in, CitizensArr* citizens) {	
		string tempCitId;
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		delete[] _array;
		_array = new Citizen * [_phySize];

		for (int i = 0; i < _logSize; i++) {
			in.read(rcastc(&tempCitId), sizeof(tempCitId));
			_array[i] = citizens->find(tempCitId);

			//next ex we will implament try&catch
			if (!in.good()) {
				cout << "Citizen load issue" << endl;
				exit(-1);
			}
		}
	}

	void CitizensArr::saveVotes(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->saveVote(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Citizen Save issue" << endl;
			exit(-1);
		}
	}

	void CitizensArr::loadVotes(istream& in, PartiesArr* parties) {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->loadVote(in, parties);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}