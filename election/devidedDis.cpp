#include "devidedDis.h"
#include "partiesArr.h"

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	DevidedDis::DevidedDis() : District(){}

	DevidedDis::DevidedDis(string name, int numOfRepresentatives) {
		District(name, numOfRepresentatives);
	}

	DevidedDis::DevidedDis(istream& in) {
		District(in);
	}

	ostream& operator<<(ostream& os, const DevidedDis& devDis) {
		if (!os || !devDis)
			throw invalid_argument("DevidedDis, <<");
		
		os << "-------------DISTRICT-START------------" << endl;
		os << "District ID: " << devDis.getId() << endl;
		os << "District type: Devided" << endl;
		os << "Name of district: " << devDis.getId() << endl;
		os << "Number of representetive: " << devDis.getNumOfRepresentatives() << endl;
		os << "--------------DISTRICT-END-------------" << endl;
		
		return os;
	}

	void DevidedDis::printResults(PartiesArr* partiesArr) {
		if (!partiesArr) {
			throw invalid_argument("DevidedDis, printResults");
		}

		cout << "-------------DISTRICT-RESULTS-START------------" << endl;
		cout << "Name of district: " << _name << endl;
		cout << "District type: DEVIDED" << endl;
		cout << "Number of representetive: " << _numOfRepresentatives << endl << endl;
		cout << "District voters Percentage: " << getVotersPresentage() << "%" << endl;
		partiesArr->sortByNumOfElectorsInDistrict(this);
		cout << "-------------Votes Summery------------" << endl << endl;
		for (int i = 0;i < partiesArr->size() &&
			((*partiesArr)[i]->getPartyCandidates()->getPartyNumOfElectors(this) > 0);i++) {
			partiesArr->printDistrictPartyDetails(i, this);
		}
		cout << "--------------------------------------" << endl << endl;
		cout << "--------------DISTRICT-RESULTS-END-------------" << endl;
		
	}

}
