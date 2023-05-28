#pragma once
#include "DynamicArray.hpp"
#include "Order.h"
#include "User.h"

class Driver : public User
{
	double rating = 0;
	DynamicArray<UniquePointer<Order>> newOrders;
};

