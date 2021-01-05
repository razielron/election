#include "electionLoader.h"

namespace Elections
{
	void ElectionLoader::save(ostream& out, Election* election) {
		ElectionType type;
		if ((typeid(*election)) == (typeid(NormalElection))) {
			type = ElectionType::normalElection;
		}
		else {
			type = ElectionType::simpleElection;
		}
		out.write(rcastcc(&type), sizeof(ElectionType));
		election->save(out);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "Election Save issue" << endl;
			exit(-1);
		}
	}

	Election* ElectionLoader::load(istream& in) {
		ElectionType type;
		in.read(rcastc(&type), sizeof(type));

		switch (type) {
			case ElectionType::normalElection:
				return new NormalElection(in);
				break;
			case ElectionType::simpleElection:
				return new SimpleElection(in);
				break;
			default:
				return nullptr;
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "Election load issue" << endl;
			exit(-1);
		}
	}

}





