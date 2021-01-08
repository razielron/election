#pragma once 
#include <istream>
#include <ostream>
#include <cmath>
#include "citizensArr.h"
#include "districtException.h"
#include "party.h"

namespace Elections
{
	class District
	{
		private:
			static int _districtSerialNumber;			
			int _totalVotes;
			int _winnerVotes;
			
			CitizensArr* _representatives;
			CitizensArr* _voters;

		protected:
			string _name;
			int _districtId;
			int _numOfRepresentatives;
			Party* _winner;

		//Constructors + Distructors
		public:
			District() :_totalVotes(0), _winnerVotes(0), _representatives(nullptr), _voters(nullptr),
				_name(""),_districtId(0), _numOfRepresentatives(0), _winner(nullptr) {}
			District(string name, int numOfRepresentatives);
			District(istream& in);
			virtual ~District();
			
		//GETTERS
		public:
			
			inline const string getName() const { return _name; }
			inline const int getId() const { return _districtId; }
			inline const int getNumOfRepresentatives() const { return _numOfRepresentatives; }
			inline const int getTotalVotes() const { return _totalVotes; }
			inline const int getWinnerVotes() const { return _winnerVotes; }
			inline const Party* getWinnerParty() const { return _winner; }
			inline const CitizensArr* getVoters() const { return _voters; }
			inline const CitizensArr* getRepresentetives() const { return _representatives; }
			//returns didtrict's vote precentage
			inline const float getVotersPresentage() { return ((float)(_totalVotes)/(float)(_voters->size())*(float)(100)); }
			//returns voters precentage by given votes
			const float getVotersPresentage(int votes) { return ((float)(votes)/(float)(_totalVotes)*(float)(100)); }
			bool operator !() const { return this == nullptr; };

		//SETTERS
		public:
			void setWinnerVotes(int winnerVotes);
			void setWinnerParty(Party* party);
			void setNumOfRepresentatives(int numOfRepresentatives);

		public:
			//returns the representetives number by given party's votes number
			int getPartyRepNumber(int partyVote);
			//increase total votes in district by one
			void addVote() { _totalVotes++; }
			//add a citizen as a resident for that district
			void appendToVoters(Citizen* cit);
			//add a citizen to array of representetives
			void appendToRepresentetives(Citizen* cit);
			friend std::ostream& operator<<(std::ostream& os, const District& dis);

			//Load and Save
		public:
			virtual void save(ostream& out) const;
			virtual void load(istream& in);
	};

}