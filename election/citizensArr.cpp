#include "citizensArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{

	CitizensArr::CitizensArr(istream& in, Election* election) : DynamicArr(in) {
		load(in, election);
	}

	CitizensArr::CitizensArr(istream& in, CitizensArr* citizens) : DynamicArr(in) {
		loadById(in, citizens);
	}

	void CitizensArr::save(ostream& out) const {
		if (!out || !out.good()) {
			throw invalid_argument("CitizensArr, save, parameters issue");
		}

		out.write(rcastcc(&_logSize), sizeof(int));
		if (!out.good()) {
			throw iostream::failure("CitizensArr, save, save issue");
		}

		for (int i = 0; i < _logSize; i++) {
			_array[i]->save(out);
		}
	}

	void CitizensArr::load(istream& in, Election* election) {
		if (!in || !in.good()) {
			throw invalid_argument("CitizensArr, load, parametrs issue");
		}

		try {
			for (int i = 0; i < this->capacity(); i++) {
				push_back(new Citizen(in, election));
			}
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
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
		int tempSize, len;

		try {
			for (int i = 0; i < this->capacity(); i++) {
				tempCitId = StringLoader::loadString(in);
				push_back(citizens->find(tempCitId));

				if (!in.good()) {
					throw iostream::failure("CitizensArr, loadById, load by id didn't work");
				}
			}
		}
		catch (bad_alloc& err) {
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