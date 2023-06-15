#include "UberApplication.h"

void UberApplication::saveSession() const
{
	std::ofstream session("session.dat", std::ios::out | std::ios::binary);
	if (!session.is_open())
	{
		throw std::exception("File not open.");
	}

	// Guard: session needs logged user
	if (this->getLoggedUser() != nullptr)
	{
		const size_t loggedUserId = this->loggedUser->getId();
		session.write((const char*)&loggedUserId, sizeof loggedUserId);
		session.write((const char*)&this->isClient, sizeof this->isClient);
	}

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

	if (session.peek() == std::ifstream::traits_type::eof()) // no logged user
	{
		session.close();
		return;
	}

	size_t loggedUserId = 0;
	session.read((char*)&loggedUserId, sizeof loggedUserId);
	session.read((char*)&this->isClient, sizeof this->isClient);
	if (this->isClient)
	{
		const size_t clientsCount = this->clients.getSize();
		for (size_t i = 0; i < clientsCount; i++)
		{
			if (this->clients[i].getId() == loggedUserId)
			{
				this->loggedUser = dynamic_cast<User*>(&this->clients[i]);
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
				this->loggedUser = dynamic_cast<User*>(&this->drivers[i]);
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

void UberApplication::checkOrder(const size_t orderId)
{
	const size_t ordersCount = orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (orders[i].getId() == orderId)
		{
			orders[i].print();
			return;
		}
	}
	throw std::runtime_error("ID not found");
}

void UberApplication::acceptPayment(const size_t orderId)
{
	const size_t ordersCount = orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (orders[i].getId() == orderId)
		{
			orders[i].driver->addToBalance(orders[i].revenue);
		}
	}
	throw std::runtime_error("ID not found");
}

UberApplication& UberApplication::getInstance()
{
	static UberApplication app;
	return app;
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

const User* UberApplication::getLoggedUser() const
{
	return this->loggedUser;
}

void UberApplication::setLoggedUser(User* userPtr)
{
	this->loggedUser = userPtr;
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
			// Throws if amount isn't enough
			this->orders[i].pay(amount);
			return;
		}
	}
	throw std::runtime_error("Order ID not found.");
}

double getDist(const Pair<int, int>& first, const Pair<int, int>& second)
{
	return std::abs(
		std::sqrt(std::pow(first.getFirst() - second.getFirst(), 2) +
			std::pow(first.getSecond() - second.getSecond(), 2)));
}

Driver* UberApplication::getNearestFreeDriverPtr(const Pair<int, int>& origin)
{
	const size_t driversCount = this->drivers.getSize();
	if (driversCount == 0)
	{
		throw std::runtime_error("No drivers available.");
	}

	double currentMinDist = -1;
	Driver* currentNearestFreeDriverPtr = nullptr;

	const size_t ordersCount = this->orders.getSize();
	for (size_t i = 0; i < ordersCount; i++)
	{
		Order* currentOrder = &orders[i];
		const DynamicArray<size_t>* declDrivers = &currentOrder->getDeclinedDriverIds();

		// Get nearest free driver
		if (currentOrder->getOrderStatus() != OrderStatus::accepted && // accepted -> driver is unavailable
			!declDrivers->contains(currentOrder->getDriver()->getId())) // driver hasn't declined
		{
			double iterDist = getDist(origin, currentOrder->getDriver()->getAddress().coordinates);

			if (currentMinDist == -1 || // safe comparison, true only first time
				iterDist - currentMinDist < 0)
			{
				currentMinDist = iterDist;
				currentNearestFreeDriverPtr = currentOrder->driver;
			}
		}
	}

	return currentNearestFreeDriverPtr;
}

bool UberApplication::usernameDriverExists(const MyString& username) const
{
	const size_t driversCount = this->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == username) return true;
	}

	return false;
}

void UberApplication::addDriverRating(const MyString& username, const double rating)
{
	const size_t ordersCount = this->orders.getSize();
	bool driverFound = false;
	for (size_t i = 0; i < ordersCount; i++)
	{
		if (orders[i].getDriver()->getUsername() == username)
		{
			driverFound = true;
			if (orders[i].getClient() == this->getLoggedUser() &&
				orders[i].getOrderStatus() == OrderStatus::completed)
			{
				orders[i].giveRatingToDriver(rating);
				return;
			}
		}
	}

	if (driverFound == false)
	{
		throw std::runtime_error("Driver not found.");
	}
	throw std::runtime_error("No valid order found.");
}

