#include "district.h"

namespace Elections
{
	int District::_districtSerialNumber = 0;

	District::District(string name, int numOfRepresentatives):
		_name(name), _numOfRepresentatives(numOfRepresentatives), _winnerVotes(0),
		_totalVotes(0){
		if (numOfRepresentatives < 0)
			throw DistrictException(_districtId);

		_winner = nullptr;
		try {
			_representatives = new CitizensArr;
			_voters = new CitizensArr;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			delete[] _representatives;
			exit(1);
		}
		_districtId = _districtSerialNumber++;
	}

	District::District(istream& in) : _winnerVotes(0), _winner(nullptr) {
		if (!in || !in.good()) {
			throw invalid_argument("District, Constractor(in)");
		}

		try {
			_representatives = new CitizensArr;
			_voters = new CitizensArr;
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			delete[] _representatives;
			exit(1);
		}

		load(in);
	}

	District::~District() {
		delete _representatives;
		delete _voters;
	}

	void District::operator =(District& dis) {
		_name = dis.getName();
		_districtId = dis.getId();
		_numOfRepresentatives = dis.getNumOfRepresentatives();
		_totalVotes = dis.getTotalVotes();
		_winnerVotes = dis.getWinnerVotes();
		_winner = dis.getWinnerParty();
		_voters = dis.getVoters();
		_representatives = dis.getRepresentetives();
	}

	int District::getPartyRepNumber(int partyVote) {
		int occupiedRep;
		if (partyVote < 0) {
			throw invalid_argument("District, getPartyRepNumber");
		}
		if ((float)(_totalVotes) * (float)(_numOfRepresentatives) == 0) {
			throw logic_error("District, getPartyRepNumber, Division by zero");
		}

		int repNum = round(((float)(partyVote) / (float)(_totalVotes) * (float)(_numOfRepresentatives)));
		occupiedRep = _representatives->size();

		if ((repNum + occupiedRep) > _numOfRepresentatives)
			return --repNum;
		return repNum;
	}

	void District::setNumOfRepresentatives(int numOfRepresentatives) {
		if (numOfRepresentatives <= 0)
			throw invalid_argument("District, setNumOfRepresentatives");
		_numOfRepresentatives = numOfRepresentatives;
	}

	void District::setWinnerVotes(int winnerVotes) {
		if (!winnerVotes)
			throw invalid_argument("District, setWinnerVotes");
		_winnerVotes = winnerVotes;
	}

	void District::setWinnerParty(Party* party) {
		if (!party)
			throw invalid_argument("District, setWinnerParty");

		_winner = party;
	}

	void District::appendToVoters(Citizen* cit) {
		_voters->push_back(cit);
	}

	void District::appendToRepresentetives(Citizen* cit) {
		_representatives->push_back(cit);
	}

	ostream& operator<<(ostream& os, const District& dis) {
		if (!os || !dis)
			throw invalid_argument("District, << ");
		
			os << "-------------DISTRICT-START------------" << endl;
			os << "District ID: " << dis.getId() << endl;
			os << "District Type: " << dis.getType() << endl;
			os << "Name of district: " << dis.getName() << endl;
			os << "Number of representetive: " << dis.getNumOfRepresentatives() << endl;
			os << "--------------DISTRICT-END-------------" << endl;

		return os;
	}

	void District::save(ostream& out) const {
		
		if (!out || !out.good())
			throw invalid_argument("District, save(ostream& out), parameter issues");


		out.write(rcastcc(&_districtSerialNumber), sizeof(int));
		StringLoader::saveString(out, _name);
		out.write(rcastcc(&_districtId), sizeof(int));		
		out.write(rcastcc(&_numOfRepresentatives), sizeof(int));
		out.write(rcastcc(&_totalVotes), sizeof(int));
		
		if (!out.good()) {
			throw iostream::failure("District, save(out)");
		}
	}

	void District::load(istream& in) {
		if (!in || !in.good())
			throw invalid_argument("District, load(istream& in)");
		
		int tempSize = 0, tempSerial=0, len;

		try {
			in.read(rcastc(&tempSerial), sizeof(int));
			if (tempSerial > _districtSerialNumber)
				_districtSerialNumber = tempSerial;
			_name = StringLoader::loadString(in);
			in.read(rcastc(&_districtId), sizeof(int));
			in.read(rcastc(&_numOfRepresentatives), sizeof(int));
			in.read(rcastc(&_totalVotes), sizeof(int));

			if (!in.good()) {
				throw iostream::failure("District, load(in)");
			}
		}
		catch (const bad_alloc&) {
			throw("bad allocate");
		}
	}
}

