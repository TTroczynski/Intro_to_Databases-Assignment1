#include "EntryFactory.h"

std::unique_ptr<Entry> HddEntryFactory::create(std::string spsid, int iFieldId, int iFuel, int iProduct, std::string productId) const
{
	return std::make_unique<HddEntry>(spsid, iFieldId, iFuel, iProduct, productId);
}

std::vector<std::unique_ptr<Entry>> HddEntryFactory::read(std::string key) const
{
	std::vector<std::unique_ptr<Entry>> records;

	std::fstream fileSearch;
	fileSearch.open(filePath, std::ios_base::in);

	if (fileSearch.is_open()) {

		while (!fileSearch.eof()) {

			std::unique_ptr<HddEntry> newHddEntry = getRecord(fileSearch, key);
			
			if (newHddEntry != nullptr) {
			records.push_back(std::make_unique<HddEntry>(newHddEntry->spsid, newHddEntry->fieldId, newHddEntry->iFuel, newHddEntry->iProduct, newHddEntry->productId));
			}
		}
		fileSearch.close();
	}

	return records;
}

int HddEntryFactory::deleteRecord(std::string key) const {

	int count = 0;
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

	std::string temp;
	std::fstream fileOut;
	fileOut.open(filePath, std::ios_base::app);

	if (fileOut.is_open()) {

		
		temp = newEntry.str();
		fileOut << NEWLINE;
		fileOut << newEntry.str().insert(temp.find(NEWLINE), DELIMITER);

		fileOut.close();

		return true;
	}

	return false;
}

bool HddEntryFactory::setFilePath(const std::string& path)
{
std::fstream ofs;

	std::filesystem::path newPath = path;

	if (newPath.has_filename()) {
		ofs.open(path, std::ios_base::app);
		if (ofs.is_open()) {
			ofs.close();
			filePath = path;
			return true;
		}
	}
	return false;
	
}
