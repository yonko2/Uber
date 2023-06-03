#include "UberApplication.h"

//void UberApplication::registerClient(const Client& client)
//{
//	this->clients.pushBack(client);
//}

void UberApplication::saveSession() const
{
	std::ofstream session("session.dat", std::ios::out | std::ios::binary);
	if (!session.is_open())
	{
		throw std::exception("File not open.");
	}

	const size_t loggedUserId = this->loggedUser->getId();
	session.write((const char*)&loggedUserId, sizeof loggedUserId);
	session.write((const char*)&this->isClient, sizeof this->isClient);

	session.close();
}

void UberApplication::saveClients() const
{
	std::ofstream clientsFile("clients.dat", std::ios::out | std::ios::binary);
	if (!clientsFile.is_open())
	{
		throw std::exception("File not open.");
	}

	const size_t clientsCount = this->clients.getSize();
	clientsFile.write((const char*)&clientsCount, sizeof clientsCount);

	for (size_t i = 0; i < clientsCount; i++)
	{
		this->clients[i].saveToFile(clientsFile);
	}

	clientsFile.close();
}

void UberApplication::saveDrivers() const
{
	std::ofstream driversFile("drivers.dat", std::ios::out | std::ios::binary);
	if (!driversFile.is_open())
	{
		throw std::exception("File not open.");
	}

	const size_t driversCount = this->drivers.getSize();
	driversFile.write((const char*)&driversCount, sizeof driversCount);

	for (size_t i = 0; i < driversCount; i++)
	{
		this->drivers[i].saveToFile(driversFile);
	}

	driversFile.close();
}

void UberApplication::saveOrders() const
{
	std::ofstream ordersFile("orders.dat", std::ios::out | std::ios::binary);
	if (!ordersFile.is_open())
	{
		throw std::exception("File not open.");
	}

	const size_t ordersCount = this->orders.getSize();
	ordersFile.write((const char*)&ordersCount, sizeof ordersCount);

	for (size_t i = 0; i < ordersCount; i++)
	{
		this->orders[i].saveToFile(ordersFile);
	}

	ordersFile.close();
}

void UberApplication::loadSession()
{
	std::ifstream session("session.dat", std::ios::in | std::ios::binary);
	if (!session.is_open())
	{
		throw std::exception("File not open.");
	}

	size_t loggedUserId = 0;
	session.read((char*)&loggedUserId, sizeof loggedUserId);
	session.read((char*)&this->isClient, sizeof this->isClient);
	if (this->isClient)
	{
		const size_t clientsCount = this->clients.getSize();
		for (size_t i = 0; i < clientsCount; i++)
		{
			if (this->clients[i].getId()==loggedUserId)
			{
				this->loggedUser = UniquePointer<User>{ &this->clients[i] };
			}
		}
	}
	else
	{
		const size_t driversCount = this->drivers.getSize();
		for (size_t i = 0; i < driversCount; i++)
		{
			if (this->drivers[i].getId() == loggedUserId)
			{
				this->loggedUser = UniquePointer<User>{ &this->drivers[i] };
			}
		}
	}

	session.close();
}

void UberApplication::loadClients()
{
	std::ifstream clientsFile("clients.dat", std::ios::in | std::ios::binary);
	if (!clientsFile.is_open())
	{
		throw std::exception("File not open.");
	}

	size_t clientsCount = 0;
	clientsFile.read((char*)&clientsCount, sizeof clientsCount);

	for (size_t i = 0; i < clientsCount; i++)
	{
		Client currClient;
		currClient.readFromFile(clientsFile);
		this->clients.pushBack(std::move(currClient));
	}

	clientsFile.close();
}

void UberApplication::loadDrivers()
{
	std::ifstream driversFile("drivers.dat", std::ios::in | std::ios::binary);
	if (!driversFile.is_open())
	{
		throw std::exception("File not open.");
	}

	size_t driversCount = 0;
	driversFile.read((char*)&driversCount, sizeof driversCount);

	for (size_t i = 0; i < driversCount; i++)
	{
		Driver currDriver;
		currDriver.readFromFile(driversFile);
		this->drivers.pushBack(std::move(currDriver));
	}

	driversFile.close();
}

void UberApplication::loadOrders()
{
	std::ifstream ordersFile("orders.dat", std::ios::in | std::ios::binary);
	if (!ordersFile.is_open())
	{
		throw std::exception("File not open.");
	}

	size_t ordersCount = 0;
	ordersFile.read((char*)&ordersCount, sizeof ordersCount);

	for (size_t i = 0; i < ordersCount; i++)
	{
		Order currOrder;
		currOrder.readFromFile(&this->clients, &this->drivers, ordersFile);
		this->orders.pushBack(std::move(currOrder));
	}

	ordersFile.close();
}

void UberApplication::registerClient(Client&& client)
{
	this->clients.pushBack(std::move(client));
}

//void UberApplication::registerDriver(const Driver& driver)
//{
//	this->drivers.pushBack(driver);
//}

void UberApplication::registerDriver(Driver&& driver)
{
	this->drivers.pushBack(std::move(driver));
}

void UberApplication::load()
{
	loadSession();
	loadClients();
	loadDrivers();
	loadOrders();
}

void UberApplication::save() const
{
	saveSession();
	saveClients();
	saveDrivers();
	saveOrders();
}

const DynamicArray<Client>& UberApplication::getClients() const
{
	return this->clients;
}

const UniquePointer<User>& UberApplication::getLoggedUser() const
{
	return this->loggedUser;
}

bool UberApplication::getIsLoggedUserClient() const
{
	return this->isClient;
}

void UberApplication::login(const MyString& username, const MyString& password)
{
	const size_t clientsCount = this->clients.getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (this->clients[i].getUsername() == username)
		{
			if (this->clients[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &this->clients[i] };
				this->isClient = true;
				return;
			}
		}
	}

	const size_t driversCount = this->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == username)
		{
			if (this->drivers[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &this->drivers[i] };
				this->isClient = false;
				return;
			}
		}
	}

	throw std::runtime_error("User with password not found.");
}

void UberApplication::login(MyString&& username, MyString&& password)
{
	const size_t clientsCount = this->clients.getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (this->clients[i].getUsername() == username)
		{
			if (this->clients[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &this->clients[i] };
				this->isClient = true;
				return;
			}
		}
	}

	const size_t driversCount = this->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == username)
		{
			if (this->drivers[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &this->drivers[i] };
				this->isClient = false;
				return;
			}
		}
	}

	throw std::runtime_error("User with password not found.");
}

void UberApplication::logout()
{
	loggedUser.release();
}
