#include "Address.h"

Address::Address(const MyString& name, const Pair<int, int>& coordinates)
{
	this->name = name;
	this->coordinates = coordinates;
}

Address::Address(const MyString& name, const Pair<int, int>& coordinates, const MyString& description) :
	Address(name,coordinates)
{
	this->description = description;
}

Address::Address(const MyString& name, const int coordX, const int coordY)
{
	this->name = name;
	this->coordinates.setFirst(coordX);
	this->coordinates.setSecond(coordY);
}

Address::Address(const MyString& name, int coordX, int coordY, const MyString& description) :
	Address(name,coordX, coordY)
{
	this->description = description;
}

void Address::saveToFile(std::ofstream& ofs) const
{
	name.saveToFile(ofs);
	coordinates.saveToFile(ofs);
	description.saveToFile(ofs);
}

void Address::readFromFile(std::ifstream& ifs)
{
	name.readFromFile(ifs);
	coordinates.readFromFile(ifs);
	description.readFromFile(ifs);
}
