#pragma once
#include <list>
#include "PartyCandidateException.h"
#include "citizensArr.h"

namespace Elections
{

	struct data {
		District* dis;
		CitizensArr* partyCandidates;
		int numOfVotes;
		int numOfElectors;
	};


	class District;
	class DistrictsArr;
	class PartyCandidates: public list<data*>
	{
		//linked list functions
		private:
			void addTail(District* dis, bool allocPartyCan = true);
			//returns the ListItem node by given district
			data* searchDistrict(District*& dis);

		//Constructors + Distructors
		public:
			PartyCandidates() {}
			PartyCandidates(istream& in, DistrictsArr* districts, CitizensArr* citizens);
			~PartyCandidates();
			void addVote(District* dis);
			bool operator !() const { return this == nullptr; };
			void delHead();
			void delTail();

		//GETTERS
		public:
			CitizensArr* getDistrictPartyCandidates(int position);
			CitizensArr* getDistrictPartyCandidates(District* dis);
			int getNumOfElectors(data* listItem);
			int setNumOfElectors(data* listItem);
			int getPartyNumOfVotes() const;
			int getPartyNumOfElectors(District* dis);
			int getPartyTotalElectors(Party* party);


		public:
			//sets this party as a district winner by the number of votes
			void setDistrictWinner(Party* party);
			//adds candidate by given district and citizen
			void appendPartyCandidate(District* dis, Citizen* cit);
			//fills district's representetives accoreding to party's votes
			void addRepresentetives();
			//prints the list of candidates of this party for every district
			void printPartyCandidates() const;
			//prints the party results in each district
			void printResults(District* dis) const;

			//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in, DistrictsArr* districts, CitizensArr* citizens);
			void saveResults(ostream& out) const;
			void loadResults(istream& in);
	};
}
