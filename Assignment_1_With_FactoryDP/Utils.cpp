#include "Utils.h"

std::unique_ptr<HddEntry> getRecord(std::fstream& fs, std::string key)
{
	std::unique_ptr<HddEntry> record;
	std::string temp;

	std::string newSpsid, newProductId, newFieldId, newIFuel, newIProduct;

	while (std::getline(fs, temp)) {
		if (temp == key) {

			newSpsid = temp;
			std::getline(fs, newFieldId);
			std::getline(fs, newIFuel);
			std::getline(fs, newIProduct);
			std::getline(fs, newProductId);

			record = std::make_unique<HddEntry>(newSpsid, std::stoi(newFieldId), std::stoi(newIFuel), std::stoi(newIProduct), newProductId);

			break;
		}
	}
	return record;
}

int removeRecords(std::fstream& fs, std::string key, std::string& buffer) {
	std::string temp;
	int count = 0;

	while (std::getline(fs, temp)) {

		if (temp != key) {

			buffer.append(temp);
			buffer.push_back(char(NEWLINE));
		}
		else {

			count++;
			for (int i = 0; i < ENTRYSIZE; i++) {
				std::getline(fs, temp);
			}
		}
	}
	return count;
}


void abort(int error)
{
	switch (error)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	default:
		break;
	}
}
