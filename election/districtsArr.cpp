#include "districtsArr.h"
#include "districtLoader.h"

namespace Elections
{
	DistrictsArr::DistrictsArr(istream& in) : DynamicArr(in) {
		load(in);
	}

	ostream& operator<<(ostream& os, const DistrictsArr& disArr) {
		if (!os || !disArr) {
			throw invalid_argument("DistrictsArr, ostream& operator<<");
		}

		for (int i = 0; i < disArr.size(); i++) {
			if (typeid(*(disArr[i])) == typeid(UniformDis))
				cout << *(static_cast<UniformDis*>(disArr[i])) << endl;
			else
				cout << *(static_cast<DevidedDis*>(disArr[i])) << endl;
		}
		return os;
	}

	void DistrictsArr::save(ostream& out) const{
		if (!out || !out.good())
			throw invalid_argument("DistrictsArr, save(ostream& out), parameter issues");

		out.write(rcastcc(&_logSize), sizeof(int));
		if (!out.good()) {
			throw iostream::failure("DistrictsArr, save(out)");
		}

		for (int i = 0;i < _logSize;i++) {
			DistrictLoader::save(out, _array[i]);
		}
	}

	void DistrictsArr::load(istream& in){

		if (!in || !in.good())
			throw invalid_argument("DistrictsArr, load(istream& in)");
		
		try {
			for (int i = 0; i < this->capacity(); i++) {
				push_back(DistrictLoader::load(in));
			}
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}
	}
}