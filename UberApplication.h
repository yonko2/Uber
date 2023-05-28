#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "SessionManager.h"
#include "UniquePointer.hpp"

class UberApplication // singleton
{
	SessionManager session;

public:
	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

	void load() const;
	void save() const;

};

