/*
Name:	Omer David
ID:		308483437
Name2:  Raziel Alron
ID:		316061415
*/

#pragma once 
#include "party.h"
#include "district.h"
#include "devidedDis.h"
#include "UniformDis.h"
#include "simpleElection.h"
#include "normalElection.h"
#include "citizen.h"
#include "electionLoader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;
using namespace Elections;

enum class Menu {
	Exit, addNewDistrict, addNewCitizen, addNewParty, addNewCandidate,
	printDistricts, printCitizens, printParties, vote, printElectionResults,
	createElection, loadElection, saveElection
};

namespace Elections {

	//Prints first menu
	void printFistMenu() {
		cout << "------------------------------------------------------" << endl;
		cout << "Press 1 to create new Election Round" << endl;
		cout << "Press 2 to load an old Election Round" << endl;
		cout << "Press 3 to Exit" << endl;
		cout << "------------------------------------------------------" << endl;
	}

	//Prints main menu
	void printMainMenu() {
		cout << endl << endl << endl;
		cout << "--------------------------MAIN-MENU----------------------------" << endl;
		cout << "Press 1 for adding a district" << endl;
		cout << "Press 2 for adding a citizen" << endl;
		cout << "Press 3 for adding a party" << endl;
		cout << "Press 4 for adding a citizen as party candidate" << endl;
		cout << "Press 5 to display all districts" << endl;
		cout << "Press 6 to display all citizens" << endl;
		cout << "Press 7 to display all parties" << endl;
		cout << "Press 8 to vote" << endl;
		cout << "Press 9 to display election results" << endl;
		cout << "Press 11 to load an old Election Round" << endl;
		cout << "Press 12 save this Election Round" << endl;
		cout << "Press 0 to exit programe" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << endl << endl << endl;
	}

	//get input from user to add new sitrict
	void addNewDistrict(Election* election) {
		District* dis;
		char name[256];
		int numOfRep = 0;
		int type;

		if ((typeid(*election)) == (typeid(SimpleElection))) {
			cout << "can't create district for simple election" << endl;
			return;
		}

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

		if (typeid(*election) == typeid(NormalElection)) {
			cout << "Enter district ID: ";
			cin >> districtId;
			while (!(dis = election->getDistricts()->getDistrict(districtId))) {
				cout << "Enter valid district ID" << endl;
				cin >> districtId;
			}
		}
		else {
			dis = (*(election->getDistricts()))[0];
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

		cout << "Enter ID of prime minister candidate: " << endl;
		cin >> id;
		while (!(temp = election->getCitizens()->getCit(id))) {
			cout << "There is no citizen with this ID" << endl;
			cin >> id;
		}

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

		if (typeid(*election) == typeid(NormalElection)) {
			cout << "Enter district ID: ";
			cin >> districtId;
			while (!(disTemp = election->getDistricts()->getDistrict(districtId))) {
				cout << "Enter valid district ID" << endl;
				cin >> districtId;
			}
		}
		else {
			disTemp = (*(election->getDistricts()))[0];
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
		
		if (typeid(*election) == typeid(NormalElection)) {
			election->sortPartiesByElectors();
			cout << *static_cast<NormalElection*>(election);
			election->getParties()->printResults();
		}
		else {
			election->sortPartiesByTotalVotes();
			cout << *static_cast<SimpleElection*>(election);
		}
		cout << "-------------------ELECTION-RESULTS-END----------------" << endl;
	}

	//creates new election round
	Election* createElection() {
		Election* election=nullptr;
		int day = 1, month = 1, year = 2020, numOfRep = 0, type = -1;
		District* dis;
		char name[256] = "DISTRICT ONE";

		cout << "Enter election date:" << endl << "Day: ";
		cin >> day;
		cout << "Month: ";
		cin >> month;
		cout << "Year: ";
		cin >> year;

		cout << "Election Type (0 - normal, 1 - simple): ";
		cin >> type;
		while (type != 0 && type != 1) {
			cout << "Wrong type selected, please choose again (0 - normal, 1 - simple): ";
			cin >> type;
		}

		if (type) {
			cout << "Enter Number of representetives: ";
			cin >> numOfRep;
			while (numOfRep <= 0) {
				cout << "Enter Valid number Of Rep" << endl;
				cin >> numOfRep;
			}

			election = new SimpleElection(day, month, year);
			dis = new DevidedDis(name, numOfRep);
			election->appendDistrict(dis);
		}
		else {
			election = new NormalElection(day, month, year);
		}
		return election;
	}

	//save an existing election round into binary file
	void saveElection(Election* election) {
		char name[256];

		cout << "Enter File Name: ";
		cin >> name;

		ofstream outfile(name, ios::binary);
		if (!outfile.good()) {
			cout << "Error opening file for write" << endl;
			exit(-1);
		}

		ElectionLoader::save(outfile, election);
		election->saveVotes(outfile);
	}

	//load election round from binary file
	Election* loadElection() {
		char name[256];
		Election* election;

		cout << "Enter File Name: ";
		cin >> name;

		ifstream infile(name, ios::binary);
		if (!infile.good()) {
			cout << "Error opening file for read" << endl;
			exit(-1);
		}

		election = ElectionLoader::load(infile);
		election->loadVotes(infile);
		return election;
	}

	//main menu
	void mainMenu(Election* election) {
		int input = 1;

		while (input) {
			printMainMenu();
			cin >> input;

			switch (input)
			{
				case static_cast<int>(Menu::addNewDistrict) :
					addNewDistrict(election);
					break;
				case static_cast<int>(Menu::addNewCitizen) :
					addNewCitizen(election);
					break;
				case static_cast<int>(Menu::addNewParty) :
					addNewParty(election);
					break;
				case static_cast<int>(Menu::addNewCandidate) :
					addNewCandidate(election);
					break;
				case static_cast<int>(Menu::printDistricts) :
					printDistricts(election);
					break;
				case static_cast<int>(Menu::printCitizens) :
					printCitizens(election);
					break;
				case static_cast<int>(Menu::printParties) :
					printParties(election);
					break;
				case static_cast<int>(Menu::vote) :
					vote(election);
					break;
				case static_cast<int>(Menu::printElectionResults) :
					printElectionResults(election);
					break;
				case static_cast<int>(Menu::loadElection) :
					if (election) {
						delete election;
					}
					election = loadElection();
					break;
				case static_cast<int>(Menu::saveElection) :
					saveElection(election);
					break;
				case static_cast<int>(Menu::Exit) :
					input = 0;
					break;
				default:
					cout << "Please enter VALID menu number" << endl;
					break;
			}
		}
	}

	//first menu
	Election* firstMenu() {
		int input = 1;
		Election* election = nullptr;

		while (input) {
			printFistMenu();
			cin >> input;

			switch (input) {
			case (static_cast<int>(Menu::createElection) - 9):
				input = 0;
				election = createElection();
				break;
			case (static_cast<int>(Menu::loadElection) - 9):
				input = 0;
				election = loadElection();
				break;
			case (static_cast<int>(Menu::Exit) + 3) :
				input = 0;
				break;
			default:
				cout << "Please enter VALID menu number" << endl;
				break;
			}
		}
		return election;
	}
}

void main() {
	Election* election = nullptr;

	election = firstMenu();

	if (election) {
		mainMenu(election);
	}
}