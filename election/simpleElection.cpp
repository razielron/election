#include "simpleElection.h"
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
	void SimpleElection::printResults() const {
		DevidedDis* dis = static_cast<DevidedDis*>((*_districts)[0]);
		int partyRep = 0, partyVotes = 0;

		cout << "Voters Percentage: " << dis->getVotersPresentage() << "%" << endl;
		cout << "Number of representetives: " << dis->getNumOfRepresentatives() << endl << endl;
		cout << "--------------PARTIES-RESULTS-START--------------" << endl;
		for (int j = 0; j < _parties->getLogSize(); j++) {
			cout << "----------PARTY-RESULTS-START----------" << endl;
			cout << "Party: " << (*_parties)[j]->getName() << endl;
			partyRep = (*_parties)[j]->getPartyCandidates()->getPartyNumOfElectors(dis);
			partyVotes = (*_parties)[j]->getPartyCandidates()->getPartyNumOfVotes();
			cout << "Total Votes: " << partyVotes << endl;
			cout << "Total Votes Presentage: " << dis->getVotersPresentage(partyVotes) << "%" << endl;
			cout << "Party num of elected representetives: " << partyRep << endl;
			if (partyRep) {
				cout << "Party elected representetives: " << endl;
				for (int k = 0; k < partyRep; k++)
					cout << *((*_parties)[j]->getPartyCandidates()->getDistrictPartyCandidates(dis)->getCit(k));
			}
			else {
				cout << "Party elected representetives: NO REPRESENTETIVES" << endl;
			}
			cout << "-----------PARTY-RESULTS-END----------" << endl;
		}
		cout << "---------------PARTIES-RESULTS-END--------------" << endl;
		cout << endl;
	}
}