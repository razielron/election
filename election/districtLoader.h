#pragma once 
#include <iostream>
#include "district.h"

namespace Elections
{
	enum class DistrictType {UNIFORM, DEVIDED};
	class DistrictLoader {
		public:
			static void save(ostream& out, District* dis);
			static District* load(istream& in);
	};
}