#include "districtsArr.h"
#include "district.h"
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

	void DistrictsArr::printDistricts() const {
		for (int i = 0; i < _logSize; i++) {
			_districts[i]->printDistrict();
		}
	}

	void DistrictsArr::printResults() const {
		for (int i = 0; i < _logSize; i++) {
			_districts[i]->printResults();
		}
	}

	District* DistrictsArr::getDistrict(int districtId) const {
		for (int i = 0;i < _logSize;i++) {
			if (_districts[i]->getDistrictNumber() == districtId)
				return _districts[i];
		}
		return nullptr;
	}
}