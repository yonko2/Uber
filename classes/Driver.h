#pragma once

#include "Address.h"
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
	double rating = -1;
	MyString carNumber;
	MyString phoneNumber;
	Address address = {"N/A",0,0,""};
	unsigned ratingsCount = 0;
	double ratingSum = 0;

public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carNumber, const MyString& phoneNumber);
	Driver(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName,
		MyString&& carNumber, MyString&& phoneNumber);

	const Address& getAddress() const;
	void setAddress(const Address& address);
	void setAddress(Address&& address);

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
	void print() const override;

	void giveRating(double rating);
};

