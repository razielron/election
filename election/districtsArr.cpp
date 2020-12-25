#include "districtsArr.h"
#include "devidedDis.h"
#include "uniformDis.h"
#include "district.h"
#include <typeinfo>
#include <string.h>

namespace Elections
{
	DistrictsArr::DistrictsArr() : _logSize(0), _phySize(1) {
		_districts = new District*[_phySize];
	}

	DistrictsArr::DistrictsArr(District* dis) : _logSize(1), _phySize(2) {
		_districts = new District*[_phySize];
		_districts[0] = dis;
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

	/*
	void DistrictsArr::printDistricts() const {
		for (int i = 0; i < _logSize; i++) {
			if (typeid(*(_districts[i])) == typeid(UniformDis))
				cout << *(static_cast<UniformDis*>(_districts[i])) << endl;
			else
				cout << *(static_cast<DevidedDis*>(_districts[i])) << endl;
		}
	}
	*/ 

	District* DistrictsArr::getDistrict(int districtId) const {
		for (int i = 0;i < _logSize;i++) {
			if (_districts[i]->getDistrictNumber() == districtId)
				return _districts[i];
		}
		return nullptr;
	}
}