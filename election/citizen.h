#pragma once 

namespace Elections
{
	class District;
	class Party;
	class Citizen
	{
		private:
			char* _name;
			char _id[10];
			int _yearOfBirth;
			District* _dis;
			Party* _vote;

		//Constructors + Distructors
		public:
			Citizen() {};
			Citizen(char id[10], int yearOfBirth, char* name, District* dis);
			~Citizen();
			
		//GETTERS
		public:
			inline const char* getName() const { return _name; }
			inline const char* getId() { return _id; }
			inline const int getYearOfBirth() { return _yearOfBirth; }
			inline const District* getDistrict() { return _dis; }
			inline const Party* getVote() { return _vote; }

		public:
			//set the citizen's district
			bool setDistict(District* dis);
			//print the citizen's data
			void printCit() const;
			//add vote for this citizen by given party
			void vote(Party* party);
	};
}