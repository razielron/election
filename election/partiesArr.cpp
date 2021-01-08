#include "partiesArr.h"
namespace Elections
{

	PartiesArr::PartiesArr(istream& in, Election* election) {
		try {
			load(in, election);
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	bool PartiesArr::setPartyTotalElectors() {
		try {
			for (int i = 0; i < _logSize; i++) {
				_array[i]->setPartyTotalElectors();
			}
			return true;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	bool PartiesArr::setDistrictWinner() {
		try {
			for (int i = 0;i < _logSize;i++) {
				_array[i]->setDistrictWinner();
			}

			return true;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	Party* PartiesArr::getElectionWinner() {
		Party* winner = nullptr;
		int winnerElectors = 0;
		try {
			for (int i = 0;i < _logSize;i++) {
				if (_array[i]->getTotalElectors() > winnerElectors) {
					winnerElectors = _array[i]->getTotalElectors();
					winner = _array[i];
				}
			}
			return winner;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::appendParty(Party* party) {
		try {
			if (_phySize >= _logSize) {
				resize();
			}
			_array[_logSize++] = party;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::appendElectedRep() {
		try {
			for (int i = 0;i < _logSize;i++) {
				_array[i]->getPartyCandidates()->addRepresentetives();
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::printDistrictPartyDetails(int& i, District* dis) {
		try {
			_array[i]->printDistrictPartyDetails(dis);
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::printResults() const {
		try {
			cout << "------------PARTIES-RESULTS-START---------" << endl;
			for (int i = 0; i < _logSize; i++) {
				cout << "Name of Party: " << _array[i]->getName() << endl;
				cout << "Party candidate " << _array[i]->getCandidate()->getName() << endl;
				cout << "Number of Electors: " << _array[i]->getTotalElectors() << endl;
				cout << "Number of Votes: " << _array[i]->getPartyNumOfVotes() << endl << endl;;
			}
			cout << "-------------PARTIES-RESULTS-END---------" << endl;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void  PartiesArr::sortByNumOfElectors() const {
		try {
			Party* temp;
			for (int i = 0; i < _logSize; i++) {
				for (int j = i + 1; j < _logSize; j++) {
					if (_array[i]->getTotalElectors() < _array[j]->getTotalElectors()) {
						temp = _array[i];
						_array[i] = _array[j];
						_array[j] = temp;
					}
				}
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::sortByNumOfElectorsInDistrict(District* dis) {
		try {
			Party* temp;
			for (int i = 0; i < _logSize; i++) {
				for (int j = i + 1; j < _logSize; j++) {
					if (_array[i]->getPartyCandidates()->getPartyNumOfElectors(dis) <
						_array[j]->getPartyCandidates()->getPartyNumOfElectors(dis)) {
						temp = _array[i];
						_array[i] = _array[j];
						_array[j] = temp;
					}
				}
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::sortByTotalVotes() {
		try {
			Party* temp;
			for (int i = 0; i < _logSize; i++) {
				for (int j = i + 1; j < _logSize; j++) {
					if (_array[i]->getPartyCandidates()->getPartyNumOfVotes() <
						_array[j]->getPartyCandidates()->getPartyNumOfVotes()) {
						temp = _array[i];
						_array[i] = _array[j];
						_array[j] = temp;
					}
				}
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::addRepresentetives() {
		try {
			for (int i = 0; i < _logSize; i++) {
				_array[i]->addRepresentetives();
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void PartiesArr::save(ostream& out) const {
		if (!out || !out.good())
			throw("PartiesArr, save(ostream& out), parameter issues");
		try {
			out.write(rcastcc(&_logSize), sizeof(int));
			for (int i = 0;i < _logSize;i++) {
				_array[i]->save(out);
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}
		if (!out.good()) {
			throw("Party, save(out)");
		}
	}

	void PartiesArr::load(istream& in, Election* election) {
		if (!in || !in.good() || !election)
			throw("PartiesArr, load, Parameter issues");
		try {
			in.read(rcastc(&_phySize), sizeof(int));
			_logSize = _phySize;
			_array = new Party * [_phySize];
			for (int i = 0; i < _phySize; i++) {
				_array[i] = new Party(in, election);
			}
		}
		catch (const char* err) {
			cout << err << endl;
		}

		if (!in.good()) {
			throw("Party, load(in, election)");
		}
	}

}