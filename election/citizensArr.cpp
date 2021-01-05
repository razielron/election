#include "citizensArr.h"

namespace Elections
{

	CitizensArr::CitizensArr(istream& in, Election* election) {
		load(in, election);
	}

	CitizensArr::CitizensArr(istream& in, CitizensArr* citizens) {
		loadById(in, citizens);
	}

	
	/*ostream& operator<<(ostream& os,const DynamicArr<Citizen*> citArr) {
		for (int i = 0; i < citArr.size(); i++) {
			os << citArr[i];
		}
		return os;
	}*/

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
		int tempSize = 0;
		char* tempCitId;
		
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new Citizen * [_phySize];

		for (int i = 0; i < _logSize; i++) {
			in.read(rcastc(&tempSize), sizeof(int));
			tempCitId = new char[tempSize + 1];
			in.read(rcastc(tempCitId), sizeof(char) * tempSize);
			tempCitId[tempSize] = '\0';
			_array[i] = citizens->find(tempCitId);
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