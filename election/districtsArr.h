#pragma once
#include "district.h"

namespace Elections {

	class DistrictsArr: public DynamicArr<District*>
	{
		//Constructors + Distructors
		public:
			DistrictsArr(): DynamicArr() {}
			DistrictsArr(District* dis) : DynamicArr(dis) {}
			DistrictsArr(istream& in);
			~DistrictsArr() {}
			bool operator !() const { return this == nullptr; };

			//Load and Save
		public:
			void printDis();
			void save(ostream& out) const;
			void load(istream& in);
	};

}