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

enum Options { OPT_A, OPT_B, OPT_C, OPT_D, OPT_E, OPT_EXIT, OPT_ERROR };

int getOption(std::string);
void postElapsedTime(time_t, time_t);
std::vector<Entry> generateRandom(int numberOfRecords, int type);
std::string getRandomSpsid();
std::string getRandomProductID();
bool checkAlphanumeric(std::string);
bool checkIsDigit(std::string);

 HddEntry createHddEntryFromInput();

int main(int argv, char* argc[]) {

	//if (argv != MAX_COMMANDS || std::string(argc[MAX_COMMANDS - 1]) != START_CMD) {
	//	std::cerr << "Syntax is: [Program] START" << std::endl;
	//	exit(EXIT_FAILURE);
	//}

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
	std::vector<Entry> randomRecords;
	std::string generateCount;
	int deleteCount = 0;

	std::cout << "Welcome to the Simple File Editor" << std::endl;
	std::cout << std::endl;

	while (getOption(userInput) != OPT_EXIT) {

		while (!dbEntry.set_filepath(filePath, FACTORY_TYPES::FT_HDD)) {

			std::cout << "Please specify a file path:" << std::endl;

			std::getline(std::cin, filePath, NEWLINE);
		}

		std::cout << std::endl << "Enter one of the following options:" << std::endl;

		std::cout << "INSERT\t\tto add a record" << std::endl << "DELETE\t\tto remove a record" << std::endl
			<< "FIND\t\tto search for multiple records" << std::endl << "RANDOM INSERT\tto generate a specified number of records"
			<< std::endl << "STOP\t\tto exit" << std::endl;

		std::getline(std::cin, userInput, NEWLINE);

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
			std::cout << "Specify the SPSID of the record to delete: " << std::endl;
			std::getline(std::cin, temp, NEWLINE);

			start = clock();
			deleteCount = dbEntry.delete_entry(FACTORY_TYPES::FT_HDD, temp);
			stop = clock();

			postElapsedTime(start, stop);
			if (status) {
				std::cout << deleteCount << " record(s) deleted successfully" << std::endl;
			}
			else {
				std::cout << "Failed to delete the record" << std::endl;
			}

			break;

		case(OPT_C):

			std::cout << "Enter an SPSID to search for: " << std::endl;
			std::getline(std::cin, key, NEWLINE);

			start = clock();
			results = dbEntry.read_entry(FACTORY_TYPES::FT_HDD, key);
			stop = clock();

			postElapsedTime(start, stop);

			if (status) {
				std::cout << std::endl << results.size() << " record(s) found!" << std::endl;

				for (std::unique_ptr<Entry>& record : results) {
					std::cout << record->str();
				}
			}
			else {
				std::cout << std::endl << "Record not found..." << std::endl;
			}
			break;

		case(OPT_D):

			std::cout << "Enter the number of random records to generate:" << std::endl;
			std::getline(std::cin, generateCount, NEWLINE);

			if (checkIsDigit(generateCount)) {

				start = clock();
				randomRecords = generateRandom(std::stoi(generateCount), FACTORY_TYPES::FT_HDD);

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
	std::cout << std::endl << "Time elapsed: " << double(stop - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

std::vector<Entry> generateRandom(int numberOfRecords, int type) {

	std::vector<Entry> newRecords;

	if (type == FACTORY_TYPES::FT_HDD) {
		for (int i = 0; i < numberOfRecords; i++) {

			std::string newSpsid, newProductId;
			int newFieldId, newIFuel, newIProduct;

			newSpsid = getRandomSpsid();
			newFieldId = rand() % (MAX_FIELDID_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
			newIFuel = rand() % (MAX_IFUEL_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
			newIProduct = rand() % (MAX_IPRODUCT_VAL - MIN_INT_VAL + 1) + MIN_INT_VAL;
			newProductId = getRandomProductID();

			newRecords.push_back(HddEntry(newSpsid, newFieldId, newIFuel, newIProduct, newProductId));
		}
	}
	
	return newRecords;
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
	std::string newIProductId;


	auto checkSpsid = [](std::string spsid) -> bool {
		for (int i = 0; i < spsid.size(); ++i) {
			if (isalnum(spsid.at(i))) {
				std::cout << "SPSID must be alphanumeric!" << std::endl;
				return false;
			}
		}
		return true;
	};

	do {
		std::cout << "Enter a SPSID: " << std::endl;
		std::getline(std::cin, newSpsid, NEWLINE);

	} while (!checkSpsid(newSpsid));


	auto checkFieldId = [](std::string fieldId) -> bool {
		for (int i = 0; i < fieldId.size(); ++i) {
			if (isdigit(fieldId.at(i))) {
				std::cout << "FieldID must be numeric!" << std::endl;
				return false;
			}
		}
		return true;
	};

	do {
		std::cout << "Enter a fieldID: " << std::endl;
		std::getline(std::cin, newFieldId, NEWLINE);

	} while (!checkFieldId(newFieldId));


	auto checkIFuel = [](std::string iFuel) -> bool {
		for (int i = 0; i < iFuel.size(); ++i) {
			if (isdigit(iFuel.at(i))) {
				std::cout << "iFuel must be numeric!" << std::endl;
				return false;
			}
		}
		return true;
	};

	do {
		std::cout << "Enter a IFuel: " << std::endl;
		std::getline(std::cin, newIFuel, NEWLINE);

	} while (!checkIFuel(newIFuel));


	auto checkIProduct = [](std::string iProduct) -> bool {
		for (int i = 0; i < iProduct.size(); ++i) {
			if (isdigit(iProduct.at(i))) {
				std::cout << "iProduct must be numeric!" << std::endl;
				return false;
			}
		}
		return true;
	};

	do {
		std::cout << "Enter an IProduct: " << std::endl;
		std::getline(std::cin, newIProduct, NEWLINE);

	} while (!checkIProduct(newIProductId));


	auto checkIProductId = [](std::string iProductId) -> bool {
		for (int i = 0; i < iProductId.size(); ++i) {
			if (isalnum(iProductId.at(i))) {
				std::cout << "iProductId must be alphanumeric!" << std::endl;
				return false;
			}
		}
		return true;
	};

	do {
		std::cout << "Enter an IProduct: " << std::endl;
		std::getline(std::cin, newIProductId, NEWLINE);

	} while (!checkIProductId(newIProductId));

	HddEntry newRecord(newSpsid, std::stoi(newFieldId), std::stoi(newIFuel), std::stoi(newIProduct), newIProductId);

	return newRecord;
}
