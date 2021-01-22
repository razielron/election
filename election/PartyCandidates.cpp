#include "partyCandidates.h"
#include "districtLoader.h"
#include "districtsArr.h"

namespace Elections
{

	PartyCandidates::PartyCandidates(istream& in, DistrictsArr* districts, CitizensArr* citizens) : PartyCandidates() {
		load(in, districts, citizens);
	}

	PartyCandidates::~PartyCandidates() {
		iterator i = begin();
		while (i != end()) {
			delete[] (*i)->partyCandidates->getArr();
			delete (*i);
			this->erase(i);
			i = begin();
		}
	}

	void PartyCandidates::addTail(District* dis, bool allocPartyCan) {
		if (!dis)
			throw PartyCandidateException();
		data* temp;
		try {
			temp = new data();
		}
		catch (bad_alloc& err) {
			cout << err.what() << endl;
			exit(1);
		}

		temp->dis = dis;
		temp->numOfVotes = 0;
		temp->numOfElectors = 0;
		temp->partyCandidates = nullptr;
		if (allocPartyCan) {
			try {
				temp->partyCandidates = new CitizensArr;
			}
			catch (bad_alloc& err) {
				cout << err.what() << endl;
				exit(1);
			}
		}
		this->push_back(temp);
	}

	void PartyCandidates::delHead(void) {
		data* temp = *(begin());
		delete temp;
		(*this).pop_back();
	}

	void PartyCandidates::delTail(void) {
		data* temp = this->back();
		delete temp;
		(*this).pop_back();
	}


	data* PartyCandidates::searchDistrict(District*& dis)
	{
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");

		for (data* x : *this) {
			if (dis->getId() == x->dis->getId())
				return x;
		}
		return nullptr;
	}

	void PartyCandidates::addVote(District* dis) {
		data* temp = searchDistrict(dis);
		temp->numOfVotes++;
	}

	void PartyCandidates::appendPartyCandidate(District* dis, Citizen* cit) {
		data* temp = searchDistrict(dis);
		if (temp) {
			temp->partyCandidates->push_back(cit);
		}
		else {
			addTail(dis);
			this->back()->partyCandidates->push_back(cit);
		}
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(int position) {
		if (position > (*this).size())
			throw out_of_range("PartyCandidates, getDistrictPartyCandidates");

		int i = 0;
		for (data* x : (*this))
			if (i++ == position)
				return x->partyCandidates;
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(District* dis) {
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");

		for (data* x : (*this))
			if (x->dis == dis)
				return x->partyCandidates;
	}


	int PartyCandidates::getNumOfElectors(data* dt) {
		if (!dt)
			throw invalid_argument("PartyCandidates, searchDistrict");

		return dt->numOfElectors;
	}

	int PartyCandidates::setNumOfElectors(data* dt) {
		if (!dt)
			throw invalid_argument("PartyCandidates, searchDistrict");

		return dt->numOfElectors = dt->dis->getPartyRepNumber(dt->numOfVotes);
	}

	void PartyCandidates::addRepresentetives() {
		int numOfRep;
		for (data* x : (*this)) {
			numOfRep = setNumOfElectors(x);
			for (int i = 0;i < numOfRep;i++) {
				x->dis->appendToRepresentetives(x->partyCandidates->at(i));
			}
		}
	}

	void PartyCandidates::setDistrictWinner(Party* party) {
		if (!party)
			throw invalid_argument("PartyCandidates, setDistrictWinner");

		for (data* x : (*this)) {
			if (x->dis->getWinnerVotes() < x->numOfVotes) {
				x->dis->setWinnerParty(party);
				x->dis->setWinnerVotes(x->numOfVotes);
			}
		}
	}

	int PartyCandidates::getPartyTotalElectors(Party* party) {
		int sumOfRep = 0;
		for (data* x : (*this)) {
			if (typeid(*(x->dis)) == typeid(UniformDis)) {
				if (x->dis->getWinnerParty() == party) {
					sumOfRep += x->dis->getNumOfRepresentatives();
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
		for (data* x : (*this)) {
			sumOfVotes += x->numOfVotes;
		}
		return sumOfVotes;
	}

	int PartyCandidates::getPartyNumOfElectors(District* dis) {
		if (!dis)
			throw invalid_argument("PartyCandidates, getPartyNumOfElectors");

		for (data* x : (*this))
			if (x->dis == dis) {
				return x->numOfElectors;
			}

		throw runtime_error("PartyCandidates, getPartyNumOfElectors: There is no such district");
	}

	void PartyCandidates::printPartyCandidates() const {
		for (data* x : (*this)) {
			cout << "Name of District:" << x->dis->getName() << endl;
			cout << *(x->partyCandidates);
		}
	}

	void PartyCandidates::printResults(District* dis) const {
		if (!dis)
			throw invalid_argument("PartyCandidates, searchDistrict");
		bool foundDis = false;
		for (data* x : (*this)) {
			if (x->dis == dis) {
				cout << "Party voters percentage in district: " << (float)((x->numOfVotes) /
					(float)(x->dis->getTotalVotes())) * (float)(100) << "%" << endl;
				cout << "Number of votes for party: " << x->numOfVotes << endl;
				cout << endl;
				foundDis = true;
			}
		}

		if (!foundDis)
			throw runtime_error("PartyCandidates, printResults: There is no such district");
	}

	void PartyCandidates::save(ostream& out) const {
		int tempInt = this->size();
		if (!out || !out.good())
			throw invalid_argument("PartyCandidates, save(ostream& out)");

		out.write(rcastcc(&tempInt), sizeof(int));
		for (data* x : (*this)) {
			tempInt = x->dis->getId();
			out.write(rcastcc(&tempInt), sizeof(int));
			x->partyCandidates->saveId(out);
			out.write(rcastcc(&(x->numOfVotes)), sizeof(int));
		}

		if (!out.good()) {
			throw iostream::failure("PartyCandidates, save(out)");
		}
	}

	void PartyCandidates::load(istream& in, DistrictsArr* districts, CitizensArr* citizens) {
		int numOfNodes = 0, temp = 0;
		District* dis;
		CitizensArr* tempCit = nullptr;
		if (!in || !in.good() || !districts)
			throw invalid_argument("PartyCandidates, load");

		try {
			in.read(rcastc(&numOfNodes), sizeof(int));
			for (int i = 0;i < numOfNodes; i++) {
				in.read(rcastc(&temp), sizeof(int));
				dis = districts->find(temp);
				addTail(dis, false);
				this->back()->partyCandidates = new CitizensArr(in, citizens);
				in.read(rcastc(&(this->back()->numOfVotes)), sizeof(int));
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


		for (data* x : (*this)) {
			tempInt = x->numOfVotes;
			out.write(rcastcc(&(x->numOfVotes)), sizeof(int));
		}

		if (!out.good()) {
			throw iostream::failure("PartyCandidates, saveResults(out)");
		}

	}

	void PartyCandidates::loadResults(istream& in) {
		int tempInt;
		if (!in || !in.good())
			throw invalid_argument("PartyCandidates, loadResults");

		for (data* x : (*this)) {
			tempInt = x->numOfVotes;
			in.read(rcastc(&(x->numOfVotes)), sizeof(int));
		}

		if (!in.good()) {
			throw iostream::failure("PartyCandidates, loadResults(in)");
		}
	}
}