#pragma once

namespace Elections {

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

		//GETTERS
		public:
			Party** getParties() { return _parties; }
			int getLogSize() { return _logSize; }
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
			//go over all parties and prints all party's data
			void printParties() const;
			//go over all parties and prints thier results
			void printResults() const;
	};

}