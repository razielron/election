#pragma once
#include <istream>
#include <ostream>
using namespace std;

namespace Elections {

	class DistrictsArr;
	class PartiesArr;
	class Citizen;

	class CitizensArr
	{
		private:
			Citizen** _citizens;
			int _logSize;
			int _phySize;

		private:
			//double the size of the arr
			void increaseCitizensArr();

		//Constructors + Distructors
		public:
			CitizensArr();
			CitizensArr(Citizen* cit);
			CitizensArr(istream& in, Election* election);
			CitizensArr(istream& in, CitizensArr* citizens);
			~CitizensArr();
			CitizensArr(const Citizen& cit) = delete;
			void operator=(const CitizensArr& citArr);
			Citizen* operator[](int idx) { return _citizens[idx]; }
			Citizen* operator[](int idx) const { return _citizens[idx]; }
			friend std::ostream& operator<<(std::ostream& os, const CitizensArr& citArr);
			

		//GETTERS
		public:
			//returns a citizen by given id
			Citizen* getCit(char* id);
			//returns cirtizen by given position
			Citizen* getCit(int position);
			//returns the number of zitizens in the array
			int getLogSize() const { return _logSize; }

			

		public:
			//adding citizen to the arr
			void appendCitizen(Citizen* cit);
			void deleteArrPointer();

		//Load and Save
		public:
			void saveId(ostream& out) const;
			void loadById(istream& in, CitizensArr* citizens);
			void save(ostream& out) const;
			void load(istream& in, Election* election);
			void saveVotes(ostream& out) const;
			void loadVotes(istream& in, PartiesArr* parties);
	};

}