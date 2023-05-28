#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
#include "UniquePointer.hpp"

enum class OrderStatus
{
	created,
	accepted,
	completed,
	canceled
};

class Order
{
	UniquePointer<Client> client;
	UniquePointer<Driver> driver;
	size_t id = 0;
	Address address;
	unsigned passengers = 0;
	OrderStatus orderStatus = OrderStatus::created;
};

