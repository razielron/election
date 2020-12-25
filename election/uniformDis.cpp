#include "uniformDis.h"
#include "party.h"
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;

namespace Elections
{
	UniformDis::UniformDis() {}

	UniformDis::UniformDis(char* name, int numOfRepresentatives) : District(name, numOfRepresentatives) {}

	ostream& operator<<(ostream& os, const UniformDis& uniDis) {
		os << "-------------DISTRICT-START------------" << endl;
		os << "District ID: " << uniDis.getDistrictNumber() << endl;
		os << "District type: Uniform" << endl;
		os << "Name of district: " << uniDis.getDistrictNumber() << endl;
		os << "Number of representetive: " << uniDis.getNumOfRepresentatives() << endl;
		os << "--------------DISTRICT-END-------------" << endl;
		return os;
	}

	void UniformDis::printResults() {
		cout << "-------------DISTRICT-RESULTS-START------------" << endl;
		cout << "Name of district: " << _name << endl;
		cout << "District type: UNIFORM" << endl;
		cout << "Number of representetive: " << _numOfRepresentatives << endl;
		cout << "District candidate winner: " << _winner->getCandidate()->getName() << endl;
		cout << "District voters Percentage: " << getVotersPresentage() << "%" << endl;
		cout << "--------------DISTRICT-RESULTS-END-------------" << endl;
	}
}
