#pragma once
#include "normalElection.h"
#include "simpleElection.h"


namespace Elections
{
	enum class ElectionType { normalElection, simpleElection };

	class ElectionLoader
	{
	public:
		static void save(ostream& out, Election* elecion);
		static Election* load(istream& in);
	};
}