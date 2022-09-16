#pragma once
#include <map>
#include "EntryFactory.h"
#include <string>


enum FACTORY_TYPES {FT_DATABASE, FT_HDD};

class RecordFactory
{
	std::map<int, std::unique_ptr<EntryFactory>> db_factories;

public:

	RecordFactory();					//add any kind of factory. This allows you to easily extend. Just implement the pure virtual class and write the factory specific implementation
										//for each overridden method.

	std::unique_ptr<Entry> create_entry(const int& type);

	std::vector<std::unique_ptr<Entry>> read_entry(const int& type, std::string key);

	int delete_entry(const int& type, std::string key);

	bool save_entry(Entry& entry, const int& type);

	void set_filepath(std::string, int type);

};

