#include "UberApplication.h"

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

	const size_t latestId = Client::getLatestId();
	clientsFile.write((const char*)&latestId, sizeof latestId);

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

	const size_t latestId = Order::getLatestId();
	ordersFile.write((const char*)&latestId, sizeof latestId);

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

	size_t latestId = 0;
	clientsFile.read((char*)&latestId, sizeof latestId);
	User::setLatestId(latestId);

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

	size_t latestId = 0;
	ordersFile.read((char*)&latestId, sizeof latestId);
	Order::setLatestId(latestId);

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

bool UberApplication::checkBinariesAvailability()
{
	std::ifstream check("session.dat", std::ios::in | std::ios::binary | std::ios::_Nocreate);

	const bool toReturn = check.is_open();
	check.close();

	return toReturn;
}

void UberApplication::registerClient(Client&& client)
{
	const size_t clientsCount = this->clients.getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (this->clients[i].getUsername() == client.getUsername())
		{
			throw std::runtime_error("Username already exists.");
		}
	}
	this->clients.pushBack(std::move(client));
}

void UberApplication::registerDriver(Driver&& driver)
{
	const size_t driversCount = this->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == driver.getUsername())
		{
			throw std::runtime_error("Username already exists.");
		}
	}
	this->drivers.pushBack(std::move(driver));
}

void UberApplication::load()
{
	// Don't load files if they're missing
	if (!checkBinariesAvailability()) return;

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

const DynamicArray<Driver>& UberApplication::getDrivers() const
{
	return this->drivers;
}

const DynamicArray<Order>& UberApplication::getOrders() const
{
	return this->orders;
}

const UniquePointer<User>& UberApplication::getLoggedUser() const
{
	return this->loggedUser;
}

UniquePointer<User>& UberApplication::getLoggedUser()
{
	return this->loggedUser;
}

bool UberApplication::getIsLoggedUserClient() const
{
	return this->isClient;
}

void UberApplication::addClient(const Client& client)
{
	this->clients.pushBack(client);
}

void UberApplication::addClient(Client&& client)
{
	this->clients.pushBack(std::move(client));
}

void UberApplication::addDriver(const Driver& driver)
{
	this->drivers.pushBack(driver);
}

void UberApplication::addDriver(Driver&& driver)
{
	this->drivers.pushBack(std::move(driver));
}

void UberApplication::addOrder(const Order& order)
{
	this->orders.pushBack(order);
}

void UberApplication::addOrder(Order&& order)
{
	this->orders.pushBack(std::move(order));
}

void UberApplication::removeOrder(const size_t orderId)
{
	const size_t ordersCount = this->orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId)
		{
			this->orders.removeAt(i);
			return;
		}
	}
	throw std::runtime_error("Order ID not found.");
}

void UberApplication::cancelOrder(const size_t orderId)
{
	const size_t ordersCount = this->orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId)
		{
			//this->orders[i].setDriver(UniquePointer{ nullptr });
			this->orders[i].setOrderStatus(OrderStatus::canceled);
			return;
		}
	}
	throw std::runtime_error("Order ID not found.");
}

void UberApplication::pay(const size_t orderId, const double amount)
{
	const size_t ordersCount = this->orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId &&
			this->orders[i].getOrderStatus() == OrderStatus::completed)
		{
			Client* clientPtr = this->orders[i].getClient().operator->();
			if (clientPtr->getBalance() - amount < 0)
			{
				throw std::logic_error("Not enough funds.");
			}
			clientPtr->addToBalance(-amount);

			Driver* driverPtr = this->orders[i].getDriver().operator->();
			driverPtr->addToBalance(amount);
		}
	}
	throw std::runtime_error("Order ID not found.");
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
	const size_t driversCount = this->drivers.getSize();

	if (clientsCount == 0 && driversCount == 0)
	{
		throw std::logic_error("No users available for login - register first.");
	}

	bool usernameFound = false;
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (this->clients[i].getUsername() == username)
		{
			usernameFound = true;
			if (this->clients[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ dynamic_cast<User*>(& this->clients[i])};
				this->isClient = true;
				return;
			}
		}
	}

	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == username)
		{
			usernameFound = true;
			if (this->drivers[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &this->drivers[i] };
				this->isClient = false;
				return;
			}
		}
	}

	if (usernameFound)
	{
		throw std::runtime_error("User with username not found.");
	}
	throw std::runtime_error("User with password not found.");
}

void UberApplication::logout()
{
	loggedUser.release();
}
