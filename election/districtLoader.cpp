#include "districtLoader.h"

namespace Elections
{
	void DistrictLoader::save(ostream& out, District* dis){
		if (!dis || !out) {
			throw invalid_argument("DistrictLoader, save");
		}
		DistrictType type;
		if ((typeid(*dis)) == (typeid(UniformDis))) {
			type = DistrictType::UNIFORM;
		}	
		else {
			type = DistrictType::DEVIDED;
		}
		out.write(rcastcc(&type), sizeof(DistrictType));
			dis->save(out);

		if (!out.good()) {
			throw iostream::failure("DistrictLoader, save issues");
		}
	}

	District* DistrictLoader::load(istream& in) {
		if (!in || !in.good())
			throw invalid_argument("DistrictLoader, load(istream& in)");

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
				throw runtime_error("There is no suitable type");
			}
		
		if (!in.good()) {
			throw iostream::failure("DistrictLoader, load issues");
		}
	}
}	