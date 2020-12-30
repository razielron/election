#include <string>
#include <typeinfo>
#include "election.h"
#include "district.h"
#include "devidedDis.h"
#include "UniformDis.h"
#include "districtsArr.h"
#include "Party.h"
#include "partiesArr.h"
#include "partyCandidates.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

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
		_districts->~DistrictsArr();
		_parties->~PartiesArr();
		_citizens->~CitizensArr();
	}

	void Election::appendParty(Party* party) {
		_parties->appendParty(party);
	}

	void Election::appendDistrict(District* dis) {
		_districts->appendDistrict(dis);
	}

	void Election::appendCitizen(Citizen* cit) {
		_citizens->appendCitizen(cit);
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
		out.write(rcastcc(_day), sizeof(int));
		out.write(rcastcc(_month), sizeof(int));
		out.write(rcastcc(_year), sizeof(int));

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
		in.read(rcastc(_day), sizeof(int));
		in.read(rcastc(_month), sizeof(int));
		in.read(rcastc(_year), sizeof(int));

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Election load issue" << endl;
			exit(-1);
		}

		_districts = new DistrictsArr(in);
		_citizens = new CitizensArr(in, _districts);
		_parties = new PartiesArr(in, _districts, _citizens);
	}

	void Election::saveResults(ostream& out) const {
		_districts->saveResults(out);
		_citizens->saveResults(out);
		_parties->saveResults(out);
	}

	void Election::loadResults(istream& in) {
		_districts->loadResults(in, _citizens, _parties);
		_citizens->loadResults(in, _parties);
		_parties->loadResults(in);
	}

}
