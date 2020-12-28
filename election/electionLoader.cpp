#include <typeinfo>
#include "electionLoader.h"
#include "normalElection.h"
#include "simpleElection.h"
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	void ElectionLoader::save(ostream& out, Election* election) {
		if ((typeid(*election)) == (typeid(NormalElection))) {
			out.write(rcastcc(ElectionType::normalElection), sizeof(ElectionType));
		}
		else {
			out.write(rcastcc(ElectionType::simpleElection), sizeof(ElectionType));
		}
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





