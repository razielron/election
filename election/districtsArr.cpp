#include "districtsArr.h"
#include "districtLoader.h"
#include "citizensArr.h"
#include "devidedDis.h"
#include "uniformDis.h"
#include "district.h"
#include <typeinfo>
#include <string.h>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	DistrictsArr::DistrictsArr() : _logSize(0), _phySize(1) {
		_districts = new District*[_phySize];
	}

	DistrictsArr::DistrictsArr(District* dis) : _logSize(1), _phySize(2) {
		_districts = new District*[_phySize];
		_districts[0] = dis;
	}

	DistrictsArr::DistrictsArr(istream& in) {
		load(in);
	}


	DistrictsArr::~DistrictsArr() {
		for (int i = 0;i < _logSize;i++) {
			_districts[i]->~District();
		}
		delete[] _districts;
	}

	void DistrictsArr::operator=(const DistrictsArr& disArr) {
		if (&disArr != this) {
			delete[] _districts;
			_logSize = _phySize = disArr.getLogSize();
			_districts = new District * [_logSize];
			for (int i = 0; i < _logSize; i++) {
				_districts[i] = disArr[i];
			}
		}
	}

	ostream& operator<<(ostream& os, const DistrictsArr& disArr) {
		for (int i = 0; i < disArr.getLogSize(); i++) {
			if (typeid(*(disArr[i])) == typeid(UniformDis))
				cout << *(static_cast<UniformDis*>(disArr[i])) << endl;
			else
				cout << *(static_cast<DevidedDis*>(disArr[i])) << endl;
		}
		return os;
	}

	void DistrictsArr::increaseDistrictsArr() {
		_phySize *=2;
		District** temp = new District*[_phySize];
		memcpy(temp, _districts, sizeof(District*)*_logSize);
		delete[] _districts;
		_districts = new District*[_phySize];
		memcpy(_districts, temp, sizeof(District*)*_logSize);
		delete[] temp;
	}

	void DistrictsArr::appendDistrict(District* dis) {
		if (_phySize >= _logSize) {
			DistrictsArr::increaseDistrictsArr();
		}
		_districts[_logSize++] = dis;
	}

	District* DistrictsArr::getDistrict(int districtId) const {
		for (int i = 0;i < _logSize;i++) {
			if (_districts[i]->getDistrictNumber() == districtId)
				return _districts[i];
		}
		return nullptr;
	}


	void DistrictsArr::save(ostream& out) const{
		out.write(rcastcc(_logSize), sizeof(int));
		for (int i = 0;i < _logSize;i++) {
			DistrictLoader::save(out, _districts[i]);
		}
	
		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "DistrictArr Save issue" << endl;
			exit(-1);
		}
	}


	void DistrictsArr::load(istream& in){
		in.read(rcastc(_phySize), sizeof(int));
		_logSize = _phySize;
		_districts = new District*[_logSize];

		for (int i = 0; i < _logSize; i++) {
			_districts[i] = DistrictLoader::load(in);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictArr load issue" << endl;
			exit(-1);
		}
	}

	void DistrictsArr::saveResults(ostream& out) const {
		for (int i = 0; i < _logSize; i++) {
			_districts[i]->saveResults(out);
		}

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "DistrictsArr Save issue" << endl;
			exit(-1);
		}
	}

	void DistrictsArr::loadResults(istream& in, CitizensArr* citArr) {
		for (int i = 0; i < _logSize; i++) {
			_districts[i]->loadResults(in, citArr);
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictsArr Load issue" << endl;
			exit(-1);
		}
	}	
}