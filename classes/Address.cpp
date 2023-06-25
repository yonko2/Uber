#include "Address.h"

Address::Address(const MyString& name, const Pair<int, int>& coordinates)
{
	this->name = name;
	this->coordinates = coordinates;
}

Address::Address(const MyString& name, const Pair<int, int>& coordinates, const MyString& description) :
	Address(name, coordinates)
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
	Address(name, coordX, coordY)
{
	this->description = description;
}

Address::Address(MyString&& name, const Pair<int, int>& coordinates)
{
	this->name = std::move(name);
	this->coordinates = coordinates;
}

Address::Address(MyString&& name, int coordX, int coordY) :
	Address(std::move(name), Pair{ coordX,coordY })
{
}

Address::Address(MyString&& name, int coordX, int coordY, MyString&& description) :
	Address(std::move(name), coordX, coordY)
{
	this->description = std::move(description);
}

Address::Address(MyString&& name, const Pair<int, int>& coordinates, MyString&& description) :
	Address(std::move(name), coordinates)
{
	this->description = std::move(description);
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

void Address::print() const
{
	std::cout << name << ' '
		<< coordinates.getFirst() << ' ' << coordinates.getSecond() << ' '
		<< description << std::endl;
}
