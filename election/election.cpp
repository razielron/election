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
		cout << _citizens;
	}

	void Election::printDistricts() const {
		_districts->printDistricts();
	}

	void Election::printParties() const {
		cout << _parties;
	}

	void Election::printResults() const {
		District* dis = nullptr;
		int partyRep = 0;
		for (int i = 0;i < _districts->getLogSize();i++) {
			dis = (*_districts)[i];
			if ((typeid(*dis)) == (typeid(UniformDis)))
				static_cast<UniformDis*>(dis)->printResults();
			else 
				static_cast<DevidedDis*>(dis)->printResults(_parties);
			for (int j = 0; j < _parties->getLogSize(); j++) {
				cout << "----------PARTY-in-district-RESULTS-START----------" << endl;
				cout << "Party: " << (*_parties)[j]->getName() << endl;
				(*_parties)[j]->getPartyCandidates()->printResults(dis);
				partyRep = (*_parties)[j]->getPartyCandidates()->getPartyNumOfElectors(dis);
				if (partyRep) {
					cout << "Party elected representetives: " << endl;
					for (int k = 0; k < partyRep; k++)
						 cout << (*_parties)[j]->getPartyCandidates()->getDistrictPartyCandidates(i)->getCit(k);
				}
				else {
					cout << "Party elected representetives: NO REPRESENTETIVES" << endl;
				}
				cout << "-----------PARTY-in-district-RESULTS-END----------" << endl;
			}
			cout << endl;
		}
	}

	void Election::electionSummery() const {
		_parties->addRepresentetives();
		_parties->setDistrictWinner();
		_parties->setPartyTotalElectors();
	}

}
