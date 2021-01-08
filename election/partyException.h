#pragma once
#include <exception>
#include <ostream>
using namespace std;

namespace Elections
{
	class PartyException : public invalid_argument
	{
	public:
		PartyException(int partyId) : invalid_argument(_what), _partyId(id) {}
		int getId() const { return _partyId; }
		virtual const char* what() const throw() {
			return _what;
		}

	private:
		int _partyId;
		const char _what[16] = "Party Exception";
	};
}