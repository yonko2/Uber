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
	static size_t latestId;

	size_t id = 0;
	UniquePointer<Client> client;
	UniquePointer<Driver> driver;
	Address address;
	unsigned passengers = 0;
	OrderStatus orderStatus = OrderStatus::created;

public:
	Order() = default;
	Order(Client* client, Driver* driver, const Address& address, unsigned passengers);

	size_t getId() const;

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs);

	/*Order(const Order&) = delete;
	Order& operator=(const Order&) = delete;

	Order(Order&&) noexcept;
	Order& operator=(Order&&) noexcept;*/
};