void UberApplication::acceptOrder(const size_t orderId, const int minutes)
{
	const size_t ordersCount = this->orders.getSize();
	bool orderFound = false;

	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId)
		{
			orderFound = true;
			if (this->orders[i].getDriver() != this->loggedUser)
			{
				throw std::logic_error("You don't have access to this order.");
			}
			if (this->orders[i].getOrderStatus() != OrderStatus::created)
			{
				throw std::logic_error("Order not available.");
			}

			this->orders[i].setOrderStatus(OrderStatus::accepted);
			this->orders[i].setMinutes(minutes);
		}
	}

	if (!orderFound)
	{
		throw std::logic_error("Order not found.");
	}
}

void UberApplication::declineOrder(const size_t orderId)
{
	const size_t ordersCount = this->orders.getSize();
	bool orderFound = false;

	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId)
		{
			orderFound = true;
			if (this->orders[i].getDriver() != this->loggedUser)
			{
				throw std::logic_error("You don't have access to this order.");
			}
			if (this->orders[i].getOrderStatus() != OrderStatus::created)
			{
				throw std::logic_error("Order not available.");
			}

			// Add current driver id to declined ids
			this->orders[i].getDeclinedDriverIds().pushBack(this->orders[i].getDriver()->getId());

			// Set driver to closest free one
			this->orders[i].setDriver(this->getNearestFreeDriverPtr(this->orders[i].getAddress().coordinates));
		}
	}

	if (!orderFound)
	{
		throw std::logic_error("Order not found.");
	}
}

void UberApplication::finishOrder(const size_t orderId)
{
	const size_t ordersCount = this->orders.getSize();
	bool orderFound = false;

	for (size_t i = 0; i < ordersCount; i++)
	{
		if (this->orders[i].getId() == orderId)
		{
			orderFound = true;
			if (this->orders[i].getDriver() != this->loggedUser)
			{
				throw std::logic_error("You don't have access to this order.");
			}
			if (this->orders[i].getOrderStatus() != OrderStatus::accepted)
			{
				throw std::logic_error("Order not available.");
			}

			this->orders[i].setOrderStatus(OrderStatus::completed);
		}
	}

	if (!orderFound)
	{
		throw std::logic_error("Order not found.");
	}
}

void UberApplication::checkMessages() const
{
	const size_t ordersCount = orders.getSize();
	const Driver* loggedDriver = dynamic_cast<Driver*>(this->loggedUser);

	for (size_t i = 0; i < ordersCount; i++)
	{
		if (orders[i].getDriver() == loggedDriver)
		{
			orders[i].print();
			std::cout << std::endl;
		}
	}
}

void UberApplication::changeAddress(Address&& address)
{
	if (isClient)
	{
		throw std::runtime_error("Can not change address of client");
	}
	dynamic_cast<Driver*>(this->loggedUser)->setAddress(std::move(address));
}

void UberApplication::order(Address&& address, Address&& destination, unsigned passengersCount)
{
	Order order{
		dynamic_cast<Client*>(loggedUser),
		getNearestFreeDriverPtr(address.coordinates),
		std::move(address),
		std::move(destination),
		passengersCount };
	std::cout << "Order ID: " << order.getId() << std::endl;

}

void UberApplication::addMoney(const double amount)
{
	if (!isClient)
	{
		throw std::runtime_error("Can't add money as non-client");
	}

	dynamic_cast<Client*>(this->loggedUser)->addToBalance(amount);
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
				this->loggedUser = dynamic_cast<User*>(&this->clients[i]);
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
				this->loggedUser = dynamic_cast<User*>(&this->drivers[i]);
				this->isClient = false;
				return;
			}
		}
	}

	throw std::runtime_error("User with password not found.");
}

void UberApplication::printClientMinutesMsg() {
	const size_t ordersCount = this->orders.getSize();

	for (size_t i = 0; i < ordersCount; i++)
	{
		if (orders[i].getClient() == this->loggedUser) // revise
		{
			orders[i].printMinutesMsg();
		}
	}
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
				this->loggedUser = dynamic_cast<User*>(&this->clients[i]);
				this->isClient = true;
				break;
			}
		}
	}

	if (this->isClient)
	{
		printClientMinutesMsg();
	}

	for (size_t i = 0; i < driversCount; i++)
	{
		if (this->drivers[i].getUsername() == username)
		{
			usernameFound = true;
			if (this->drivers[i].comparePassword(password))
			{
				this->loggedUser = dynamic_cast<User*>(&this->drivers[i]);
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
	this->loggedUser = nullptr;
}
