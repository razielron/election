#include "party.h"
#include "district.h"
#include "election.h"
#include "citizen.h"
#include "partyCandidates.h"
#include <string.h>

namespace Elections
{
	int Party::_partySerialNumber = 0;

	Party::Party(char* name, Citizen* cit): _totalElectors(0) {
		_name = new char[strlen(name) + 1];
		memcpy(_name, name, strlen(name) + 1);
		_partyId = _partySerialNumber++;
		_candidate = cit;
		_partyCandidates = new PartyCandidates;
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

	int Party::getPartyNumOfVotes() {
		int sumOfVotes = 0;
		return _partyCandidates->getPartyNumOfVotes();
	}

	void Party::appendCandidateToList(District* dis, Citizen* cit) {
		_partyCandidates->appendPartyCandidate(dis, cit);
	}

	void Party::addVote(District* dis){
		_partyCandidates->addVote(dis);
	}


	void Party::printParty() const {
		cout << "-----------PARTY-START-----------" << endl;
		cout << "Party ID: " << _partyId << endl;
		cout << "Name of Party: " << _name << endl;
		cout << "Party candidate: " << endl;
		_candidate->printCit();
		cout << "Represetetives of district: " << endl;
		_partyCandidates->printPartyCandidates();
		cout << "------------PARTY-END-----------" << endl;
	}
	
	
	void Party::printResults() const {
		cout << "-----------PARTY-RESULTS-START-----------" << endl;
		cout << "Name of Party: " << _name << endl;
		cout << "Name of Prime Minister Candidate: " << _candidate << endl;
		cout << "Total Electors: " << _totalElectors << endl;
		cout << "Total Votes: " << _partyCandidates->getPartyNumOfVotes() << endl;
		cout << "------------PARTY-RESULTS-END-----------" << endl;
	}

	void Party::addRepresentetives() {
		_partyCandidates->addRepresentetives();
	}
	
}