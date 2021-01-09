#pragma once
#include <string>
#include <exception>

using namespace std;

namespace Elections
{
	class CitizenException : public invalid_argument
	{
	public:
		CitizenException(string id) : invalid_argument(_what), _id(id) {}
		string getId() const { return _id; }

		virtual const char* what() const throw() {
			return _what;
		}

	private:
		string _id;
		const char _what[18] = "Citizen Exception";
	};
}