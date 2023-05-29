#pragma once
#include "MyString.h"
#include "Pair.h"

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
};

