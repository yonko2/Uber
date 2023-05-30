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
	logout
};

class Client : public User
{
public:
	Client() = default;

	Client(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);
};

