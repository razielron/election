#pragma once
#include <istream>
#include <ostream>
#include <string>
#include <exception>
#include "citizenException.h"
#include "dynamicArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace Elections
{
	class Election;
	class District;
	class Party;
	class PartiesArr;
	class Citizen
	{
		private:
			string _name;
			string _id;
			int _yearOfBirth;
			District* _dis;
			Party* _vote;

		//Constructors + Distructors
		public:
			Citizen() : _yearOfBirth(0), _name(""), _id(""), _dis(nullptr), _vote(nullptr) {}
			Citizen(string id, int yearOfBirth, string name, District* dis);
			Citizen(istream& in, Election* election);
			~Citizen() {};
			bool operator!() const { return this == nullptr; }
			friend ostream& operator<<(ostream& os, const Citizen& cit);
			
		//GETTERS
		public:
			inline const string getName() const { return _name; }
			inline const string getId() const { return _id; }
			inline const int getYearOfBirth() const { return _yearOfBirth; }
			inline const District* getDistrict() const { return _dis; }
			inline const Party* getVote() const { return _vote; }

		public:
			//set the citizen's district
			bool setDistict(District* dis);
			//add vote for this citizen by given party
			void vote(Party* party);

		//Load and Save
		public:
			void saveId(ostream& out) const;
			void save(ostream& out) const;
			void load(istream& in, Election* election);
			void saveVote(ostream& out) const;
			void loadVote(istream& in, PartiesArr* parties);
	};
}