#pragma once 
#include "district.h"

namespace Elections
{
	class DevidedDis : public District
	{

	public:
		DevidedDis();
		DevidedDis(string name, int numOfRepresentatives);
		DevidedDis(istream& in);


	public:
		//returns district's type
		virtual string getType() const;
		//prints district's election results
		void printResults(PartiesArr* partiesArr);
	};
}