#include "party.h"
#include "district.h"
#include "election.h"
#include "citizen.h"
#include "citizensArr.h"
#include "partyCandidates.h"
#include <string.h>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	int Party::_partySerialNumber = 0;

	Party::Party(char* name, Citizen* cit) : _totalElectors(0) {
		_name = new char[strlen(name) + 1];
		memcpy(_name, name, strlen(name) + 1);
		_partyId = _partySerialNumber++;
		_candidate = cit;
		_partyCandidates = new PartyCandidates;
	}

	Party::Party(istream& in, DistrictsArr* districts, CitizensArr* citArr) : _totalElectors(0) {
		load(in, districts, citArr);
	}

	Party::~Party() {
		delete[] _name;
		_partyCandidates->~PartyCandidates();
	}

	ostream& operator<<(ostream& os, const Party& party) {
		os << "-----------PARTY-START-----------" << endl;
		os << "Party ID: " << party.getId() << endl;
		os << "Name of Party: " << party.getName() << endl;
		os << "Party candidate: " << endl;
		os << party.getCandidate();
		os << "Represetetives of district: " << endl;
		party.getPartyCandidates()->printPartyCandidates();
		os << "------------PARTY-END-----------" << endl;
		return os;
	}

	bool Party::setCandidate(Citizen* cit) {
		_candidate = cit;
		return true;
	}

	bool Party::setDistrictWinner() {
		return _partyCandidates->setDistrictWinner(this);
	}

	bool Party::setPartyTotalElectors() {
		_totalElectors = _partyCandidates->getPartyTotalElectors(this);
		return true;
	}

	int Party::getPartyNumOfVotes() const {
		return _partyCandidates->getPartyNumOfVotes();
	}

	void Party::appendCandidateToList(District* dis, Citizen* cit) {
		_partyCandidates->appendPartyCandidate(dis, cit);
	}

	void Party::addVote(District* dis) {
		_partyCandidates->addVote(dis);
	}

	void Party::printDistrictPartyDetails(District* dis) const {
		cout << "Party: " << _name << endl;
		cout << "Candidate: " << _candidate->getName() << endl;
		cout << "Electors: " << _partyCandidates->getPartyNumOfElectors(dis) << endl << endl;
	}

	void Party::printResults() const {
		cout << "-----------PARTY-RESULTS-START-----------" << endl;
		cout << "Name of Party: " << _name << endl;
		cout << "Name of Prime Minister Candidate: " << _candidate << endl;
		cout << "Total Electors: " << _totalElectors << endl;
		cout << "Total Votes: " << this->getPartyNumOfVotes() << endl;
		cout << "------------PARTY-RESULTS-END-----------" << endl;
	}

	void Party::addRepresentetives() {
		_partyCandidates->addRepresentetives();
	}

	void Party::save(ostream& out) const {
		int temp;
		const char* tempId;

		out.write(rcastcc(&_partySerialNumber), sizeof(int));
		temp = strlen(_name);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(_name), sizeof(char) * temp);
		out.write(rcastcc(&_partyId), sizeof(int));
		tempId = _candidate->getId();
		temp = strlen(tempId);
		out.write(rcastcc(&temp), sizeof(int));
		out.write(rcastcc(tempId), sizeof(char) * temp);
		_partyCandidates->save(out);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Party Save issue" << endl;
			exit(-1);
		}
	}

	void Party::load(istream& in, DistrictsArr* districts, CitizensArr* citArr) {
		int temp = 0;
		char* canId;

		in.read(rcastc(&temp), sizeof(int));
		if (temp > _partySerialNumber)
			_partySerialNumber = temp;

		in.read(rcastc(&temp), sizeof(int));
		_name = new char[temp + 1];
		in.read(rcastc(_name), sizeof(char) * temp);
		_name[temp] = '\0';
		in.read(rcastc(&_partyId), sizeof(int));
		in.read(rcastc(&temp), sizeof(int));
		canId = new char[temp + 1];
		in.read(rcastc(canId), sizeof(char) * temp);
		canId[temp] = '\0';
		_candidate = citArr->getCit(canId);
		_partyCandidates = new PartyCandidates(in, districts, citArr);

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void Party::saveResults(ostream& out) const {
		_partyCandidates->saveResults(out);
	}


	void Party::loadResults(istream& in) {
		_partyCandidates->loadResults(in);
	}
}