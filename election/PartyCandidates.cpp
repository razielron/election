#include "partyCandidates.h"
#include "uniformDis.h"
#include "devidedDis.h"
#include "district.h"
#include "districtsArr.h"
#include "citizensArr.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <typeinfo>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{

	PartyCandidates::PartyCandidates(istream& in, DistrictsArr* districts, CitizensArr* citizens) : PartyCandidates() {
		load(in, districts, citizens);
	}

	PartyCandidates::~PartyCandidates() {
		ListItem* temp = _head;
		while (temp) {
			temp->partyCandidates->deleteArrPointer();
			temp = temp->next;
			delete _head;
			_head = temp;
		}
	}

	void PartyCandidates::addTail(District* dis) {
		ListItem* temp = new ListItem();
		temp->dis = dis;
		temp->numOfVotes = 0;
		temp->numOfElectors = 0;
		temp->partyCandidates = new CitizensArr;
		temp->prev = _tail;
		temp->next = nullptr;
		if (!_tail) {
			_head = temp;
		}
		else {
			_tail->next = temp;
		}

		_tail = temp;
	}

	void PartyCandidates::delHead(void) {
		ListItem* temp = _head->next;
		delete _head;
		_head = temp;
	}

	void PartyCandidates::delTail(void) {
		ListItem* temp = _tail->prev;
		delete _tail;
		_tail = temp;
	}


	PartyCandidates::ListItem* PartyCandidates::searchDistrict(District*& dis)
	{
		ListItem* temp = _head;
		while (temp) {
			if (dis->getId() == temp->dis->getId())
				return temp;
			temp = temp->next;
		}
		return nullptr;
	}

	void PartyCandidates::addVote(District* dis) {
		ListItem* temp = searchDistrict(dis);
		if (!temp) {
			cout << "NO Candidates FOR THAT DISTRICT" << endl;
			return;
		}

		temp->numOfVotes++;
	}

	void PartyCandidates::appendPartyCandidate(District* dis, Citizen* cit) {
		ListItem* temp = searchDistrict(dis);
		if (temp) {
			temp->partyCandidates->appendCitizen(cit);
		}
		else {
			addTail(dis);
			_tail->partyCandidates->appendCitizen(cit);
		}
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(int position) {
		ListItem* temp = _head;
		for (int i = 0;i < position;i++)
			temp = temp->next;
		return temp->partyCandidates;
	}

	CitizensArr* PartyCandidates::getDistrictPartyCandidates(District* dis) {
		ListItem* temp = _head;
		while (temp->dis != dis) {
			temp = temp->next;
		}
		return temp->partyCandidates;
	}

	int PartyCandidates::getNumOfNodes() const {
		int counter = 0;
		ListItem* temp = _head;
		while (temp) {
			counter++;
			temp = temp->next;
		}
		return counter++;
	}

	int PartyCandidates::getNumOfElectors(ListItem* listItem) {
		return listItem->numOfElectors;
	}

	int PartyCandidates::setNumOfElectors(ListItem* listItem) {
		return listItem->numOfElectors = listItem->dis->getPartyRepNumber(listItem->numOfVotes);
	}

	void PartyCandidates::addRepresentetives() {
		int numOfRep;
		ListItem* temp = _head;
		while (temp) {
			numOfRep = setNumOfElectors(temp);
			for (int i = 0;i < numOfRep;i++) {
				temp->dis->appendToRepresentetives(temp->partyCandidates->getCit(i));
			}
			temp = temp->next;
		}
	}

	bool PartyCandidates::setDistrictWinner(Party* party) {
		ListItem* temp = _head;
		while (temp) {
			if (temp->dis->getWinnerVotes() < temp->numOfVotes) {
				temp->dis->setWinnerParty(party);
				temp->dis->setWinnerVotes(temp->numOfVotes);
			}
			temp = temp->next;
		}
		return true;
	}

	int PartyCandidates::getPartyTotalElectors(Party* party) {
		ListItem* temp = _head;
		int sumOfRep = 0;
		while (temp) {
			if (typeid(*(temp->dis)) == typeid(UniformDis)) {
				if (temp->dis->getWinnerParty() == party) {
					sumOfRep += temp->dis->getNumOfRepresentatives();
				}
			}
			else {
				sumOfRep += getNumOfElectors(temp);
			}
			temp = temp->next;
		}
		return sumOfRep;
	}

	int PartyCandidates::getPartyNumOfVotes() const {
		ListItem* temp = _head;
		int sumOfVotes = 0;
		while (temp) {
			sumOfVotes += temp->numOfVotes;
			temp = temp->next;
		}
		return sumOfVotes;
	}

	int PartyCandidates::getPartyNumOfElectors(District* dis) {
		ListItem* temp = _head;
		while (temp && (temp->dis != dis)) {
			temp = temp->next;
		}
		return temp->numOfElectors;
	}

	void PartyCandidates::printPartyCandidates() const {
		ListItem* temp = _head;
		while (temp) {
			cout << "Name of District:" << temp->dis->getName() << endl;
			cout << temp->partyCandidates;
			temp = temp->next;
		}
	}

	void PartyCandidates::printResults(District* dis) const {
		ListItem* temp = _head;
		while (temp && (temp->dis != dis))
			temp = temp->next;
		cout << "Party voters percentage in district: " << (float)((temp->numOfVotes) /
			(float)(temp->dis->getTotalVotes())) * (float)(100) << "%" << endl;
		cout << "Number of votes for party: " << temp->numOfVotes << endl;
		cout << endl;
	}

	void PartyCandidates::save(ostream& out) const {
		int tempInt = getNumOfNodes();
		out.write(rcastcc(&tempInt), sizeof(int));
		ListItem* temp = _head;
		while (temp) {
			tempInt = temp->dis->getId();
			out.write(rcastcc(&tempInt), sizeof(int));
			temp->partyCandidates->saveId(out);
			out.write(rcastcc(&(temp->numOfVotes)), sizeof(int));
			temp = temp->next;
		}
	}

	void PartyCandidates::load(istream& in, DistrictsArr* districts, CitizensArr* citizens) {
		int numOfNodes = 0, temp = 0;
		District* dis;
		CitizensArr* tempCit;

		in.read(rcastc(&numOfNodes), sizeof(int));
		for (int i = 0;i < numOfNodes; i++) {
			in.read(rcastc(&temp), sizeof(int));
			dis = districts->getDistrict(temp);
			addTail(dis);
			delete _tail->partyCandidates;
			_tail->partyCandidates = new CitizensArr(in, citizens);
			in.read(rcastc(&(_tail->numOfVotes)), sizeof(int));
		}
	}

	void PartyCandidates::saveResults(ostream& out) const {
		ListItem* temp = _head;
		int tempInt;

		while (temp) {
			tempInt = temp->numOfVotes;
			out.write(rcastcc(&(temp->numOfVotes)), sizeof(int));
			temp = temp->next;
		}
	}

	void PartyCandidates::loadResults(istream& in) {
		int tempInt;
		ListItem* temp = _head;
		int numOfNodes = getNumOfNodes();
		while (temp) {
			tempInt = temp->numOfVotes;
			in.read(rcastc(&(temp->numOfVotes)), sizeof(int));
			temp = temp->next;
		}
	}
}