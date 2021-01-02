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
	ostream& operator<<(ostream& os, const NormalElection& election) {
		PartiesArr* parties = election.getParties();
		DistrictsArr* districts = election.getDistricts();
		District* dis = nullptr;
		int partyRep = 0;

		os << static_cast<const Election&>(election);

		for (int i = 0; i < districts->getLogSize(); i++) {
			dis = (*districts)[i];

			if ((typeid(*dis)) == (typeid(UniformDis)))
				static_cast<UniformDis*>(dis)->printResults();
			else
				static_cast<DevidedDis*>(dis)->printResults(parties);

			for (int j = 0; j < parties->getLogSize(); j++) {
				os << "----------PARTIES-in-district-RESULTS-START----------" << endl;
				os << "Party: " << (*parties)[j]->getName() << endl;
				partyRep = (*parties)[j]->getPartyCandidates()->getPartyNumOfElectors(dis);
				(*parties)[j]->getPartyCandidates()->printResults(dis);
				os << "Prime Minister Candidate : " << *((*parties)[j]->getCandidate()) << endl;
				if (partyRep) {
					os << "Party elected representetives: " << endl;
					for (int k = 0; k < partyRep; k++)
						os << *((*parties)[j]->getPartyCandidates()->getDistrictPartyCandidates(i)->getCit(k));
				}
				else {
					os << "Party elected representetives: NO REPRESENTETIVES" << endl;
				}
				os << "-----------PARTIES-in-district-RESULTS-END----------" << endl;
			}
			os << endl;
		}

		return os;
	}
}