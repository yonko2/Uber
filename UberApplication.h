#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "SessionManager.h"
#include "Order.h"

class UberApplication // singleton
{
	SessionManager sessionManager;

public:
	UberApplication() = default;

	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

	void load() const;
	void save() const;

};

