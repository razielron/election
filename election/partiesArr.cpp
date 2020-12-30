#include "citizensArr.h"
#include "district.h"
#include "districtsArr.h"
#include "partiesArr.h"
#include "PartyCandidates.h"
#include "party.h"
#include <string>
#include <iostream>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	PartiesArr::PartiesArr() : _logSize(0), _phySize(1) {
		_parties = new Party*[_phySize];
	}

	PartiesArr::PartiesArr(istream& in, DistrictsArr* districts, CitizensArr* citizens) {
		load(in, districts, citizens);
	}

	PartiesArr::PartiesArr(Party* party) : _logSize(1), _phySize(2) {
		_parties = new Party*[_phySize];
		_parties[0] = party;
	}

	PartiesArr::~PartiesArr() {
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->~Party();
		}
		delete[] _parties;
	}

	void PartiesArr::operator=(const PartiesArr& partyArr) {
		if (&partyArr != this) {
			delete[] _parties;
			_logSize = _phySize = partyArr.getLogSize();
			_parties = new Party * [_logSize];
			for (int i = 0; i < _logSize; i++) {
				_parties[i] = partyArr[i];
			}
		}
	}

	ostream& operator<<(ostream& os, const PartiesArr& partyArr) {
		for (int i = 0; i < partyArr.getLogSize(); i++) {
			cout << partyArr[i];
		}
		return os;
	}

	void PartiesArr::increasePartiesArr() {
		_phySize *= 2;
		Party** temp = new Party*[_phySize];
		memcpy(temp, _parties, sizeof(Party*)*_logSize);
		delete[] _parties;
		_parties = new Party*[_phySize];
		memcpy(_parties, temp, sizeof(Party*)*_logSize);
		delete[] temp;
	}

	Party* PartiesArr::getParty(int id) {
		for (int i = 0; i < _logSize; i++) {
			if (_parties[i]->getId() == id)
				return _parties[i];
		}
		return nullptr;
	}

	bool PartiesArr::setPartyTotalElectors() {
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->setPartyTotalElectors();
		}
		return true;
	}

	bool PartiesArr::setDistrictWinner() {
		for (int i = 0;i < _logSize;i++) {
			_parties[i]->setDistrictWinner();
		}

		return true;
	}

	Party* PartiesArr::getElectionWinner() {
		Party* winner = nullptr;
		int winnerElectors = 0;

		for (int i = 0;i < _logSize;i++) {
			if (_parties[i]->getTotalElectors() > winnerElectors) {
				winnerElectors = _parties[i]->getTotalElectors();
				winner = _parties[i];
			}
		}
		return winner;
	}

	void PartiesArr::appendParty(Party* party) {
		if (_phySize >= _logSize) {
			PartiesArr::increasePartiesArr();
		}
		_parties[_logSize++] = party;
	}

	void PartiesArr::appendElectedRep() {
		for (int i = 0;i < _logSize;i++) {
			_parties[i]->getPartyCandidates()->addRepresentetives();
		}
	}

	void PartiesArr::printDistrictPartyDetails(int& i, District* dis) {
		_parties[i]->printDistrictPartyDetails(dis);
	}

	void PartiesArr::printResults() const {
		cout << "------------PARTIES-RESULTS-START---------" << endl;
		for (int i = 0; i < _logSize; i++) {
			cout << "Name of Party: " << _parties[i]->getName() << endl;
			cout << "Party candidate " << _parties[i]->getCandidate()->getName() << endl;
			cout << "Number of Electors: " << _parties[i]->getTotalElectors() << endl;
			cout << "Number of Votes: " << _parties[i]->getPartyNumOfVotes() << endl << endl;;
		}
		cout << "-------------PARTIES-RESULTS-END---------" << endl;
	}

	void PartiesArr::sortByNumOfElectors() const {
		Party* temp;
		for (int i = 0; i < _logSize; i++) {
			for (int j = i + 1; j < _logSize; j++) {
				if (_parties[i]->getTotalElectors() < _parties[j]->getTotalElectors()) {
					temp = _parties[i];
					_parties[i] = _parties[j];
					_parties[j] = temp;
				}
			}
		}
	}

	void PartiesArr::sortByNumOfElectorsInDistrict(District* dis) {
		Party* temp;
		for (int i = 0; i < _logSize; i++) {
			for (int j = i + 1; j < _logSize; j++) {
				if (_parties[i]->getPartyCandidates()->getPartyNumOfElectors(dis) <
					_parties[j]->getPartyCandidates()->getPartyNumOfElectors(dis)) {
					temp = _parties[i];
					_parties[i] = _parties[j];
					_parties[j] = temp;
				}
			}
		}
	}

	void PartiesArr::sortByTotalVotes() {
		Party* temp;
		for (int i = 0; i < _logSize; i++) {
			for (int j = i + 1; j < _logSize; j++) {
				if (_parties[i]->getPartyCandidates()->getPartyNumOfVotes() <
					_parties[j]->getPartyCandidates()->getPartyNumOfVotes()) {
					temp = _parties[i];
					_parties[i] = _parties[j];
					_parties[j] = temp;
				}
			}
		}
	}

	void PartiesArr::addRepresentetives() {
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->addRepresentetives();
		}
	}

	void PartiesArr::save(ostream& out) const {
		out.write(rcastcc(_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			_parties[i]->save(out);
		}
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "DistrictArr Save issue" << endl;
			exit(-1);
		}
	}

	void PartiesArr::load(istream& in, DistrictsArr* districts, CitizensArr* citizens) {
		in.read(rcastc(_phySize), sizeof(int));
		_logSize = _phySize;
		_parties = new Party* [_logSize];
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->load(in, districts, citizens);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictArr load issue" << endl;
			exit(-1);
		}
	}

	void PartiesArr::saveResults(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->saveResults(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "PartiesArr Save issue" << endl;
			exit(-1);
		}
	}

	void PartiesArr::loadResults(istream& in) {
		for (int i = 0; i < _logSize; i++) {
			_parties[i]->loadResults(in);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "PartiesArr Load issue" << endl;
			exit(-1);
		}
	}

}