#include "election.h"

namespace Elections
{
	Election::Election(int day, int month, int year)
		: _day(day), _month(month), _year(year) {
		if (_year < 1 || _month < 1 || _day < 1
			|| _month > 12 || _day > 31 || (_month == 2 && _day > 28)) {
			throw ElectionException("Election cannot be created - invalid date");
		}
		try {
			_districts = new DistrictsArr;
			_parties = new PartiesArr;
			_citizens = new CitizensArr;
		}
		catch (bad_alloc& err) {
			delete _districts;
			delete _citizens;
			cout << err.what() << endl;
			exit(1);
		}
	}

	Election::Election(istream& in) {
		load(in);
	}

	Election::~Election() {
		delete _districts;
		delete _parties;
		delete _citizens;
	}

	ostream& operator<<(ostream& os, const Election& election) {
		if (!os || !election) {
			throw invalid_argument("Election, operator<<, parameters issue");
		}

		os << "Election Date: ";
		os << election.getDay() << "/";
		os << election.getMonth() << "/";
		os << election.getYear() << endl;
		return os;
	}

	void Election::appendParty(Party* party) {
		if (!_parties) {
			throw invalid_argument("Election, appendParty, missing party");
		}

		_parties->push_back(party);
	}

	void Election::appendDistrict(District* dis) {
		if (!_districts) {
			throw invalid_argument("Election, appendDistrict, missing district");
		}

		_districts->push_back(dis);
	}

	void Election::appendCitizen(Citizen* cit) {
		if (!_citizens) {
			throw invalid_argument("Election, appendCitizen, missing citizen");
		}

		_citizens->push_back(cit);
	}

	void Election::appendCandidateToList(Party* party, District* dis, Citizen* cit) {
		if (!party) {
			throw invalid_argument("Election, appendCandidateToList, missing party");
		}

		party->appendCandidateToList(dis, cit);
	}

	void Election::appendDistrictRep(District* dis, Citizen* cit) {
		if (!dis) {
			throw invalid_argument("Election, appendDistrictRep, missing district");
		}

		dis->appendToRepresentetives(cit);
	}

	void Election::printCitizens() const {
		if (!_citizens) {
			throw invalid_argument("Election, printCitizens, missing citizens");
		}

		cout << (*_citizens);
	}

	void Election::printDistricts() const {
		if (!_districts) {
			throw invalid_argument("Election, printDistricts, missing districts");
		}

		cout << (*_districts);
	}

	void Election::printParties() const {
		if (!_parties) {
			throw invalid_argument("Election, printParties, missing parties");
		}

		cout << (*_parties);
	}

	void Election::electionSummery() const {
		if (!_parties) {
			throw invalid_argument("Election, electionSummery, missing parties");
		}

		_parties->addRepresentetives();
		_parties->setDistrictWinner();
		_parties->setPartyTotalElectors();
	}

	void Election::save(ostream& out) const {
		if (!out || !out.good() || !_districts || !_parties || !_citizens) {
			throw invalid_argument("Election, save, parameters issue");
		}

		out.write(rcastcc(&_day), sizeof(int));
		out.write(rcastcc(&_month), sizeof(int));
		out.write(rcastcc(&_year), sizeof(int));

		if (!out.good()) {
			throw iostream::failure("Election, save, save didn't work");
		}

		_districts->save(out);
		_citizens->save(out);
		_parties->save(out);
	}

	void Election::load(istream& in) {
		if (!in || !in.good()) {
			throw invalid_argument("Election, load, parameters issue");
		}

		in.read(rcastc(&_day), sizeof(int));
		in.read(rcastc(&_month), sizeof(int));
		in.read(rcastc(&_year), sizeof(int));

		if (!in.good()) {
			throw iostream::failure("Election, load, laod didn't work");
		}

		try {
			_districts = new DistrictsArr(in);
			_citizens = new CitizensArr(in, this);
			_parties = new PartiesArr(in, this);
		}
		catch (bad_alloc& err) {
			delete _districts;
			delete _citizens;
			cout << err.what() << endl;
			exit(1);
		}
	}

	void Election::saveVotes(ostream& out) const {
		if (!_citizens) {
			throw invalid_argument("Elecetion, saveVote, missing citizens");
		}

		_citizens->saveVotes(out);
	}

	void Election::loadVotes(istream& in) {
		if (!_citizens) {
			throw invalid_argument("Election, loadVotes, missing citizens");
		}

		_citizens->loadVotes(in, _parties);
	}

}
