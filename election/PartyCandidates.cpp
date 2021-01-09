#include "partyCandidates.h"
#include "districtLoader.h"
#include "districtsArr.h"

namespace Elections
{

	PartyCandidates::PartyCandidates(istream& in, DistrictsArr* districts, CitizensArr* citizens) : PartyCandidates() {
		load(in, districts, citizens);
	}

	PartyCandidates::~PartyCandidates() {
		for (CandidatesData* x : *this) {
			delete[] x->_partyCandidates->getArr();
			delete x;
		}
	}

	void PartyCandidates::addTail(District* dis, bool createPartyCan) {
		if (!dis) {
			throw PartyCandidateException();
		}

		CandidatesData* temp;
		temp = new CandidatesData(dis, nullptr, 0, 0);

		if (createPartyCan) {
			temp->_partyCandidates = new CitizensArr;
		}
		this->push_back(temp);
	}

	void PartyCandidates::delHead() {
		CandidatesData* temp = *(begin());
		delete temp;
		(*this).pop_back();
	}

	void PartyCandidates::delTail() {
		CandidatesData* temp = this->back();
		delete temp;
		(*this).pop_back();
	}


	CandidatesData* PartyCandidates::searchDistrict(District*& dis)
	{
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");

		for (CandidatesData* x : *this) {
			if (dis->getId() == x->_dis->getId())
				return x;
		}
		return nullptr;
	}

	void PartyCandidates::addVote(District* dis) {
		CandidatesData* temp = searchDistrict(dis);
		temp->_numOfVotes++;
	}

