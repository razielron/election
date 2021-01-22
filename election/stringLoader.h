#pragma once
#include <string>
#include <istream>
#include <ostream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace Elections {
	void saveString(ostream& out, string str) {
		if (!out || !out.good()) {
			throw invalid_argument("saveString, parameter issue");
		}

		int len = str.size();
		out.write(rcastcc(&len), sizeof(int));
		out.write(rcastcc(str.c_str()), len * sizeof(char));

		if (!out.good()) {
			throw iostream::failure("Citizen, load, load didn't work");
		}
	}

	string loadString(istream& in) {
		if (!in || !in.good()) {
			throw invalid_argument("loadString, parameter issue");
		}

		string str;
		int len;
		char* buff;
		try {
			in.read(rcastc(&len), sizeof(int));
			buff = new char[len + 1];
			in.read(buff, len);
			buff[len] = '\0';
			str = buff;
			delete[] buff;

			if (!in.good()) {
				throw iostream::failure("Citizen, load, load didn't work");
			}

			return str;
		}
		catch (const bad_alloc&) {
			throw("bad allocate");
		}
	}
}