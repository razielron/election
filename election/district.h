#pragma once 
#include "citizensArr.h"
#include "Party.h"

namespace Elections
{

	class District
	{
		private:
			static int _districtSerialNumber;
			int _type;
			char* _name;
			int _districtId;
			int _numOfRepresentatives;
			int _totalVotes;
			int _winnerVotes;
			Party* _winner;
			CitizensArr* _representatives;
			CitizensArr* _voters;

		//Constructors + Distructors
		public:
			District() {}
			District(int type, char* name, int numOfRepresentatives);
			~District();

		//GETTERS
		public:
			inline const int getType() const { return _type; }
			inline const char* getName() const { return _name; }
			inline const int getDistrictNumber() { return _districtId; }
			inline const int getNumOfRepresentatives() { return _numOfRepresentatives; }
			inline const int getTotalVotes() { return _totalVotes; }
			inline const int getWinnerVotes() { return _winnerVotes; }
			inline const Party* getWinnerParty() { return _winner; }
			inline const CitizensArr* getVoters() { return _voters; }
			inline const CitizensArr* getRepresentetives() { return _representatives; }
			//returns didtrict's vote precentage
			inline const float getVotersPresentage() { return ((float)(_totalVotes)/(float)(_voters->getLogSize())*(float)(100)); }
			
		//SETTERS
		public:
			bool setWinnerVotes(int winnerVotes);
			bool setWinnerParty(Party* party);
			bool setNumOfRepresentatives(int numOfRepresentatives);

		public:
			//returns the representetives number by given party's votes number
			int getPartyRepNumber(int partyVote);
			//increase total votes in district by one
			void addVote() { _totalVotes++; }
			//add a citizen as a resident for that district
			void appendToVoters(Citizen* cit);
			//add a citizen to array of representetives
			void appendToRepresentetives(Citizen* cit);
			//prints district's data
			void printDistrict() const;
			//prints election results for that district
			void printResults();

			


	};

}