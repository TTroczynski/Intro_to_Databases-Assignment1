#pragma once
#include <memory>
#include "Entry.h"
#include <fstream>
#include <iostream>

std::unique_ptr<HddEntry> getRecord(std::fstream& fs, std::string key);

int removeRecords(std::fstream& fs, std::string key, std::string& buffer);