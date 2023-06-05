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

const char* OrderStatusToString(OrderStatus e)
{
	switch (e)
	{
	case OrderStatus::created: return "created";
	case OrderStatus::accepted: return "accepted";
	case OrderStatus::completed: return "completed";
	case OrderStatus::canceled: return "canceled";
	default: return "unknown";
	}
}

class Order
{
	static size_t latestId;

	size_t id = 0;
	UniquePointer<Client> client;
	UniquePointer<Driver> driver;
	Address address;
	Address destination;
	unsigned passengers = 0;
	OrderStatus orderStatus = OrderStatus::created;

public:
	Order() = default;
	Order(Client* client, Driver* driver, const Address& address, const Address& destination, unsigned passengers);
	Order(Client* client, Driver* driver, Address&& address, Address&& destination, unsigned passengers);

	static size_t getLatestId();
	static void setLatestId(size_t latestId);

	size_t getId() const;

	void setOrderStatus(OrderStatus orderStatus);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs);

	void print() const;
	void setDriver(UniquePointer<Driver>&& driverPtr);

	/*Order(const Order&) = delete;
	Order& operator=(const Order&) = delete;

	Order(Order&&) noexcept;
	Order& operator=(Order&&) noexcept;*/
};

