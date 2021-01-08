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
			friend ostream& operator<<(ostream& os, const DynamicArr<District*>& disArr);
			bool operator !() const { return this == nullptr; };

			//Load and Save
		public:
			void save(ostream& out) const;
			void load(istream& in);
	};

}