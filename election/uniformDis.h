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
		//returns district's type
		virtual string getType() const;
		//prints district's election results
		void printResults();
	};
}