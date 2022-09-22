#include "Utils.h"

std::unique_ptr<HddEntry> getRecord(std::fstream& fs, std::string key)
{
	std::unique_ptr<HddEntry> record = nullptr;
	std::string temp;

	std::string newSpsid, newProductId, newFieldId, newIFuel, newIProduct;

	while (std::getline(fs, temp, NEWLINE)) {
		if (temp == (key + DELIMITER)) {

			temp.erase(temp.begin() + temp.find(DELIMITER));
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

		if (temp != (key + DELIMITER)) {

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
