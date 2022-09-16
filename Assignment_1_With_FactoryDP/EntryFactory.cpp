#include "EntryFactory.h"

std::unique_ptr<Entry> HddEntryFactory::create() const
{
	return std::make_unique<HddEntry>();
}

std::vector<std::unique_ptr<Entry>> HddEntryFactory::read(std::string key) const
{
	std::vector<std::unique_ptr<Entry>> records;

	std::fstream fileSearch;
	fileSearch.open(filePath, std::ios_base::in);

	if (fileSearch.is_open()) {

		while (!fileSearch.eof()) {

			records.push_back(getRecord(fileSearch, key));
		}
		fileSearch.close();

		return records;
	}

	abort(ERROR_READALL);

}

int HddEntryFactory::deleteRecord(std::string key) const {

	int count;
	std::fstream fileSearch;
	std::fstream fileWrite;
	std::string buffer;

	fileSearch.open(filePath, std::ios_base::in);

	if (fileSearch.is_open()) {

		count = removeRecords(fileSearch, key, buffer);

		fileSearch.close();

	}

	fileSearch.open(filePath, std::ios_base::out);

	if (fileSearch.is_open()) {

		fileSearch << buffer;
		fileSearch.close();
	}
	return count;
}

bool HddEntryFactory::write(Entry& newEntry) const {

	std::fstream fileOut;
	fileOut.open(filePath, std::ios_base::app);

	if (fileOut.is_open()) {

		fileOut << newEntry.str();

		fileOut.close();

		return true;
	}

	return false;
}

void HddEntryFactory::setFilePath(const std::string& path)
{
	filePath = path;
}
