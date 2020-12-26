#pragma once
#include <iostream>
using namespace std;

namespace Elections
{
	class District;
	class Party;
	class Citizen
	{
		private:
			char* _name;
			char* _id;
			int _yearOfBirth;
			District* _dis;
			Party* _vote;

		//Constructors + Distructors
		public:
			Citizen();
			Citizen(char* id, int yearOfBirth, char* name, District* dis);
			~Citizen();
			friend ostream& operator<<(ostream& os, const Citizen& cit);
			
		//GETTERS
		public:
			inline const char* getName() const { return _name; }
			inline const char* getId() const { return _id; }
			inline const int getYearOfBirth() const { return _yearOfBirth; }
			inline const District* getDistrict() const { return _dis; }
			inline const Party* getVote() const { return _vote; }

		public:
			//set the citizen's district
			bool setDistict(District* dis);
			//add vote for this citizen by given party
			void vote(Party* party);
	};
}