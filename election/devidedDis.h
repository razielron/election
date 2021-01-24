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
		//prints district's data
		friend std::ostream& operator<<(std::ostream& os, const DevidedDis& devDis);
		//prints district's election results
		void printResults(PartiesArr* partiesArr);
		virtual void printDis();
	};
}