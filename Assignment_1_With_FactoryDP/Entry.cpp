#include "Entry.h"


HddEntry::HddEntry()
{
}

HddEntry::HddEntry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : spsid(spsid),  {}

std::string HddEntry::str()
{
	std::ostringstream oss;
	oss << spsid << std::endl;
	oss << fieldId << std::endl;
	oss << iFuel << std::endl;
	oss << iProduct << std::endl;
	oss << productId << std::endl;
	return oss.str();
}


Entry::Entry() : spsid(EMPTY), fieldId(NOVALUE), iFuel(NOVALUE), iProduct(NOVALUE), productId(EMPTY)
{
}

Entry::Entry(std::string spsid, int fieldId, int iFuel, int iProduct, std::string productId) : spsid(spsid), fieldId(fieldId), iFuel(iFuel), iProduct(iProduct), productId(productId) {}

