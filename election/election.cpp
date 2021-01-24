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
		_districts->deleteValues();
		delete _districts;
		_citizens->deleteValues();
		delete _citizens;
		_parties->deleteValues();
		delete _parties;
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
		_parties->push_back(party);
	}

	void Election::appendDistrict(District* dis) {
		_districts->push_back(dis);
	}

	void Election::appendCitizen(Citizen* cit) {
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
		cout << (*_citizens);
	}

	void Election::printDistricts() const {
		_districts->printDis();
	}

	void Election::printParties() const {
		cout << (*_parties);
	}

	void Election::electionSummery() const {
		_parties->addRepresentetives();
		_parties->setDistrictWinner();
		_parties->setPartyTotalElectors();
	}

	void Election::save(ostream& out) const {
		if (!out || !out.good()) {
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
		_citizens->saveVotes(out);
	}

	void Election::loadVotes(istream& in) {
		_citizens->loadVotes(in, _parties);
	}

}
