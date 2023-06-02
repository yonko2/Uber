#include "Driver.h"
//#include "Order.h"

Driver::Driver(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName,
	const MyString& carNumber, const MyString& phoneNumber) :
	User(username, password, firstName, lastName)
{
	this->carNumber = carNumber;
	this->phoneNumber = phoneNumber;
}

void Driver::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
	ofs.write((const char*)&rating, sizeof rating);
	carNumber.saveToFile(ofs);
	phoneNumber.saveToFile(ofs);

	const size_t ordersCount = newOrderIDs.getSize();
	ofs.write((const char*)&ordersCount, sizeof ordersCount);
	for (size_t i = 0; i < ordersCount; i++)
	{
		ofs.write((const char*)&this->newOrderIDs[i], sizeof this->newOrderIDs[i]);
	}
}

void Driver::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);
	ifs.read((char*)&rating, sizeof rating);
	carNumber.readFromFile(ifs);
	phoneNumber.readFromFile(ifs);

	size_t ordersCount = 0;
	ifs.read((char*)&ordersCount, sizeof ordersCount);
	for (size_t i = 0; i < ordersCount; i++)
	{
		size_t currId = 0;
		ifs.read((char*)&currId, sizeof currId);
		this->newOrderIDs.pushBack(currId);
	}
}
