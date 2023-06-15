#include "Order.h"

#include "UberApplication.h"

size_t Order::latestId = 1;

const char* OrderStatusToString(const OrderStatus e)
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

Order::Order(Client* client, Driver* driver, const Address& address, const Address& destination, const unsigned passengers)
{
	this->client = client;
	this->driver = driver;
	this->address = address;
	this->destination = destination;
	this->passengers = passengers;
}

Order::Order(Client* client, Driver* driver, Address&& address, Address&& destination, const unsigned passengers)
{
	this->client = client;
	this->driver = driver;
	this->address = std::move(address);
	this->destination = std::move(destination);
	this->passengers = passengers;
}

size_t Order::getLatestId()
{
	return Order::latestId;
}

void Order::setLatestId(const size_t latestId)
{
	Order::latestId = latestId;
}

size_t Order::getId() const
{
	return this->id;
}

OrderStatus Order::getOrderStatus() const
{
	return this->orderStatus;
}

const Address& Order::getAddress() const
{
	return this->address;
}

const Client* Order::getClient() const
{
	return this->client;
}

const Driver* Order::getDriver() const
{
	return this->driver;
}

const DynamicArray<size_t>& Order::getDeclinedDriverIds() const
{
	return this->declinedDriverIds;
}

DynamicArray<size_t>& Order::getDeclinedDriverIds()
{
	return this->declinedDriverIds;
}

void Order::setOrderStatus(const OrderStatus orderStatus)
{
	this->orderStatus = orderStatus;
}

void Order::saveToFile(std::ofstream& ofs) const
{
	if (client == nullptr || driver == nullptr)
	{
		throw std::exception("Empty order");
	}

	ofs.write((const char*)&id, sizeof id);

	const size_t clientId = client->getId();
	ofs.write((const char*)&clientId, sizeof clientId);

	const size_t driverId = driver->getId();
	ofs.write((const char*)&driverId, sizeof driverId);

	address.saveToFile(ofs);
	ofs.write((const char*)&passengers, sizeof passengers);
	ofs.write((const char*)&orderStatus, sizeof orderStatus);

	const size_t declinedIdsCount = declinedDriverIds.getSize();
	ofs.write((const char*)&declinedIdsCount, sizeof declinedIdsCount);
	for (size_t i = 0; i < declinedIdsCount; i++)
	{
		ofs.write((const char*)&this->declinedDriverIds[i], sizeof this->declinedDriverIds[i]);
	}
}

void Order::readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof id);

	size_t clientId = 0;
	ifs.read((char*)&clientId, sizeof clientId);
	const size_t clientsCount = clientsPtr->getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if ((*clientsPtr)[i].getId() == clientId)
		{
			this->client = &(*clientsPtr)[i];
		}
	}

	size_t driverId = 0;
	ifs.read((char*)&driverId, sizeof driverId);
	const size_t driversCount = driversPtr->getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if ((*driversPtr)[i].getId() == driverId)
		{
			this->driver = &(*driversPtr)[i];
		}
	}

	address.readFromFile(ifs);
	ifs.read((char*)&passengers, sizeof passengers);
	ifs.read((char*)&orderStatus, sizeof orderStatus);

	size_t declinedIdsCount = 0;
	ifs.read((char*)&declinedIdsCount, sizeof declinedIdsCount);
	for (size_t i = 0; i < declinedIdsCount; i++)
	{
		ifs.read((char*)&this->declinedDriverIds[i], sizeof this->declinedDriverIds[i]);
	}
}

void Order::print() const
{
	std::cout << "Order ID: " << this->id << std::endl;

	if (this->client != nullptr)
	{
		this->client->print();
	}
	if (this->driver != nullptr)
	{
		this->driver->print();
	}

	std::cout << "From: \n";
	this->address.print();
	std::cout << "To: \n";
	this->destination.print();
	std::cout << "Order status: " << OrderStatusToString(this->orderStatus) << '\n';

}

void Order::setDriver(Driver* driverPtr)
{
	this->driver = driverPtr;
}

void Order::pay(const double amount)
{
	if (client->getBalance() - amount < 0)
	{
		throw std::logic_error("Not enough funds.");
	}

	this->client->addToBalance(-amount);
	this->revenue = amount;
}

void Order::giveRatingToDriver(const double rating) const
{
	this->driver->giveRating(rating);
}
