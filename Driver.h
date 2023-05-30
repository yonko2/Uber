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
	logout
};

class Order;

class Driver : public User
{
	double rating = 0;
	MyString carNumber;
	MyString phoneNumber;
	DynamicArray<UniquePointer<Order>> newOrders;

public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carNumber, const MyString& phoneNumber);

	/*Driver(const Driver&) = delete;
	Driver& operator=(const Driver&) = delete;

	Driver(Driver&&) = default;
	Driver& operator=(Driver&&) = default;*/
};

