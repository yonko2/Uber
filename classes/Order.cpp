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
	this->client = UniquePointer<Client>{ client };
	this->driver = UniquePointer<Driver>{ driver };
	this->address = address;
	this->destination = destination;
	this->passengers = passengers;
}

Order::Order(Client* client, Driver* driver, Address&& address, Address&& destination, const unsigned passengers)
{
	this->client = UniquePointer<Client>{ client };
	this->driver = UniquePointer<Driver>{ driver };
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

UniquePointer<Client>& Order::getClient()
{
	return this->client;
}

UniquePointer<Driver>& Order::getDriver()
{
	return this->driver;
}

void Order::setOrderStatus(const OrderStatus orderStatus)
{
	this->orderStatus = orderStatus;
}

void Order::saveToFile(std::ofstream& ofs) const
{
	if (client.operator->() == nullptr || driver.operator->() == nullptr)
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
			this->client = UniquePointer<Client>{ &(*clientsPtr)[i] };
		}
	}

	size_t driverId = 0;
	ifs.read((char*)&driverId, sizeof driverId);
	const size_t driversCount = driversPtr->getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if ((*driversPtr)[i].getId() == driverId)
		{
			this->driver = UniquePointer<Driver>{ &(*driversPtr)[i] };
		}
	}

	address.readFromFile(ifs);
	ifs.read((char*)&passengers, sizeof passengers);
	ifs.read((char*)&orderStatus, sizeof orderStatus);
}

void Order::print() const
{
	std::cout << "Order status: " << OrderStatusToString(this->orderStatus) << '\n';

	if (this->driver.operator->() != nullptr)
	{
		this->driver->print();
	}
}

void Order::setDriver(UniquePointer<Driver>&& driverPtr)
{
	this->driver = std::move(driverPtr);
}
