#pragma once
#include "User.h"

enum class ClientActions
{
	order,
	checkOrder,
	cancelOrder,
	pay,
	rate,
	add_money,
	logout,
	exit
};

class Client : public User
{
public:
	Client() = default;

	Client(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);
	Client(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName);

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
	void print() const override;
};

