#pragma once
#include <string>
#include <exception>
#include <ostream>

using namespace std;

namespace Elections
{
	class ElectionException : public invalid_argument
	{
	public:
		ElectionException(string id) : invalid_argument(_what) {}

		virtual const char* what() const throw() {
			return _what;
		}

	private:
		const char _what[19] = "Election Exception";
	};
}