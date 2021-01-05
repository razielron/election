#pragma once
#include "citizen.h"

namespace Elections {
	
	class CitizensArr: public DynamicArr<Citizen*>
	{
		//Constructors + Distructors
		public:
			CitizensArr() : DynamicArr() {}
			CitizensArr(Citizen* cit) : DynamicArr(cit) {}
			CitizensArr(istream& in, Election* election);
			CitizensArr(istream& in, CitizensArr* citizens);
			~CitizensArr() {}


		//Load and Save
		public:
			void saveId(ostream& out) const;
			void loadById(istream& in, CitizensArr* citizens);
			void save(ostream& out) const;
			void load(istream& in, Election* election);
			void saveVotes(ostream& out) const;
			void loadVotes(istream& in, PartiesArr* parties);
	};

}