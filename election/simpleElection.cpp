#include "simpleElection.h"
#include "districtLoader.h"
namespace Elections
{
	ostream& operator<<(ostream& os, const SimpleElection& election) {
		PartiesArr* parties = election.getParties();
		DevidedDis* dis = static_cast<DevidedDis*>((*election.getDistricts())[0]);
		int partyRep = 0, partyVotes = 0;

		os << static_cast<const Election&>(election);
		os << "Voters Percentage: " << dis->getVotersPresentage() << "%" << endl;
		os << "Number of representetives: " << dis->getNumOfRepresentatives() << endl << endl;
		os << "--------------PARTIES-RESULTS-START--------------" << endl;
		for (int j = 0; j < parties->size(); j++) {
			os << "----------PARTY-RESULTS-START----------" << endl;
			os << "Party: " << (*parties)[j]->getName() << endl;
			partyRep = (*parties)[j]->getPartyCandidates()->getPartyNumOfElectors(dis);
			partyVotes = (*parties)[j]->getPartyCandidates()->getPartyNumOfVotes();
			os << "Total Votes: " << partyVotes << endl;
			os << "Total Votes Presentage: " << dis->getVotersPresentage(partyVotes) << "%" << endl;
			os << "Party num of elected representetives: " << partyRep << endl;
			if (partyRep) {
				os << "Party elected representetives: " << endl;
				for (int k = 0; k < partyRep; k++)
					os << *((*parties)[j]->getPartyCandidates()->getDistrictPartyCandidates(dis)->at(k));
			}
			else {
				os << "Party elected representetives: NO REPRESENTETIVES" << endl;
			}
			os << "-----------PARTY-RESULTS-END----------" << endl;
		}
		os << "---------------PARTIES-RESULTS-END--------------" << endl;
		os << endl;

		return os;
	}
}