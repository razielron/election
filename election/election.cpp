#include <string.h>
#include <typeinfo>
#include "election.h"
#include "district.h"
#include "devidedDis.h"
#include "UniformDis.h"
#include "districtsArr.h"
#include "Party.h"
#include "partiesArr.h"
#include "partyCandidates.h"

namespace Elections
{
	Election::Election(int day, int month, int year)
		: _day(day), _month(month), _year(year) {
		_districts = new DistrictsArr;
		_parties = new PartiesArr;
		_citizens = new CitizensArr;
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

}
