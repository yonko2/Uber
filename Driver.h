#pragma once

#include "User.h"
#include "DynamicArray.hpp"
#include "UniquePointer.hpp"

enum class DriverActions
{
	changeAddress,
	checkMessages,
	acceptOrder,
	declineOrder,
	finishOrder,
	acceptPayment,
	logout,
	exit
};

class Driver : public User
{
	double rating = 0;
	MyString carNumber;
	MyString phoneNumber;
	DynamicArray<size_t> newOrderIDs;

public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carNumber, const MyString& phoneNumber);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

