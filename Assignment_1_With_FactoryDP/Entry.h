#pragma once
#define DELIMITER ','
#define NEWLINE '\n'
#define ENTRYSIZE 5
#define EMPTY ""
#define NOVALUE 0

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

struct Entry {


	std::string spsid;
	int fieldId;
	int iFuel;
	int iProduct;
	std::string productId;

	Entry();
 
public:
	Entry(std::string, int, int, int, std::string);
	virtual std::string str() = 0;
	virtual ~Entry() = default;
};

struct HddEntry : public Entry {

	HddEntry();
	HddEntry(std::string, int, int, int, std::string);
	std::string str() override;
										//change to take values as params. lets you resuse this to randomly generate without running through prompts
										//put user input into its own file
};
