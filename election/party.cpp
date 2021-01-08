#include "party.h"
#include "partyCandidates.h"
#include "election.h"

namespace Elections
{
	int Party::_partySerialNumber = 0;

	Party::Party(string name, Citizen* cit) : _name(name), _totalElectors(0) {
		_partyId = _partySerialNumber++;
		if (!cit)
			throw PartyException(_partyId);
		_candidate = cit;
		try {
			_partyCandidates = new PartyCandidates;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	}

	Party::Party(istream& in, Election* election) : _totalElectors(0) {
		load(in, election);
	}

	Party::~Party() {
		try {
			_partyCandidates->~PartyCandidates();
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	ostream& operator<<(ostream& os, const Party& party) {
		if (!os || !party)
			throw("Party, << , Parametr issue");
		
		try {
			os << "-----------PARTY-START-----------" << endl;
			os << "Party ID: " << party.getId() << endl;
			os << "Name of Party: " << party.getName() << endl;
			os << "Party candidate: " << endl;
			os << party.getCandidate();
			os << "Represetetives of district: " << endl;
			party.getPartyCandidates()->printPartyCandidates();
			os << "------------PARTY-END-----------" << endl;
		}
		catch (const char* err) {
			cout << err << endl;
		}
		return os;
	}

	bool Party::setCandidate(Citizen* cit) {
		_candidate = cit;
		return true;
	}

	bool Party::setDistrictWinner() {
		try {
			return _partyCandidates->setDistrictWinner(this);
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}


	bool Party::setPartyTotalElectors() {
		try {
			_totalElectors = _partyCandidates->getPartyTotalElectors(this);
		}
		catch (const char* err) {
			cout << err << endl;
		}
		return true;
	}

	int Party::getPartyNumOfVotes() const {
		try {
			return _partyCandidates->getPartyNumOfVotes();
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::appendCandidateToList(District* dis, Citizen* cit) {
		try {
			_partyCandidates->appendPartyCandidate(dis, cit);
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::addVote(District* dis) {
		try {
			_partyCandidates->addVote(dis);
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::printDistrictPartyDetails(District* dis) const {
		try {
			cout << "Party: " << _name << endl;
			cout << "Candidate: " << _candidate->getName() << endl;
			cout << "Electors: " << _partyCandidates->getPartyNumOfElectors(dis) << endl << endl;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::printResults() const {
		try {
			cout << "-----------PARTY-RESULTS-START-----------" << endl;
			cout << "Name of Party: " << _name << endl;
			cout << "Name of Prime Minister Candidate: " << _candidate << endl;
			cout << "Total Electors: " << _totalElectors << endl;
			cout << "Total Votes: " << this->getPartyNumOfVotes() << endl;
			cout << "------------PARTY-RESULTS-END-----------" << endl;
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::addRepresentetives() {
		try {
			_partyCandidates->addRepresentetives();
		}
		catch (const char* err) {
			cout << err << endl;
		}
	}

	void Party::save(ostream& out) const {
		if (!out || !out.good())
			throw("Party, save(ostream& out), parameter issues");
		
		int temp;
		string tempId;
		try {
			out.write(rcastcc(&_partySerialNumber), sizeof(int));
			out.write(rcastcc(&_name), sizeof(_name));
			out.write(rcastcc(&_partyId), sizeof(int));
			tempId = _candidate->getId();
			out.write(rcastcc(&tempId), sizeof(tempId));
			_partyCandidates->save(out);
		}
		catch (const char* err) {
			cout << err << endl;
		}

		if (!out.good()) {
			throw("Party, save(out)");
		}
	}

	void Party::load(istream& in, Election* election) {
		
		if (!in || !in.good() || !election )
			throw("Party, load, Parameter issues");
		
		try {
			int temp = 0;
			string canId;
			CitizensArr* citArr = election->getCitizens();
			DistrictsArr* districts = election->getDistricts();


			in.read(rcastc(&temp), sizeof(int));
			if (temp > _partySerialNumber)
				_partySerialNumber = temp;

			in.read(rcastc(&_name), sizeof(_name));
			in.read(rcastc(&_partyId), sizeof(int));
			in.read(rcastc(&canId), sizeof(canId));
			_candidate = citArr->find(canId);
			_partyCandidates = new PartyCandidates(in, districts, citArr);
		}
		catch (const char* err) {
			cout << err << endl;
		}

		if (!in.good()) {
			throw("Party, load(in, election)");
		}
	}
}