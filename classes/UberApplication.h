#pragma once
#include "Client.h"
#include "Driver.h"
#include "../external/DynamicArray.hpp"
#include "Order.h"

enum class SessionActions
{
	registerUser,
	login,
	exit
};

class UberApplication // singleton
{
	User* loggedUser = nullptr;
	bool isClient = true;

	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

	void saveSession() const;
	void saveClients() const;
	void saveDrivers() const;
	void saveOrders() const;

	void loadSession();
	void loadClients();
	void loadDrivers();
	void loadOrders();

	static bool checkBinariesAvailability();
	Driver* getNearestFreeDriverPtr(const Pair<int, int>& origin);

	UberApplication() = default;
public:
	UberApplication(const UberApplication& other) = delete;
	UberApplication& operator=(const UberApplication& other) = delete;
	void acceptPayment(size_t orderId);

	static UberApplication& getInstance();

	bool usernameDriverExists(const MyString& username) const;

	void registerClient(Client&& client);
	void registerDriver(Driver&& driver);

	void load();
	void save() const;

	void printClientMinutesMsg();

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();

	const DynamicArray<Client>& getClients() const;
	const DynamicArray<Driver>& getDrivers() const;
	const DynamicArray<Order>& getOrders() const;

	const User* getLoggedUser() const;
	void setLoggedUser(User* userPtr);
	bool getIsLoggedUserClient() const;

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addDriver(const Driver& driver);
	void addDriver(Driver&& driver);
	void addOrder(Order&& order);

	void removeOrder(size_t orderId);
	void cancelOrder(size_t orderId);
	void pay(size_t orderId, double amount);

	void addDriverRating(const MyString& username, double rating);
	void acceptOrder(size_t orderId, int minutes);
	void declineOrder(size_t orderId);
	void checkOrder(size_t orderId);
	void finishOrder(size_t orderId);
	void checkMessages() const;
	void changeAddress(Address&& address);
	void order(Address&& address, Address&& destination, unsigned passengersCount);
	void addMoney(double amount);
};

static double getDist(const Pair<int, int>& first, const Pair<int, int>& second);

