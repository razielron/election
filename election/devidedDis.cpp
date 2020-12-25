#include "devidedDis.h"
#include "partiesArr.h"
#include "partyCandidates.h"
#include "party.h"
#include <string.h>
#include <iostream>
using namespace std;

namespace Elections
{
	DevidedDis::DevidedDis() {}

	DevidedDis::DevidedDis(char* name, int numOfRepresentatives) : District(name, numOfRepresentatives){}


	ostream& operator<<(ostream& os, const DevidedDis& devDis) {
		os << "-------------DISTRICT-START------------" << endl;
		os << "District ID: " << devDis.getDistrictNumber() << endl;
		os << "District type: Devided" << endl;
		os << "Name of district: " << devDis.getDistrictNumber() << endl;
		os << "Number of representetive: " << devDis.getNumOfRepresentatives() << endl;
		os << "--------------DISTRICT-END-------------" << endl;
		return os;
	}



	void DevidedDis::printResults(PartiesArr* partiesArr) {
		cout << "-------------DISTRICT-RESULTS-START------------" << endl;
		cout << "Name of district: " << _name << endl;
		cout << "District type: DEVIDED" << endl;
		cout << "Number of representetive: " << _numOfRepresentatives << endl << endl;

		partiesArr->sortByNumOfElectorsInDistrict(this);

		cout << "-------------Votes Summery------------" << endl << endl;

		for (int i = 0;i < partiesArr->getLogSize() &&
			((*partiesArr)[i]->getPartyCandidates()->getPartyNumOfElectors(this) > 0);i++) {
			partiesArr->printDistrictPartyDetails(i, this);
		}

		cout << "--------------------------------------" << endl << endl;
		cout << "District voters Percentage: " << getVotersPresentage() << "%" << endl;
		cout << "--------------DISTRICT-RESULTS-END-------------" << endl;
	}
}
