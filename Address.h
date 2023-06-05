#pragma once
#include "MyString.h"
#include "Pair.hpp"

struct Address
{
	MyString name;
	Pair<int, int> coordinates{};
	MyString description; // not required

	Address() = default;
	Address(const MyString& name, const Pair<int, int>& coordinates);
	Address(const MyString& name, const Pair<int, int>& coordinates, const MyString& description);
	Address(const MyString& name, int coordX, int coordY);
	Address(const MyString& name, int coordX, int coordY, const MyString& description);
	Address(MyString&& name, const Pair<int, int>& coordinates);
	Address(MyString&& name, const Pair<int, int>& coordinates, MyString&& description);
	Address(MyString&& name, int coordX, int coordY);
	Address(MyString&& name, int coordX, int coordY, MyString&& description);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
	void print() const;
};

