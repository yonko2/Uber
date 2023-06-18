#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
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
	friend class UberApplication;

	static size_t latestId;

	size_t id = 0;
	Client* client = nullptr;
	Driver* driver = nullptr;
	Address address;
	Address destination;
	unsigned passengers = 0;
	OrderStatus orderStatus = OrderStatus::created;
	DynamicArray<size_t> declinedDriverIds;
	double revenue = 0;
	bool ratingGiven = false;
	int minutes = -1;

public:
	Order();
	Order(Client* client, Driver* driver, const Address& address, const Address& destination, unsigned passengers);
	Order(Client* client, Driver* driver, Address&& address, Address&& destination, unsigned passengers);

	static size_t getLatestId();
	static void setLatestId(size_t latestId);

	size_t getId() const;
	OrderStatus getOrderStatus() const;
	int getMinutes() const;
	const Address& getAddress() const;
	const Client* getClient() const;
	const Driver* getDriver() const;
	const DynamicArray<size_t>& getDeclinedDriverIds() const;
	DynamicArray<size_t>& getDeclinedDriverIds();
	double getRevenue() const;

	void setOrderStatus(OrderStatus orderStatus);
	void setMinutes(int minutes);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs);

	void print() const;
	void setDriver(Driver* driverPtr);
	void pay(double amount);
	void giveRatingToDriver(double rating);
	void giveRatingToDriver(double rating) const;
	void printMinutesMsg();
};

