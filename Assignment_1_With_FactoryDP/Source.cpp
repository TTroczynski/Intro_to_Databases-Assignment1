#include <ctime>
#include "RecordFactory.h"
#include <vector>

#define NEWLINE '\n'
#define MIN_INT_VAL 1
#define MAX_FIELDID_VAL 255
#define MAX_IFUEL_VAL 350
#define MAX_IPRODUCT_VAL 1200
#define MAX_PREFIXES 5
#define MAX_PRODUCTIDS 3
#define MAX_ALPHANUM_LEN 24
#define MAX_COMMANDS 2
#define START_CMD "START"
#define INSERT_CMD "INSERT"
#define DELETE_CMD "DELETE"
#define FIND_CMD "FIND"
#define FINDALL_CMD "FINDALL"
#define RANDOMINSERT_CMD "RANDOM INSERT"
#define STOP_CMD "STOP"
#define SPSID_LENGTH 24
#define MAX_PRODUCTID 24
#define MAX_FIELDID 255
#define MAX_IFUEL 350
#define MAX_IPRODUCT 1200
#define MIN_LENGTH 1
#define DEFAULT_STRING "ERROR"
#define PRECISION 3


enum Options { OPT_A, OPT_B, OPT_C, OPT_D, OPT_E, OPT_EXIT, OPT_ERROR };

int getOption(std::string);
void postElapsedTime(time_t, time_t);
void generateRandomHdd(int numberOfRecords, std::vector<HddEntry>&);
std::string getRandomSpsid();
std::string getRandomProductID();
bool checkAlphanumeric(std::string);
bool checkIsDigit(std::string);

 HddEntry createHddEntryFromInput();