	void PartyCandidates::appendPartyCandidate(District* dis, Citizen* cit) {
		CandidatesData* temp = searchDistrict(dis);
		if (temp) {
			temp->_partyCandidates->push_back(cit);
		}
		else {
			addTail(dis);
			this->back()->_partyCandidates->push_back(cit);
		}
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(int position) {
		if (position > (*this).size())
			throw out_of_range("PartyCandidates, getDistrictPartyCandidates");

		int i = 0;
		for (CandidatesData* x : (*this))
			if (i++ == position)
				return x->_partyCandidates;
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(District* dis) {
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");

		for (CandidatesData* x : (*this))
			if (x->_dis == dis)
				return x->_partyCandidates;
	}


	int PartyCandidates::getNumOfElectors(CandidatesData* data) {
		if (!data)
			throw invalid_argument("PartyCandidates, searchDistrict");

		return data->_numOfElectors;
	}

	int PartyCandidates::setNumOfElectors(CandidatesData* data) {
		if (!data)
			throw invalid_argument("PartyCandidates, searchDistrict");

		return data->_numOfElectors = data->_dis->getPartyRepNumber(data->_numOfVotes);
	}

	void PartyCandidates::addRepresentetives() {
		int numOfRep;
		for (CandidatesData* x : (*this)) {
			numOfRep = setNumOfElectors(x);
			for (int i = 0;i < numOfRep;i++) {
				x->_dis->appendToRepresentetives(x->_partyCandidates->at(i));
			}
		}
	}

	void PartyCandidates::setDistrictWinner(Party* party) {
		if (!party)
			throw invalid_argument("PartyCandidates, setDistrictWinner");
		
		for (CandidatesData* x : (*this)) {
			if (x->_dis->getWinnerVotes() < x->_numOfVotes) {
				x->_dis->setWinnerParty(party);
				x->_dis->setWinnerVotes(x->_numOfVotes);
			}
		}
	}

	int PartyCandidates::getPartyTotalElectors(Party* party) {
		int sumOfRep = 0;
		for (CandidatesData* x : (*this)) {
			if (typeid(*(x->_dis)) == typeid(UniformDis)) {
				if (x->_dis->getWinnerParty() == party) {
					sumOfRep += x->_dis->getNumOfRepresentatives();
				}
			}
			else {
				sumOfRep += getNumOfElectors(x);
			}
		}
		return sumOfRep;
	}

	int PartyCandidates::getPartyNumOfVotes() const {
		int sumOfVotes = 0;
		for (CandidatesData* x : (*this)) {
			sumOfVotes += x->_numOfVotes;
		}
		return sumOfVotes;
	}

	int PartyCandidates::getPartyNumOfElectors(District* dis) {
		if (!dis)
			throw invalid_argument("PartyCandidates, getPartyNumOfElectors");
		
		for (CandidatesData* x : (*this))
			if (x->_dis == dis) {
				return x->_numOfElectors;
		}

		throw runtime_error("PartyCandidates, getPartyNumOfElectors: There is no such district");
	}

	void PartyCandidates::printPartyCandidates() const {
		for (CandidatesData* x : (*this)){
			cout << "Name of District:" << x->_dis->getName() << endl;
			cout << x->_partyCandidates;
		}
	}

	void PartyCandidates::printResults(District* dis) const {
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");
		bool foundDis = false;
		for (CandidatesData* x : (*this)) {
			if (x->_dis == dis) {
				cout << "Party voters percentage in district: " << (float)((x->_numOfVotes) /
					(float)(x->_dis->getTotalVotes())) * (float)(100) << "%" << endl;
				cout << "Number of votes for party: " << x->_numOfVotes << endl;
				cout << endl;
				foundDis = true;
			}
		}

		if(!foundDis)
			throw runtime_error("PartyCandidates, printResults: There is no such district");
	}

	void PartyCandidates::save(ostream& out) const {
		int tempInt = this->size();
		if (!out || !out.good())
			throw invalid_argument("PartyCandidates, save(ostream& out)");

		out.write(rcastcc(&tempInt), sizeof(int));
		for (CandidatesData* x : (*this)) {
			tempInt = x->_dis->getId();
			out.write(rcastcc(&tempInt), sizeof(int));
			x->_partyCandidates->saveId(out);
			out.write(rcastcc(&(x->_numOfVotes)), sizeof(int));
		}

		if (!out.good()) {
			throw iostream::failure("PartyCandidates, save(out)");
		}
	}

	void PartyCandidates::load(istream& in, DistrictsArr* districts, CitizensArr* citizens) {
		int numOfNodes = 0, temp = 0;
		District* dis;
		CitizensArr* tempCit;
		if (!in || !in.good() || !districts)
			throw invalid_argument("PartyCandidates, load");

		try {
			in.read(rcastc(&numOfNodes), sizeof(int));
			for (int i = 0;i < numOfNodes; i++) {
				in.read(rcastc(&temp), sizeof(int));
				dis = districts->find(temp);
				addTail(dis, false);
				//this->back()->partyCandidates = new CitizensArr(in, citizens);
				in.read(rcastc(&(this->back()->_numOfVotes)), sizeof(int));
			}
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}

		if (!in.good()) {
			throw iostream::failure("PartyCandidates, load(in, districts, citizens)");
		}
	}


	void PartyCandidates::saveResults(ostream& out) const {
		int tempInt;
		if (!out || !out.good())
			throw invalid_argument("PartyCandidates, saveResults(ostream& out)");


		for (CandidatesData* x : (*this)) {
			tempInt = x->_numOfVotes;
			out.write(rcastcc(&(x->_numOfVotes)), sizeof(int));
		}

		if (!out.good()) {
			throw iostream::failure("PartyCandidates, saveResults(out)");
		}

	}

	void PartyCandidates::loadResults(istream& in) {
		int tempInt;
		if (!in || !in.good())
			throw invalid_argument("PartyCandidates, loadResults");

		for (CandidatesData* x : (*this)) {
			tempInt = x->_numOfVotes;
			in.read(rcastc(&(x->_numOfVotes)), sizeof(int));
		}

		if (!in.good()) {
			throw iostream::failure("PartyCandidates, loadResults(in)");
		}
	}
}