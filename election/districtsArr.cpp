#include "districtsArr.h"
#include "districtLoader.h"

namespace Elections
{
	DistrictsArr::DistrictsArr(istream& in) {
		load(in);
	}

	ostream& operator<<(ostream& os, const DistrictsArr& disArr) {
		for (int i = 0; i < disArr.size(); i++) {
			if (typeid(*(disArr[i])) == typeid(UniformDis))
				cout << *(static_cast<UniformDis*>(disArr[i])) << endl;
			else
				cout << *(static_cast<DevidedDis*>(disArr[i])) << endl;
		}
		return os;
	}


	void DistrictsArr::save(ostream& out) const{
		out.write(rcastcc(&_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			DistrictLoader::save(out, _array[i]);
		}
	
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "DistrictArr Save issue" << endl;
			exit(-1);
		}
	}

	void DistrictsArr::load(istream& in){
		in.read(rcastc(&_phySize), sizeof(int));
		_logSize = _phySize;
		_array = new District*[_phySize];

		for (int i = 0; i < _phySize; i++) {
			_array[i] = DistrictLoader::load(in);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictArr load issue" << endl;
			exit(-1);
		}
	}
}