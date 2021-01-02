#pragma once
#include <iostream>
using namespace std;

namespace Elections {

	class District;
	class CitizensArr;
	class PartiesArr;
	class DistrictsArr
	{
		private:
			District** _districts;
			int _logSize;
			int _phySize;

		private:
			//double the physical size of the array
			void increaseDistrictsArr();

		//Constructors + Distructors
		public:
			DistrictsArr();
			DistrictsArr(District* dis);
			DistrictsArr(istream& in);
			~DistrictsArr();
			//DistrictsArr(const District& dis) = delete;
			void operator=(const DistrictsArr& disArr);
			District* operator[](int idx) { return _districts[idx]; }
			District* operator[](int idx) const { return _districts[idx]; }
			friend ostream& operator<<(ostream& os, const DistrictsArr& disArr);

		//GETTERS
		public:
			District** getDistricts() const { return _districts; }
			int getLogSize() const { return _logSize; }
			//returns district by given districd id
			District* getDistrict(int districtId) const;

		public:
			//add district to districts array
			void appendDistrict(District* dis);
			//prints all districts and their data
			void printDistricts() const;

			//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in);
	};

}