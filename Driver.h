#pragma once
#include "DynamicArray.hpp"
#include "Order.h"
#include "User.h"
#include "UniquePointer.hpp"

class Driver : public User
{
	double rating = 0;
	DynamicArray<UniquePointer<Order>> newOrders;
};

