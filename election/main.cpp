#pragma once 
#include "party.h"
#include "district.h"
#include "election.h"
#include "citizen.h"
#include <string.h>
#include <iostream>
using namespace std;
using namespace Elections;

namespace Elections {
	//Prints the menu
	void menu() {
		cout << endl << endl << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "Press 1 for adding a district" << endl;
		cout << "Press 2 for adding a citizen" << endl;
		cout << "Press 3 for adding a party" << endl;
		cout << "Press 4 for adding a citizen as party candidate" << endl;
		cout << "Press 5 to display all districts" << endl;
		cout << "Press 6 to display all citizens" << endl;
		cout << "Press 7 to display all parties" << endl;
		cout << "Press 8 to vote" << endl;
		cout << "Press 9 to display election results" << endl;
		cout << "Press 0 to exit programe" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << endl << endl << endl;
	}

	//get input from user to add new sitrict
	void addNewDistrict(Election* election) {
		char name[256];
		int numOfRep = 0;
		int type;

		cout << "Enter type of district (0/1): ";
		cin >> type;
		while (type != 0 && type != 1) {
			cout << "Enter valid type of district (0/1): ";
			cin >> type;
		}

		cout << "Enter name of district: ";
		cin >> name;
		cout << "Enter Number of representetives: ";
		cin >> numOfRep;

		while (numOfRep <= 0) {
			cout << "Enter Valid number Of Rep" << endl;
			cin >> numOfRep;
		}

		District* dis = new District(type, name, numOfRep);
		election->appendDistrict(dis);
	}

	//returns true if the id is valid else false
	bool isValidId(char id[10]) {
		for (int i = 0;i < 9;i++)
			if (!(id[i] && id[i] <= '9' && id[i] >= '0')) {
				return false;
			}
		return true;
	}

	//get input from user to add new citizen
	void addNewCitizen(Election* election) {
		int yearOfBirth, districtId;
		char name[256];
		char id[10];
		District* dis;

		if (!(election->getDistricts()->getLogSize())) {
			cout << "There are no distrits " << endl;
			return;
		}

		cout << "Enter name of citizen: ";
		cin >> name;

		cout << "Enter ID: ";
		cin >> id;
		while (!(isValidId(id))) {
			cout << "Enter correct ID" << endl;
			cin >> id;
		}
		id[9] = '\0';

		cout << "Enter year of birth: ";
		cin >> yearOfBirth;
		while (yearOfBirth <= 1900 || yearOfBirth >= 2020) {
			cout << "Enter Valid year of birth" << endl;
			cin >> yearOfBirth;
		}

		cout << "Enter district ID: ";
		cin >> districtId;

		while (!(dis = election->getDistricts()->getDistrict(districtId))) {
			cout << "Enter valid district ID" << endl;
			cin >> districtId;
		}

		Citizen* cit = new Citizen(id, yearOfBirth, name, dis);
		election->appendCitizen(cit);
	}

	//get input from user to add new party
	void addNewParty(Election* election) {
		char name[256];
		char id[10];
		Citizen* temp = nullptr;
		
		if (!(election->getCitizens()->getLogSize())) {
			cout << "There are no citizens " << endl;
			return;
		}


		cout << "Enter name of Party: ";
		cin >> name;

		cout << "Enter ID of prime minister candidate: ";
		cin >> id;
		while (!(isValidId(id) && (temp = election->getCitizens()->getCit(id)))) {
			cout << "Enter correct ID / There is no citizen with this ID" << endl;
			cin >> id;
		}
		id[9] = '\0';

		Party* party = new Party(name, temp);
		election->appendParty(party);
	}

	//get input from user to add new party's candidate
	void addNewCandidate(Election* election) {
		char id[10];
		Citizen* citTemp = nullptr;
		Party* partyTemp = nullptr;
		District* disTemp = nullptr;
		int partyId, districtId;

		cout << "Enter citizen ID: ";
		cin >> id;
		while (!(isValidId(id) && (citTemp = election->getCitizens()->getCit(id)))) {
			cout << "Enter correct ID / There is no citizen with this ID" << endl;
			cin >> id;
		}
		id[9] = '\0';

		cout << "Enter Party ID: ";
		cin >> partyId;
		while (!(partyTemp = election->getParties()->getParty(partyId))) {
			cout << "Enter valid Party ID: ";
			cin >> partyId;
		}

		cout << "Enter district ID: ";
		cin >> districtId;
		while (!(disTemp = election->getDistricts()->getDistrict(districtId))) {
			cout << "Enter valid district ID" << endl;
			cin >> districtId;
		}

		partyTemp->appendCandidateToList(disTemp, citTemp);
	}

	//get input from user to add new Vote
	void vote(Election* election) {
		char id[10];
		int partyId;
		Citizen* citTemp = nullptr;
		Party* partyTemp = nullptr;

		cout << "Enter citizen ID: ";
		cin >> id;
		while (!(isValidId(id) && (citTemp = election->getCitizens()->getCit(id)))) {
			cout << "Enter correct ID / There is no citizen with this ID" << endl;
			cin >> id;
		}
		id[9] = '\0';

		if (citTemp->getVote()) {
			cout << "This citizen has already voted" << endl;
			return;
		}

		cout << "Enter Party ID: ";
		cin >> partyId;
		while (!(partyTemp = election->getParties()->getParty(partyId))) {
			cout << "Enter valid Party ID: ";
			cin >> partyId;
		}

		citTemp->vote(partyTemp);
	}

	//Prints all created districts
	void printDistricts(Election* election) {
		election->printDistricts();
	}

	//Prints all created citizens
	void printCitizens(Election* election) {
		election->printCitizens();
	}
	
	//Prints all created parties
	void printParties(Election* election) {
		election->printParties();
	}

	//Prints all election's results
	void printElectionResults(Election* election) {
		cout << "------------------ELECTION-RESULTS-START----------------" << endl;
		election->electionSummery();
		election->sortPartiesByElectors();
		election->printResults();
		election->getParties()->printResults();
		cout << "-------------------ELECTION-RESULTS-END----------------" << endl;
	}

}




void main() {
	int input=1, day=1, month=1, year=2020;
	
	cout << "Enter election date:" << endl << "Day: ";
	cin >> day;
	cout << "Month: ";
	cin >> month;
	cout << "Year: ";
	cin >> year;
	
	Election* election = new Election(day,month,year);


	while (input) {
		menu();
		cin >> input;
		switch (input)
		{
		case 1:
			addNewDistrict(election);
			break;
		case 2:
			addNewCitizen(election);
			break;
		case 3:
			addNewParty(election);
			break;
		case 4:
			addNewCandidate(election);
			break;
		case 5:
			printDistricts(election);
			break;
		case 6:
			printCitizens(election);
			break;
		case 7:
			printParties(election);
			break;
		case 8:
			vote(election);
			break;
		case 9:
			printElectionResults(election);
			break;
		case 0:
			input = 0;
			break;
		default:
			break;
		}
	}
}