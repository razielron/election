#pragma once 
#include <iostream>
#include "district.h"

namespace Elections
{
	class UniformDis : public District
	{

	//getters
	public:
		UniformDis();
		UniformDis(char* name, int numOfRepresentatives);
	

	public:
		//prints district's data
		friend std::ostream& operator<<(std::ostream& os, const UniformDis& uniDis);
		//prints district's election results
		void printResults();
	};
}