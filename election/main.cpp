#pragma once 
#include "party.h"
#include "district.h"
#include "devidedDis.h"
#include "UniformDis.h"
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
		District* dis;
		char name[256];
		int numOfRep = 0;
		int type;

		cout << "Enter type of district: for Uniform press 0, for Devided press 1 (0/1): ";
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

		if (!type)
			dis = new UniformDis(name, numOfRep);
		else
			dis = new DevidedDis(name, numOfRep);
		election->appendDistrict(dis);
	}

	/*
	//returns true if the id is valid else false
	bool isValidId(char id[10]) {
		for (int i = 0;i < 9;i++)
			if (!(id[i] && id[i] <= '9' && id[i] >= '0')) {
				return false;
			}
		return true;
	}
	*/

	//get input from user to add new citizen
	void addNewCitizen(Election* election) {
		int yearOfBirth, districtId;
		char name[256];
		char id[256];
		District* dis;

		if (!(election->getDistricts()->getLogSize())) {
			cout << "There are no distrits " << endl;
			return;
		}

		cout << "Enter name of citizen: ";
		cin >> name;

		cout << "Enter ID: ";
		cin >> id;

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
		char id[256];
		Citizen* temp = nullptr;
		
		if (!(election->getCitizens()->getLogSize())) {
			cout << "There are no citizens " << endl;
			return;
		}


		cout << "Enter name of Party: ";
		cin >> name;

		cout << "Enter ID of prime minister candidate: ";
		cin >> id;
		while (!(temp = election->getCitizens()->getCit(id))) {
			cout << "There is no citizen with this ID" << endl;
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
		while (!(citTemp = election->getCitizens()->getCit(id))) {
			cout << "There is no citizen with this ID" << endl;
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
		while (!(citTemp = election->getCitizens()->getCit(id))) {
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

enum class Menu { Exit, addNewDistrict, addNewCitizen, addNewParty,
	addNewCandidate, printDistricts, printCitizens, printParties, vote, printElectionResults};


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
		case static_cast<int>(Menu::addNewDistrict):
			addNewDistrict(election);
			break;
		case static_cast<int>(Menu::addNewCitizen):
			addNewCitizen(election);
			break;
		case static_cast<int>(Menu::addNewParty):
			addNewParty(election);
			break;
		case static_cast<int>(Menu::addNewCandidate):
			addNewCandidate(election);
			break;
		case static_cast<int>(Menu::printDistricts):
			printDistricts(election);
			break;
		case static_cast<int>(Menu::printCitizens):
			printCitizens(election);
			break;
		case static_cast<int>(Menu::printParties):
			printParties(election);
			break;
		case static_cast<int>(Menu::vote):
			vote(election);
			break;
		case static_cast<int>(Menu::printElectionResults):
			printElectionResults(election);
			break;
		case static_cast<int>(Menu::Exit):
			input = 0;
			break;
		default:
			break;
		}
	}
}