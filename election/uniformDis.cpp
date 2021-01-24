#include "uniformDis.h"
namespace Elections
{
	UniformDis::UniformDis() : District() {}

	UniformDis::UniformDis(string name, int numOfRepresentatives) : District(name, numOfRepresentatives) {}

	UniformDis::UniformDis(istream& in): District(in) {}

	string UniformDis::getType() const {
		return "UNIFORM";
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
