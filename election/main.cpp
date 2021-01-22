/*
Name:	Omer David
ID:		308483437
Name2:  Raziel Alron
ID:		316061415
*/
#include "electionLoader.h"
#include "districtLoader.h"
#include <fstream>
#include <string>
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
		District* dis = nullptr;
		string name;
		int numOfRep = 0;
		int type;

		if ((typeid(*election)) == (typeid(SimpleElection))) {
			throw invalid_argument("can't create district for simple election");
		}

		cout << "Enter type of district: for Uniform press 0, for Devided press 1 (0/1): ";
		cin >> type;
		if (type != 0 && type != 1) {
			throw invalid_argument("invalid type of district (0/1)");
		}

		cout << "Enter name of district: ";
		cin >> name;
		cout << "Enter Number of representetives: ";
		cin >> numOfRep;

		if (numOfRep <= 0) {
			throw invalid_argument("Enter Valid number Of Rep");
		}

		try {
			if (!type)
				dis = new UniformDis(name, numOfRep);
			else
				dis = new DevidedDis(name, numOfRep);

			election->appendDistrict(dis);
		}
		catch (DistrictException& err) {
			cout << "District Exception: " << err.getId() << ", " << err.what() << endl;
			delete dis;
			cout << "District cannot be created, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			delete dis;
			cout << "District cannot be created, Exit to main menu" << endl;
		}
		catch (...) {
			delete dis;
			cout << "District cannot be created, Exit to main menu" << endl;
		}
	}

	//get input from user to add new citizen
	void addNewCitizen(Election* election) {
		int yearOfBirth, districtId;
		string name;
		string id;
		District* dis;
		Citizen* cit = nullptr;

		if (!(election->getDistricts()->size())) {
			throw invalid_argument("can't create Citizen before creating a District");
		}

		cout << "Enter name of citizen: ";
		cin >> name;

		cout << "Enter ID: ";
		cin >> id;

		cout << "Enter year of birth: ";
		cin >> yearOfBirth;
		if (yearOfBirth < 1) {
			throw invalid_argument("Invalid year of birth, should be positive number");
		}
		try {
			if (typeid(*election) == typeid(NormalElection)) {
				cout << "Enter district ID: ";
				cin >> districtId;
				if (!(dis = election->getDistricts()->find(districtId))) {
					throw invalid_argument("No District matches the given ID");
				}
			}
			else {
				dis = (*(election->getDistricts()))[0];
			}

			cit = new Citizen(id, yearOfBirth, name, dis);
			election->appendCitizen(cit);
		}
		catch (CitizenException& err) {
			delete cit;
			cout << "Citizen Exception: " << err.getId() << ", " << err.what() << endl;
			cout << "Citizen cannot be created, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			delete cit;
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Citizen cannot be created, Exit to main menu" << endl;
		}
		catch (...) {
			delete cit;
			cout << "Citizen cannot be created, Exit to main menu" << endl;
		}
	}

	//get input from user to add new party
	void addNewParty(Election* election) {
		string name;
		string id;
		Citizen* temp = nullptr;
		Party* party = nullptr;
		
		if (!(election->getCitizens()->size())) {
			throw invalid_argument("can't create Party before creating a Citizen");
		}

		cout << "Enter name of Party: ";
		cin >> name;

		cout << "Enter ID of prime minister candidate: " << endl;
		cin >> id;
		if (!(temp = election->getCitizens()->find(id))) {
			throw invalid_argument("No Citizen matches the given ID");
		}
		try {
			party = new Party(name, temp);
			election->appendParty(party);
		}
		catch (PartyException& err) {
			cout << "PArty Exception: " << err.getId() << ", " << err.what() << endl;
			delete party;
			cout << "Party cannot be created, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			delete party;
			cout << "Party cannot be created, Exit to main menu" << endl;
		}
		catch (...) {
			delete party;
			cout << "Party cannot be created, Exit to main menu" << endl;
		}
	}

	//get input from user to add new party's candidate
	void addNewCandidate(Election* election) {
		string id;
		Citizen* citTemp = nullptr;
		Party* partyTemp = nullptr;
		District* disTemp = nullptr;
		int partyId, districtId;

		if (!(election->getParties()->size())) {
			throw invalid_argument("can't add Candidate before creating a Party");
		}

		cout << "Enter citizen ID: ";
		cin >> id;
		if (!(citTemp = election->getCitizens()->find(id))) {
			throw invalid_argument("No Citizen matches the given ID");
		}

		cout << "Enter Party ID: ";
		cin >> partyId;
		while (!(partyTemp = election->getParties()->find(partyId))) {
			throw invalid_argument("No Party matches the given ID");
		}

		if (typeid(*election) == typeid(NormalElection)) {
			cout << "Enter district ID: ";
			cin >> districtId;
			if (!(disTemp = election->getDistricts()->find(districtId))) {
				throw invalid_argument("No District matches the given ID");
			}
		}
		else {
			disTemp = (*(election->getDistricts()))[0];
		}
		try {
			partyTemp->appendCandidateToList(disTemp, citTemp);
		}
		catch (PartyException& err) {
			cout << "PArty Exception: " << err.getId() << ", " << err.what() << endl;
			cout << "Cannot add Party Candidate, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot add Party Candidate, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot add Party Candidate, Exit to main menu" << endl;
		}
	}

	//get input from user to add new Vote
	void vote(Election* election) {
		string id;
		int partyId;
		Citizen* citTemp = nullptr;
		Party* partyTemp = nullptr;

		cout << "Enter citizen ID: ";
		cin >> id;
		if (!(citTemp = election->getCitizens()->find(id))) {
			throw invalid_argument("No Citizen matches the given ID");
		}

		if (citTemp->getVote()) {
			throw invalid_argument("The current Citizenhas already voted");
		}

		cout << "Enter Party ID: ";
		cin >> partyId;
		if (!(partyTemp = election->getParties()->find(partyId))) {
			throw invalid_argument("No Party matches the given ID");
		}
		try {
			citTemp->vote(partyTemp);
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot vote, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot vote, Exit to main menu" << endl;
		}
	}

	//Prints all created districts
	void printDistricts(Election* election) {
		try {
			election->printDistricts();
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot print Districts, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot print Districts, Exit to main menu" << endl;
		}
	}

	//Prints all created citizens
	void printCitizens(Election* election) {
		try {
			election->printCitizens();
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot print Citizens, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot print Citizens, Exit to main menu" << endl;
		}
	}
	
	//Prints all created parties
	void printParties(Election* election) {
		try {
			election->printParties();
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot print Parties, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot print Parties, Exit to main menu" << endl;
		}
	}

	//Prints all election's results
	void printElectionResults(Election* election) {
		try {
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
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot Print Election Results, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot Print Election Results, Exit to main menu" << endl;
		}
	}

	//creates new election round
	Election* createElection() {
		Election* election=nullptr;
		int day = 1, month = 1, year = 2020, numOfRep = 0, type = -1;
		District* dis;
		string name = "DISTRICT ONE";

		cout << "Enter election date:" << endl << "Day: ";
		cin >> day;
		cout << "Month: ";
		cin >> month;
		cout << "Year: ";
		cin >> year;

		cout << "Election Type (0 - normal, 1 - simple): ";
		cin >> type;
		if (type != 0 && type != 1) {
			throw invalid_argument("Invalid election type (0/1)");
		}
		try {
			if (type) {
				cout << "Enter Number of representetives: ";
				cin >> numOfRep;
				if (numOfRep <= 0) {
					throw invalid_argument("Enter Valid number Of Rep");
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
		catch (ElectionException& err) {
			cout << "Election Exception: " << err.what() << endl;
			cout << "Cannot create Election, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot create Election, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot create Election, Exit to main menu" << endl;
		}
	}

	//save an existing election round into binary file
	void saveElection(Election* election) {
		string name;

		cout << "Enter File Name: ";
		cin >> name;

		ofstream outfile(name, ios::binary);
		if (!outfile.good()) {
			throw iostream::failure("Error opening file for write");
		}
		try {
			ElectionLoader::save(outfile, election);
			election->saveVotes(outfile);
			outfile.close();
		}
		catch (iostream::failure& err) {
			cout << "File Exception: " << err.what() << endl;
			cout << "Cannot save Election, Exit to main menu" << endl;
		}
		catch (ElectionException& err) {
			cout << "Election Exception: " << err.what() << endl;
			cout << "Cannot save Election, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot save Election, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot save Election, Exit to main menu" << endl;
		}
	}

	//load election round from binary file
	Election* loadElection() {
		string name;
		Election* election;

		cout << "Enter File Name: ";
		cin >> name;

		ifstream infile(name, ios::binary);
		if (!infile.good()) {
			throw iostream::failure("Error opening file for read");
		}
		try {
		election = ElectionLoader::load(infile);
		election->loadVotes(infile);
		infile.close();
		return election;
		}
		catch (iostream::failure& err) {
			cout << "File Exception: " << err.what() << endl;
			cout << "Cannot load Election, Exit to main menu" << endl;
		}
		catch (ElectionException& err) {
			cout << "Election Exception: " << err.what() << endl;
			cout << "Cannot load Election, Exit to main menu" << endl;
		}
		catch (invalid_argument& err) {
			cout << "Invalid Argument: " << err.what() << endl;
			cout << "Cannot load Election, Exit to main menu" << endl;
		}
		catch (...) {
			cout << "Cannot load Election, Exit to main menu" << endl;
		}
	}

	//delete instance of election
	void deleteElection(Election* election) {
		try {
			if (election) {
				delete election;
			}
		}
		catch (...) {
			cout << "Cannot delete Election" << endl;
			exit(2);
		}
	}

	//main menu
	void mainMenu(Election* election) {
		int input = 1;
		Election* election2 = nullptr;

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
					deleteElection(election);
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