#pragma once
#include "citizensArr.h"

namespace Elections
{
	class District;
	class DistrictsArr;
	class PartyCandidates
	{
		private:
			struct ListItem {
				District* dis;
				CitizensArr* partyCandidates;
				int numOfVotes;
				int numOfElectors;
				ListItem* next;
				ListItem* prev;
			};

			ListItem* _head;
			ListItem* _tail;

		//linked list functions
		private:
			void addTail(District* dis);
			void delHead(void);
			void delTail(void);
			//returns the ListItem node by given district
			ListItem* searchDistrict(District*& dis);

		//Constructors + Distructors
		public:
			PartyCandidates() : _head(nullptr), _tail(nullptr) {}
			PartyCandidates(istream& in, DistrictsArr* districts, CitizensArr* citizens);
			~PartyCandidates();
			void addVote(District* dis);

		//GETTERS
		public:
			CitizensArr* getDistrictPartyCandidates(int position);
			CitizensArr* getDistrictPartyCandidates(District* dis);
			int getNumOfNodes() const;
			int getNumOfElectors(ListItem* listItem);
			int setNumOfElectors(ListItem* listItem);
			int getPartyNumOfVotes() const;
			int getPartyNumOfElectors(District* dis);
			int getPartyTotalElectors(Party* party);

		public:
			//sets this party as a district winner by the number of votes
			bool setDistrictWinner(Party* party);
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
