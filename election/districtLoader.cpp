#pragma once 
#include "districtLoader.h"
#include "uniformDis.h"
#include "devidedDis.h"
#include <iostream>
#include <typeinfo>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	void DistrictLoader::save(ostream& out, District* dis){
		DistrictType type;
		if ((typeid(*dis)) == (typeid(UniformDis))) {
			type = DistrictType::UNIFORM;
		}	
		else {
			type = DistrictType::DEVIDED;
		}
		out.write(rcastcc(&type), sizeof(DistrictType));
		dis->save(out);

		//next ex we will implament try&catch
		if (!out.good()) {
			cout << "DistrictArr Save issue" << endl;
			exit(-1);
		}
	}

	District* DistrictLoader::load(istream& in) {
		DistrictType type;
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
			case DistrictType::UNIFORM: {
				return new UniformDis(in);
				break;
			}
			case DistrictType::DEVIDED: {
				return new DevidedDis(in);
				break;
			}
			default:
				return nullptr;
		}

		//next ex we will implament try&catch
		if (!in.good()) {
			cout << "DistrictArr load issue" << endl;
			exit(-1);
		}
	}
}	