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

	Party::Party(istream& in, DistrictsArr* districts, CitizensArr* citArr): _totalElectors(0) {
		load(in, districts, citArr);
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
		out.write(rcastcc(_partySerialNumber), sizeof(int));
		out.write(rcastcc(strlen(_name)), sizeof(int));
		out.write(rcastcc(_name), sizeof(_name));
		out.write(rcastcc(_partyId), sizeof(int));
		out.write(rcastcc(strlen(_candidate->getId())), sizeof(int));
		out.write(rcastcc(_candidate->getId()), sizeof(_candidate->getId()));
		_partyCandidates->save(out);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Party Save issue" << endl;
			exit(-1);
		}
	}

	void Party::load(istream& in,DistrictsArr* districts, CitizensArr* citArr) {
		int temp = 0;
		char* canId;

		in.read(rcastc(temp), sizeof(int));
		if (temp > _partySerialNumber)
			_partySerialNumber = temp;

		in.read(rcastc(temp), sizeof(int));
		_name = new char[temp + 1];
		in.read(rcastc(_name), sizeof(_name));
		in.read(rcastc(_partyId), sizeof(int));
		in.read(rcastc(temp), sizeof(int));
		canId = new char[temp + 1];
		_candidate = citArr->getCit(canId);
		_partyCandidates->load(in, districts, citArr);

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}

	void Party::saveResults(ostream& out) const{
		out.write(rcastcc(_totalElectors), sizeof(int));
		//out.write(rcastcc(_partyId), sizeof(int));
		_partyCandidates->saveResults(out);
	}


	void Party::loadResults(istream& in){
		in.read(rcastc(_totalElectors), sizeof(int));
		_partyCandidates->loadResults(in);
	}
}
	