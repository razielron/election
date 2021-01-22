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
		delete _partyCandidates;
	}

	ostream& operator<<(ostream& os, const Party& party) {
		if (!os || !party)
			throw invalid_argument("Party, <<");
		
		os << "-----------PARTY-START-----------" << endl;
		os << "Party ID: " << party.getId() << endl;
		os << "Name of Party: " << party.getName() << endl;
		os << "Party candidate: " << endl;
		os << *(party.getCandidate());
		os << "Represetetives of district: " << endl << endl;
		party.getPartyCandidates()->printPartyCandidates();
		os << "------------PARTY-END-----------" << endl;

		return os;
	}

	void Party::setCandidate(Citizen* cit) {
		_candidate = cit;
	}

	void Party::setDistrictWinner() {
		_partyCandidates->setDistrictWinner(this);
	}

	void Party::setPartyTotalElectors() {
		_totalElectors = _partyCandidates->getPartyTotalElectors(this);
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
		if (!out || !out.good())
			throw invalid_argument("Party, save(ostream& out)");
		
		int temp, len;
		string tempId;
		out.write(rcastcc(&_partySerialNumber), sizeof(int));
		saveString(out, _name);
		out.write(rcastcc(&_partyId), sizeof(int));
		saveString(out, _candidate->getId());
		_partyCandidates->save(out);

		if (!out.good()) {
			throw iostream::failure("Party, save(out)");
		}
	}

	void Party::load(istream& in, Election* election) {	
		if (!in || !in.good() || !election )
			throw invalid_argument("Party, load");

		int temp = 0, len;
		string canId;
		CitizensArr* citArr = election->getCitizens();
		DistrictsArr* districts = election->getDistricts();

		try {
			in.read(rcastc(&temp), sizeof(int));
			if (temp > _partySerialNumber)
				_partySerialNumber = temp;

			_name = loadString(in);
			in.read(rcastc(&_partyId), sizeof(int));
			in.read(rcastc(&len), sizeof(int));
			canId = loadString(in);

			if (!in.good()) {
				throw iostream::failure("Party, load(in, election)");
			}

			_candidate = citArr->find(canId);
			_partyCandidates = new PartyCandidates(in, districts, citArr);
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	}
}