#include "election.h"

namespace Elections
{
	Election::Election(int day, int month, int year)
		: _day(day), _month(month), _year(year) {
		_districts = new DistrictsArr;
		_parties = new PartiesArr;
		_citizens = new CitizensArr;
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
		party->appendCandidateToList(dis, cit);
	}

	void Election::appendDistrictRep(District* dis, Citizen* cit) {
		dis->appendToRepresentetives(cit);
	}

	void Election::printCitizens() const {
		cout << (*_citizens);
	}

	void Election::printDistricts() const {
		cout << (*_districts);
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
		out.write(rcastcc(&_day), sizeof(int));
		out.write(rcastcc(&_month), sizeof(int));
		out.write(rcastcc(&_year), sizeof(int));

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Election Save issue" << endl;
			exit(-1);
		}

		_districts->save(out);
		_citizens->save(out);
		_parties->save(out);
	}

	void Election::load(istream& in) {
		in.read(rcastc(&_day), sizeof(int));
		in.read(rcastc(&_month), sizeof(int));
		in.read(rcastc(&_year), sizeof(int));

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Election load issue" << endl;
			exit(-1);
		}

		_districts = new DistrictsArr(in);
		_citizens = new CitizensArr(in, this);
		_parties = new PartiesArr(in, this);
	}

	void Election::saveVotes(ostream& out) const {
		_citizens->saveVotes(out);
	}

	void Election::loadVotes(istream& in) {
		_citizens->loadVotes(in, _parties);
	}

}
