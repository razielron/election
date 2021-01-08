#pragma once
#include <exception>
#include <ostream>
using namespace std;

namespace Elections
{
	class DistrictException : public invalid_argument
	{
	public:
		DistrictException(int districtId) : invalid_argument(_what), _districtId(districtId) {}
		int getId() const { return _districtId; }
		virtual const char* what() const throw() {
			return _what;
		}

	private:
		int _districtId;
		const char _what[19] = "District Exception";
	};
}