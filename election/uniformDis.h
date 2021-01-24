#pragma once 
#include "district.h"

namespace Elections
{
	class UniformDis : public District
	{

	//getters
	public:
		UniformDis();
		UniformDis(string name, int numOfRepresentatives);
		UniformDis(istream& in);
	

	public:
		virtual void printDis();
		//prints district's data
		friend std::ostream& operator<<(std::ostream& os, const UniformDis& uniDis);
		//prints district's election results
		void printResults();
	};
}