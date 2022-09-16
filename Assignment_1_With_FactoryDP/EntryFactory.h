#pragma once
#include "Entry.h"
#include "Utils.h"

struct EntryFactory
{
	virtual std::unique_ptr<Entry> create() const = 0;
	virtual std::vector<std::unique_ptr<Entry>> read(std::string key) const = 0;
	virtual int deleteRecord(std::string key) const = 0;
	virtual bool write(Entry&) const = 0;
	virtual void setFilePath(const std::string&) = 0;
};


struct HddEntryFactory : public EntryFactory
{
private:
	std::string filePath;

public:

	enum ERROR { ERROR_CREATE, ERROR_READ, ERROR_READALL, ERROR_DELETE, ERROR_WRITE, ERROR_UNKNOWN };

	std::unique_ptr<Entry> create() const override;

	std::vector<std::unique_ptr<Entry>> read(std::string key) const override;

	int deleteRecord(std::string key) const override;

	bool write(Entry& newEntry) const override;

	void setFilePath(const std::string&) override;
};