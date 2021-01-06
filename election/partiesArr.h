#pragma once
#include "party.h"

namespace Elections {

	class PartiesArr: public DynamicArr<Party*>
	{
		//Constructors + Distructors
		public:
			PartiesArr(): DynamicArr() {};
			PartiesArr(Party* party): DynamicArr(party) {};
			PartiesArr(istream& in, Election* election);
			~PartiesArr() {}
			
		//GETTERS
		public:
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
			//bool sortByNumOfElectors() const;
			void sortByNumOfElectors() const;
			//sorts the parites from the most electors to few in specific district
			void sortByNumOfElectorsInDistrict(District* dis);
			//sorts the parites from the most total votes to few
			void sortByTotalVotes();
			//prints party's data in a specific district
			void printDistrictPartyDetails(int& i, District* dis);
			//go over all parties and prints thier results
			void printResults() const;

			//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in, Election* election);
	};

}