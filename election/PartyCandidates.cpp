#include "partyCandidates.h"
#include "district.h"
#include <string.h>
#include <iostream>
#include <cmath>
using namespace std;

namespace Elections
{
	PartyCandidates::PartyCandidates() {
		_head = nullptr;
		_tail = nullptr;
	}

	PartyCandidates::~PartyCandidates() {
		ListItem* temp = _head;
		while (temp) {
			delete[] temp->partyCandidates;
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
			if (dis->getDistrictNumber() == temp->dis->getDistrictNumber())
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

	int PartyCandidates::getNumOfElectors(ListItem* listItem) {
		return listItem->numOfElectors;
	}

	int PartyCandidates::setNumOfElectors(ListItem* listItem) {
		return listItem->numOfElectors = listItem->dis->getPartyRepNumber(listItem->numOfVotes);
	}
	/*
	int PartyCandidates::getNumOfRep(District* dis) {
		ListItem* temp = _head;
		while (temp) {
			if (temp->dis == dis)
				return setNumOfElectors(temp);
			temp = temp->next;
		}
		return 0;
	}
	*/
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

	int PartyCandidates::getPartyTotalElectors(Party* party) { //HW2
		ListItem* temp = _head;
		int sumOfRep = 0;
		while (temp) {
			if (!temp->dis->getType()) {
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

	int PartyCandidates::getPartyNumOfVotes() {
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
		while (temp && (temp->dis != dis)){
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
		cout << "Party voters percentage in district: " << (float)((temp->numOfVotes) / (float)(temp->dis->getTotalVotes())) * (float)(100) << "%" << endl;
		cout << "Number of votes for party: " << temp->numOfVotes << endl;
		cout << endl;
	}
}