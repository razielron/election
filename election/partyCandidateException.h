#pragma once
#include <exception>
#include <ostream>
using namespace std;

namespace Elections
{
	class PartyCandidateException : public invalid_argument
	{
	public:
		PartyCandidateException() : invalid_argument(_what) {}
		virtual const char* what() const throw() {
			return _what;
		}

	private:
		const char _what[26] = "PartyCandidates Exception";
	};
}