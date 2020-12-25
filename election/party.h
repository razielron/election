#pragma once
#include "citizen.h"
#include <iostream>
using namespace std;

namespace Elections
{

	class PartyCandidates;
	class Party
	{
		private:
			static int _partySerialNumber;
			char* _name;
			int _partyId;
			int _totalElectors;
			Citizen* _candidate;
			PartyCandidates* _partyCandidates;

		public:
			friend class Election;

		//Constructors + Distructors
		public:
			Party() {}
			Party(char* name, Citizen* cit);
			friend ostream& operator<<(ostream& os, const Party& party);

		//GETTERS
		public:
			inline const char* getName() const { return _name; }
			inline const int getId() const { return _partyId; }
			inline const int getTotalElectors() const { return _totalElectors; }
			inline const Citizen* getCandidate() const { return _candidate; }
			inline PartyCandidates* getPartyCandidates() const { return _partyCandidates; }
		
		//SETTERS
		public:
			//calculated in PartyCandidates class and sets in totalElectors field
			bool setPartyTotalElectors();
			//sets the candidate for prime minister
			bool setCandidate(Citizen* cit);
			//calculated in PartyCandidates class and sets in each district the party winner
			bool setDistrictWinner();

		public:
			//calculated in PartyCandidates and returns the total votes of this party
			int getPartyNumOfVotes();
			//passes a district and a citizen candidate to add to PartyCadidates
			void appendCandidateToList(District* dis, Citizen* cit);
			//add vote to for this party by given district
			void addVote(District* dis);
			//fill district's representetives by PartyCandidates list of candidater
			void addRepresentetives();
			//prints party's data
			void printParty() const;
			//prints party's data in a specific district
			void printDistrictPartyDetails(District* dis) const;
			//prints the election's results of the party
			void printResults() const;
	};
}
