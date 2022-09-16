#include "Entry.h"


HddEntry::HddEntry()
{
}

HddEntry::HddEntry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : Entry(spsid, fieldId, iFuel, iProduct) {}

std::string HddEntry::str()
{
	std::ostringstream oss;
	oss << spsid << std::endl;
	oss << fieldId << std::endl;
	oss << iFuel << std::endl;
	oss << iProduct << std::endl;
	return oss.str();
}


Entry::Entry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : spsid(spsid), fieldId(fieldId), iFuel(iFuel), iProduct(iProduct), productId(productId) {}

