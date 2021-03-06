#pragma once
#include "citizen.h"
#include "partyException.h"
#include "partyCandidates.h"

namespace Elections
{
	class Party
	{
		private:
			static int _partySerialNumber;
			string _name;
			int _partyId;
			int _totalElectors;
			Citizen* _candidate;
			PartyCandidates* _partyCandidates;

		public:
			friend class Election;

		//Constructors + Distructors
		public:
			Party():_name(""), _partyId(0), _totalElectors(0), _candidate(nullptr), _partyCandidates(nullptr) {}
			Party(istream& in, Election* election);
			Party(string name, Citizen* cit);
			~Party();
			friend ostream& operator<<(ostream& os, const Party& party);

		//GETTERS
		public:
			inline const string getName() const { return _name; }
			inline const int getId() const { return _partyId; }
			inline const int getTotalElectors() const { return _totalElectors; }
			inline const Citizen* getCandidate() const { return _candidate; }
			inline PartyCandidates* getPartyCandidates() const { return _partyCandidates; }
			bool operator !() const { return this == nullptr; };;
		
		//SETTERS
		public:
			//calculated in PartyCandidates class and sets in totalElectors field
			void setPartyTotalElectors();
			//sets the candidate for prime minister
			void setCandidate(Citizen* cit);
			//calculated in PartyCandidates class and sets in each district the party winner
			void setDistrictWinner();

		public:
			//calculated in PartyCandidates and returns the total votes of this party
			int getPartyNumOfVotes() const;
			//passes a district and a citizen candidate to add to PartyCadidates
			void appendCandidateToList(District* dis, Citizen* cit);
			//add vote to for this party by given district
			void addVote(District* dis);
			//fill district's representetives by PartyCandidates list of candidater
			void addRepresentetives();
			//prints party's data in a specific district
			void printDistrictPartyDetails(District* dis) const;
			//prints the election's results of the party
			void printResults() const;


			//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in, Election* election);
			
	};
}
