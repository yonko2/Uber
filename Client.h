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
	//Client() = default;
};

