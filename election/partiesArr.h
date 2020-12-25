#pragma once
#include <iostream>
using namespace std;

namespace Elections {

	class District;
	class Party;
	class PartiesArr
	{
		private:
			Party** _parties;
			int _logSize;
			int _phySize;

		private:
			//doubles the pyhsical size of the array
			void increasePartiesArr();

		//Constructors + Distructors
		public:
			PartiesArr();
			PartiesArr(Party* party);
			~PartiesArr();
			PartiesArr(const Party& party) = delete;
			void operator=(const PartiesArr& partyArr);
			Party* operator[](int idx) { return _parties[idx]; }
			Party* operator[](int idx) const { return _parties[idx]; }
			friend ostream& operator<<(ostream& os, const PartiesArr& partyArr);

		//GETTERS
		public:
			Party** getParties() const { return _parties; }
			int getLogSize() const { return _logSize; }
			//get party from array by given id
			Party* getParty(int id);
			//returns the party with most electors
			Party* getElectionWinner();

		//SETTERS
		public:
			//go over all parties in the array and calculates if they win in any district
			bool setDistrictWinner();
			//go over all parties in the array and calculates their electors by their votes
			bool setPartyTotalElectors();

		public:
			//adds party for the array
			void appendParty(Party* party);
			//go over all parties in the array and adds thier candidates for each district
			void appendElectedRep();
			//go over all parties in the array and fills the representetives by candidates
			void addRepresentetives();
			//sorts the parites from the most electors to few
			void sortByNumOfElectors() const;
			//sorts the parites from the most electors to few in specific district
			void sortByNumOfElectorsInDistrict(District* dis);
			//prints party's data in a specific district
			void printDistrictPartyDetails(int& i, District* dis);
			//go over all parties and prints thier results
			void printResults() const;
	};

}