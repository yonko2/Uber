#pragma once

#include "User.h"

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
public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carNumber, const MyString& phoneNumber);
	Driver(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName,
		MyString&& carNumber, MyString&& phoneNumber);

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
	void print() const override;
};

