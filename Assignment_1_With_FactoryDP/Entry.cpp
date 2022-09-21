#include "Entry.h"


HddEntry::HddEntry()
{
}

HddEntry::HddEntry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : Entry(spsid, fieldId, iFuel, iProduct, productId) {}

std::string HddEntry::str()
{
	std::ostringstream oss;
	oss << spsid << std::endl;
	oss << fieldId << std::endl;
	oss << iFuel << std::endl;
	oss << iProduct << std::endl;
	oss << productId;
	return oss.str();
}

std::string HddEntry::getSpsid() const
{
	return spsid;
}

int HddEntry::getFieldId() const
{
	return fieldId;
}

int HddEntry::getIFuel() const
{
	return iFuel;
}

int HddEntry::getIProduct() const
{
	return iProduct;
}

std::string HddEntry::getProductId() const
{
	return productId;
}

HddEntry& HddEntry::operator=(const HddEntry& other)
{
	if (this != &other) {
		spsid = other.getSpsid();
		fieldId = other.getFieldId();
		iFuel = other.getIFuel();
		iProduct = other.getIProduct();
		productId = other.getProductId();
		return *this;
	}
	return *this;
}


Entry::Entry() : spsid(EMPTY), fieldId(NOVALUE), iFuel(NOVALUE), iProduct(NOVALUE), productId(EMPTY){}

Entry::Entry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : spsid(spsid), fieldId(fieldId), iFuel(iFuel), iProduct(iProduct), productId(productId) {}

