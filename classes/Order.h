#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
#include "../external/UniquePointer.hpp"
#include "../external/DynamicArray.hpp"

enum class OrderStatus
{
	created,
	accepted,
	completed,
	canceled
};

const char* OrderStatusToString(OrderStatus e);

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
	DynamicArray<size_t> declinedDriverIds;

public:
	Order() = default;
	Order(Client* client, Driver* driver, const Address& address, const Address& destination, unsigned passengers);
	Order(Client* client, Driver* driver, Address&& address, Address&& destination, unsigned passengers);

	static size_t getLatestId();
	static void setLatestId(size_t latestId);

	size_t getId() const;
	OrderStatus getOrderStatus() const;
	UniquePointer<Client>& getClient();
	UniquePointer<Driver>& getDriver();

	void setOrderStatus(OrderStatus orderStatus);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs);

	void print() const;
	void setDriver(UniquePointer<Driver>&& driverPtr);

	Order(const Order& other) = delete;
	Order& operator=(const Order& other) = delete;

	Order(Order&& other) = default;
	Order& operator=(Order&& other) = default;
};

