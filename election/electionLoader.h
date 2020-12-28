#pragma once
#include "normalElection.h"
#include "simpleElection.h"
#include <iostream>
using namespace std;

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