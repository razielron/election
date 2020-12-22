#pragma once

namespace Elections {

	class District;

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
			~DistrictsArr();
			DistrictsArr(const District& dis) = delete;

		//GETTERS
		public:
			District** getDistricts() { return _districts; }
			int getLogSize() { return _logSize; }
			//returns district by given districd id
			District* getDistrict(int districtId) const;

		public:
			//add district to districts array
			void appendDistrict(District* dis);
			//prints all districts and their data
			void printDistricts() const;
			//print election results by district
			void printResults() const;

	};

}