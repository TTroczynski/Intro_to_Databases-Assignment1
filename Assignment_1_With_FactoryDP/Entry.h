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

	std::string getSpsid() const;
	int getFieldId() const;
	int getIFuel() const;
	int getIProduct() const;
	std::string getProductId() const;
										
	HddEntry& operator=(const HddEntry& other);
};
