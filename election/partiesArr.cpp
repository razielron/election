#include "partiesArr.h"
namespace Elections
{

	PartiesArr::PartiesArr(istream& in, Election* election) {
		load(in, election);
	}

	bool PartiesArr::setPartyTotalElectors() {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->setPartyTotalElectors();
		}
		return true;
	}

	bool PartiesArr::setDistrictWinner() {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->setDistrictWinner();
		}

		return true;
	}

	Party* PartiesArr::getElectionWinner() {
		Party* winner = nullptr;
		int winnerElectors = 0;

		for (int i = 0; i < _logSize; i++) {
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
		for (int i = 0; i < _logSize; i++) {
			_array[i]->getPartyCandidates()->addRepresentetives();
		}
	}

	void PartiesArr::printDistrictPartyDetails(int& i, District* dis) {
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

	void  PartiesArr::sortByNumOfElectors() const {
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

	int totalVotesCompare(Party* p1, Party* p2) {
		if (p1->getPartyCandidates()->getPartyNumOfVotes() <
			p2->getPartyCandidates()->getPartyNumOfVotes()) {
			return -1;
		}

		if (p1->getPartyCandidates()->getPartyNumOfVotes() >
			p2->getPartyCandidates()->getPartyNumOfVotes()) {
			return 1;
		}

		return 0;
	}

	void PartiesArr::sortByTotalVotes() {
		this->sort(this->begin(), this->end(), totalVotesCompare);
	}

	void PartiesArr::addRepresentetives() {
		for (int i = 0; i < _logSize; i++) {
			_array[i]->addRepresentetives();
		}
	}

	void PartiesArr::save(ostream& out) const {
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			_array[i]->save(out);
		}
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "PartyArr Save issue" << endl;
			exit(-1);
		}
	}

	void PartiesArr::load(istream& in, Election* election) {
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new Party* [_phySize];
		for (int i = 0; i < _phySize; i++) {
			_array[i] = new Party(in, election);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "PartyArr load issue" << endl;
			exit(-1);
		}
	}

}