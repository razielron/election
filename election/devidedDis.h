#pragma once 
#include <iostream>
#include "district.h"

namespace Elections
{
	class PartiesArr;
	class DevidedDis : public District
	{

	public:
		DevidedDis();
		DevidedDis(char* name, int numOfRepresentatives);
		DevidedDis(istream& in);


	public:
		//prints district's data
		friend std::ostream& operator<<(std::ostream& os, const DevidedDis& devDis);
		//prints district's election results
		void printResults(PartiesArr* partiesArr);
	};
}