int main(int argv, char* argc[]) {

	if (argv != MAX_COMMANDS || std::string(argc[MAX_COMMANDS - 1]) != START_CMD) {
		std::cerr << "Syntax is: [Program] START" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::srand(clock());

	std::string filePath;
	std::string userInput;
	RecordFactory dbEntry;

	HddEntry newEntry;
	std::string key;
	int status = 0;
	time_t start, stop;
	std::string temp;
	std::vector<std::unique_ptr<Entry>> results;
	std::vector<HddEntry> randomRecords;
	std::string generateCount;
	int deleteCount = 0;

	std::cout << "Welcome to the Simple File Editor" << std::endl;
	std::cout << std::endl;

	while (getOption(userInput) != OPT_EXIT) {

		while (!dbEntry.set_filepath(filePath, FACTORY_TYPES::FT_HDD)) {

			std::cout << "Please specify a file path:" << std::endl << ">";

			std::getline(std::cin, filePath, NEWLINE);
		}

		std::cout << std::endl << "Enter one of the following options:" << std::endl;

		std::cout << "INSERT\t\tto add a record" << std::endl << "DELETE\t\tto remove a record" << std::endl
			<< "FIND\t\tto search for multiple records" << std::endl << "RANDOM INSERT\tto generate a specified number of records"
			<< std::endl << "STOP\t\tto exit" << std::endl << std::endl << ">";

		std::getline(std::cin, userInput, NEWLINE);
		std::cout << NEWLINE;

		switch (getOption(userInput))
		{
		case(OPT_A):

			newEntry = createHddEntryFromInput();

			start = clock();
			status = dbEntry.save_entry(newEntry, FT_HDD);
			stop = clock();

			postElapsedTime(start, stop);

			if (status) {
				std::cout << "Record inserted!" << std::endl;
			}
			else {
				std::cout << "Failed to insert record..." << std::endl;
			}
			break;

		case(OPT_B):

			std::cout << std::endl;
			std::cout << "Specify the SPSID of the record to delete: " << std::endl << ">";
			std::getline(std::cin, temp, NEWLINE);

			start = clock();
			deleteCount = dbEntry.delete_entry(FACTORY_TYPES::FT_HDD, temp);
			stop = clock();

			postElapsedTime(start, stop);
			if (deleteCount) {
				std::cout << deleteCount << " record(s) deleted successfully" << std::endl;
			}
			else {
				std::cout << "Failed to delete the record" << std::endl;
			}

			break;

		case(OPT_C):

			std::cout << "Enter an SPSID to search for: " << std::endl << ">";
			std::getline(std::cin, key, NEWLINE);

			start = clock();
			results = dbEntry.read_entry(FACTORY_TYPES::FT_HDD, key);
			stop = clock();

			postElapsedTime(start, stop);

			if (!results.empty()) {
				std::cout << results.size() << " record(s) found!" << std::endl << std::endl;

				for (std::unique_ptr<Entry>& record : results) {
					
					if(record.get())
					std::cout << record->str() << std::endl << std::endl;
				}
			}
			else {
				std::cout << std::endl << "Record not found..." << std::endl;
			}
			break;

		case(OPT_D):

			std::cout << "Enter the number of random records to generate:" << std::endl << ">";
			std::getline(std::cin, generateCount, NEWLINE);

			if (checkIsDigit(generateCount)) {

				start = clock();
				generateRandomHdd(std::stoi(generateCount), randomRecords);

				std::cout << std::endl << std::stoi(generateCount) << " records generated!" << std::endl;
				
				for (Entry& record : randomRecords) {
					dbEntry.save_entry(record, FACTORY_TYPES::FT_HDD);
				}
				stop = clock();
				postElapsedTime(start, stop);
			}
			else {
				std::cout << "Please enter a valid number" << std::endl;
			}

			break;

		case(OPT_EXIT):
			break;

		default:
			if (getOption(userInput) == OPT_ERROR) {
				std::cout << "I dont understand that input..." << std::endl;
			}
			break;
		}
	}
	std::cout << "Exiting!" << std::endl;

	return 0;
}

int getOption(std::string input) {

	if (input == INSERT_CMD) {
		return OPT_A;
	}
	else if (input == DELETE_CMD) {
		return OPT_B;
	}
	else if (input == FIND_CMD) {
		return OPT_C;
	}
	else if (input == RANDOMINSERT_CMD) {
		return OPT_D;
	}
	else if (input == STOP_CMD) {
		return OPT_EXIT;
	}
	else {
		return OPT_ERROR;
	}
}

void postElapsedTime(time_t start, time_t stop) {
	std::cout.precision(PRECISION);
	std::cout << std::fixed << std::endl << "Time elapsed: " << double(stop - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

void generateRandomHdd(int numberOfRecords, std::vector<HddEntry>& destination) {

	for (int i = 0; i < numberOfRecords; i++) {

		std::string newSpsid, newProductId;
		int newFieldId, newIFuel, newIProduct;

		newSpsid = getRandomSpsid();
		newFieldId = rand() % (MAX_FIELDID_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
		newIFuel = rand() % (MAX_IFUEL_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
		newIProduct = rand() % (MAX_IPRODUCT_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
		newProductId = getRandomProductID();

		destination.push_back(HddEntry(newSpsid, newFieldId, newIFuel, newIProduct, newProductId));
	}
}

std::string getRandomSpsid() {
	int randomNumber = std::rand() % MAX_PREFIXES + MIN_INT_VAL;
	switch (randomNumber)
	{
	case 1:
		return "JDR0423";
		break;

	case 2:
		return "NHSP310F";
		break;

	case 3:
		return "STARA3100AR";
		break;

	case 4:
		return "HAGIESTS16";
		break;

	case 5:
		return "CASE4430";
		break;
	}

	return DEFAULT_STRING;
}

std::string getRandomProductID() {
	int randomNumber = std::rand() % MAX_PRODUCTIDS + MIN_INT_VAL;
	switch (randomNumber)
	{
	case 1:
		return "DUPCurzate";
		break;

	case 2:
		return "BAYSCALA";
		break;

	case 3:
		return "SYNMaxim";
		break;
	}

	return DEFAULT_STRING;
}

bool checkAlphanumeric(std::string input) {

	for (int i = 0; i < input.size(); i++) {
		if (!std::isalnum(input.at(i))) {
			return false;
		}
	}

	return true;
}

bool checkIsDigit(std::string input) {

	for (int i = 0; i < input.size(); i++) {
		if (!std::isdigit(input.at(i))) {
			return false;
		}
	}

	return true;
}


HddEntry createHddEntryFromInput()
{
	std::string newSpsid;
	std::string newFieldId;
	std::string newIFuel;
	std::string newIProduct;
	std::string newProductId;


	auto checkString = [](std::string userInput) -> bool {
		for (int i = 0; i < userInput.size(); ++i) {
			if (!isalnum(userInput.at(i))) {
				std::cout << "Please enter an alphanumeric value!" << std::endl;
				return false;
			}
		}
		return true;
	};

	auto checkInteger = [](std::string userInput) -> bool {
		for (int i = 0; i < userInput.size(); ++i) {
			if (!isdigit(userInput.at(i))) {
				std::cout << "Please enter an integer value!" << std::endl;
				return false;
			}
		}
		return true;
	};


	do {
		std::cout << "Enter a 24 character alphanumeric SPSID: " << std::endl << ">";
		std::getline(std::cin, newSpsid, NEWLINE);

	} while (!checkString(newSpsid) || MIN_LENGTH > newSpsid.length() || newSpsid.length() > SPSID_LENGTH);

	do {
		std::cout << "Enter a fieldID (1-255): " << std::endl << ">";
		std::getline(std::cin, newFieldId, NEWLINE);

	} while (!checkInteger(newFieldId) || MIN_LENGTH > std::stoi(newFieldId) || std::stoi(newFieldId) > MAX_FIELDID);

	do {
		std::cout << "Enter a IFuel (1-350): " << std::endl << ">";
		std::getline(std::cin, newIFuel, NEWLINE);

	} while (!checkInteger(newIFuel) || MIN_LENGTH > std::stoi(newIFuel) || std::stoi(newIFuel) > MAX_IFUEL);

	do {
		std::cout << "Enter an IProduct (1-1200): " << std::endl << ">";
		std::getline(std::cin, newIProduct, NEWLINE);

	} while (!checkInteger(newIProduct) || MIN_LENGTH > std::stoi(newIProduct) || std::stoi(newIProduct) > MAX_IPRODUCT);

	do {
		std::cout << "Enter a 24 character alphanumeric productId: " << std::endl << ">";
		std::getline(std::cin, newProductId, NEWLINE);

	} while (!checkString(newProductId) || MIN_LENGTH > newProductId.length() || newProductId.length() > MAX_PRODUCTID);

	HddEntry newRecord(newSpsid, std::stoi(newFieldId), std::stoi(newIFuel), std::stoi(newIProduct), newProductId);

	return newRecord;
}
