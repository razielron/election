#pragma once
#include "citizen.h"
#include "party.h"
#include "district.h"
#include "districtsArr.h"
#include "partiesArr.h"
#include "citizensArr.h"
#include <iostream>
using namespace std;

namespace Elections
{

	class Election
	{
		private:
			int _day;
			int _year;
			int _month;

		protected:
			CitizensArr* _citizens;
			PartiesArr* _parties;
			DistrictsArr* _districts;

		//Constructors + Distructors
		public:
			Election(int day, int month, int year);
			Election(istream& in);
			virtual ~Election();

		//GETTERS
		public:
			inline const int getDay() const { return _day; }
			inline const int getMonth() const { return _month; }
			inline const int getYear() const { return _year; }
			inline CitizensArr* getCitizens() const { return _citizens; }
			inline PartiesArr* getParties() const { return _parties; }
			inline DistrictsArr* getDistricts() const { return _districts; }

		public:
			//adds a party to party array
			void appendParty(Party* party);
			//adds a district to district array
			void appendDistrict(District* dis);
			//adds a citizen to citizens array
			void appendCitizen(Citizen* cit);
			//adds a candidate to party candidates for specific district
			void appendCandidateToList(Party* party, District* dis, Citizen* cit);
			//go over all of the parties and fill for each district the representetives
			void appendDistrictRep(District* dis, Citizen* cit);
			//sort parties array by the number of electors
			void sortPartiesByElectors() { _parties->sortByNumOfElectors(); }
			//sort parties array by total of votes
			void sortPartiesByTotalVotes() { _parties->sortByTotalVotes(); }

		public:
			//prints the date of the election
			void printDate() const { cout << _month << " " << _day << " " << _year << endl; }
			//finish the election - calculates all the votes
			void electionSummery() const;
			//prints the list of citizens
			void printCitizens() const;
			//prints the list of districts
			void printDistricts() const;
			//prints the list of parties
			void printParties() const;

		//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in);
			void saveVotes(ostream& out) const;
			void loadVotes(istream& in);
	};
}