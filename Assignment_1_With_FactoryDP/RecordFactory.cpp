#include "RecordFactory.h"

RecordFactory::RecordFactory()
{
	//db_factories[FACTORY_TYPES::FT_DATABASE] = std::make_unique<DbEntryFactory>();
	db_factories[FACTORY_TYPES::FT_HDD] = std::make_unique<HddEntryFactory>();
}

std::unique_ptr<Entry> RecordFactory::create_entry(const int& type)
{
	return db_factories[type]->create();
}

std::vector<std::unique_ptr<Entry>> RecordFactory::read_entry(const int& type, std::string key)
{
	return db_factories[type]->read(key);
}

int RecordFactory::delete_entry(const int& type, std::string key)
{
	return db_factories[type]->deleteRecord(key);
}

bool RecordFactory::save_entry(Entry& entry, const int& type)
{
	return db_factories[type]->write(entry);
}

bool RecordFactory::set_filepath(std::string filePath, int type)
{
	return db_factories[type]->setFilePath(filePath);
}
