#pragma once 
#include "devidedDis.h"
#include "uniformDis.h"

namespace Elections
{
	enum class DistrictType {UNIFORM, DEVIDED};
	class DistrictLoader {
		public:
			static void save(ostream& out, District* dis);
			static District* load(istream& in);
	};
}