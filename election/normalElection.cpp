#include "normalElection.h"
#include "district.h"
#include "devidedDis.h"
#include "UniformDis.h"
#include "districtsArr.h"
#include "Party.h"
#include "partiesArr.h"
#include "partyCandidates.h"
#include <typeinfo>
#include <string>

namespace Elections
{
	void NormalElection::printResults() const {
		District* dis = nullptr;
		int partyRep = 0;
		for (int i = 0; i < _districts->getLogSize(); i++) {
			dis = (*_districts)[i];
			if ((typeid(*dis)) == (typeid(UniformDis)))
				static_cast<UniformDis*>(dis)->printResults();
			else
				static_cast<DevidedDis*>(dis)->printResults(_parties);
			for (int j = 0; j < _parties->getLogSize(); j++) {
				cout << "----------PARTIES-in-district-RESULTS-START----------" << endl;
				cout << "Party: " << (*_parties)[j]->getName() << endl;
				partyRep = (*_parties)[j]->getPartyCandidates()->getPartyNumOfElectors(dis);
				(*_parties)[j]->getPartyCandidates()->printResults(dis);
				cout << "Prime Minister Candidate : " << *((*_parties)[j]->getCandidate()) << endl;
				if (partyRep) {
					cout << "Party elected representetives: " << endl;
					for (int k = 0; k < partyRep; k++)
						cout << *((*_parties)[j]->getPartyCandidates()->getDistrictPartyCandidates(i)->getCit(k));
				}
				else {
					cout << "Party elected representetives: NO REPRESENTETIVES" << endl;
				}
				cout << "-----------PARTIES-in-district-RESULTS-END----------" << endl;
			}
			cout << endl;
		}
	}
}