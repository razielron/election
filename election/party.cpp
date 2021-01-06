#include "party.h"
#include "partyCandidates.h"
#include "election.h"

namespace Elections
{
	int Party::_partySerialNumber = 0;

	Party::Party(string name, Citizen* cit) : _name(name), _totalElectors(0) {
		_partyId = _partySerialNumber++;
		_candidate = cit;
		_partyCandidates = new PartyCandidates;
	}

	Party::Party(istream& in, Election* election) : _totalElectors(0) {
		load(in, election);
	}

	Party::~Party() {
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
		const string tempId;

		out.write(rcastcc(&_partySerialNumber), sizeof(int));
		out.write(rcastcc(_name), sizeof(string));
		out.write(rcastcc(&_partyId), sizeof(int));
		tempId = _candidate->getId();
		out.write(rcastcc(tempId), sizeof(string));
		_partyCandidates->save(out);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Party Save issue" << endl;
			exit(-1);
		}
	}

	void Party::load(istream& in, Election* election) {
		int temp = 0;
		string canId;
		CitizensArr* citArr = election->getCitizens();
		DistrictsArr* districts = election->getDistricts();


		in.read(rcastc(&temp), sizeof(int));
		if (temp > _partySerialNumber)
			_partySerialNumber = temp;

		in.read(rcastc(_name), sizeof(string));
		in.read(rcastc(&_partyId), sizeof(int));
		in.read(rcastc(canId), sizeof(string));
		_candidate = citArr->find(canId);
		_partyCandidates = new PartyCandidates(in, districts, citArr);

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Citizen load issue" << endl;
			exit(-1);
		}
	}
}