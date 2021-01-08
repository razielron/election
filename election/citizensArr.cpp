#include "citizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{

	CitizensArr::CitizensArr(istream& in, Election* election) : DynamicArr(0) {
		load(in, election);
	}

	CitizensArr::CitizensArr(istream& in, CitizensArr* citizens) : DynamicArr(0) {
		loadById(in, citizens);
	}

	void CitizensArr::save(ostream& out) const {
		if (!out || !out.good()) {
			throw invalid_argument("CitizensArr, save, parameters issue");
		}

		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_array[i]->save(out);
		}

		if (!out.good()) {
			throw iostream::failure("CitizensArr, save, save issue");
		}
	}

	void CitizensArr::load(istream& in, Election* election) {
		if (!in || !in.good()) {
			throw invalid_argument("CitizensArr, load, parametrs issue");
		}

		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		try {
			_array = new Citizen * [_phySize];

			for (int i = 0; i < _phySize; i++) {
				_array[i] = new Citizen(in, election);
			}
		}
		catch (bad_alloc& err) {
			delete[] _array;
			cout << err.what() << endl;
			exit(1);
		}

		if (!in.good()) {
			throw iostream::failure("CitizensArr, load, load didn't work");
		}
	}

	void CitizensArr::saveId(ostream& out) const {
		if (!out || !out.good()) {
			throw invalid_argument("CitizensArr, saveId, parametrs issue");
		}

		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0; i < _logSize; i++) {
			_array[i]->saveId(out);
		}

		if (!out.good()) {
			throw iostream::failure("CitizensArr, saveId, save id didn't work");
		}
	}

	void CitizensArr::loadById(istream& in, CitizensArr* citizens) {
		if (!in || !in.good() || !citizens) {
			throw invalid_argument("CitizensArr, loadById, parametrs issue");
		}

		string tempCitId;
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		delete[] _array;
		try {
			_array = new Citizen * [_phySize];

			for (int i = 0; i < _logSize; i++) {
				in.read(rcastc(&tempCitId), sizeof(tempCitId));
				_array[i] = citizens->find(tempCitId);

				if (!in.good()) {
					throw iostream::failure("CitizensArr, loadById, load by id didn't work");
				}
			}
		}
		catch (bad_alloc& err) {
			delete[] _array;
			cout << err.what() << endl;
			exit(1);
		}
	}

	void CitizensArr::saveVotes(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->saveVote(out);
		}
	}

	void CitizensArr::loadVotes(istream& in, PartiesArr* parties) {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->loadVote(in, parties);
		}
	}
}