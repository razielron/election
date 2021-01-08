#include "partiesArr.h"
namespace Elections
{

	PartiesArr::PartiesArr(istream& in, Election* election) {
		load(in, election);
	}

	void PartiesArr::setPartyTotalElectors() {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->setPartyTotalElectors();
		}
	}

	void PartiesArr::setDistrictWinner() {
		for (int i = 0;i < _logSize;i++) {
			_array[i]->setDistrictWinner();
		}
	}

	Party* PartiesArr::getElectionWinner() {
		Party* winner = nullptr;
		int winnerElectors = 0;
		for (int i = 0;i < _logSize;i++) {
			if (_array[i]->getTotalElectors() > winnerElectors) {
				winnerElectors = _array[i]->getTotalElectors();
				winner = _array[i];
			}
		}
		return winner;
	}

	void PartiesArr::appendParty(Party* party) {
		if (_phySize >= _logSize) {
			resize();
		}
		_array[_logSize++] = party;
	}

	void PartiesArr::appendElectedRep() {
		for (int i = 0;i < _logSize;i++) {
			_array[i]->getPartyCandidates()->addRepresentetives();
		}
	}

	void PartiesArr::printDistrictPartyDetails(int& i, District* dis) {
		if (i > _logSize)
			throw out_of_range("PartiesArr, printDistrictPartyDetails");
		_array[i]->printDistrictPartyDetails(dis);
	}

	void PartiesArr::printResults() const {
		cout << "------------PARTIES-RESULTS-START---------" << endl;
		for (int i = 0; i < _logSize; i++) {
			cout << "Name of Party: " << _array[i]->getName() << endl;
			cout << "Party candidate " << _array[i]->getCandidate()->getName() << endl;
			cout << "Number of Electors: " << _array[i]->getTotalElectors() << endl;
			cout << "Number of Votes: " << _array[i]->getPartyNumOfVotes() << endl << endl;;
		}
		cout << "-------------PARTIES-RESULTS-END---------" << endl;
	}

	void PartiesArr::sortByNumOfElectors() const {
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
	

	void PartiesArr::sortByNumOfElectorsInDistrict(District* dis) {
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

	void PartiesArr::sortByTotalVotes() {
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

	void PartiesArr::addRepresentetives() {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->addRepresentetives();
		}
	}

	void PartiesArr::save(ostream& out) const {
		if (!out || !out.good())
			throw invalid_argument("PartiesArr, save(ostream& out)");

		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			_array[i]->save(out);
		}

		if (!out.good()) {
			throw iostream::failure("Party, save(out)");
		}
	}

	void PartiesArr::load(istream& in, Election* election) {
		if (!in || !in.good() || !election)
			throw invalid_argument("PartiesArr, load, Parameter issues");

		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		try {
			_array = new Party * [_phySize];
			for (int i = 0; i < _phySize; i++) {
				_array[i] = new Party(in, election);
			}
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}

		if (!in.good()) {
			throw iostream::failure("Party, load(in, election)");
		}
	}

}