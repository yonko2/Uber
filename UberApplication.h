#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "Order.h"

enum class SessionActions
{
	registerUser,
	login,
	exit
};

class UberApplication // singleton
{
	UniquePointer<User> loggedUser = nullptr;
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

public:
	UberApplication() = default;
	UberApplication(const UberApplication& other) = delete; // because of UniquePointer
	UberApplication& operator=(const UberApplication& other) = delete; // because ofUniquePointer

	void registerClient(Client&& client);
	void registerDriver(Driver&& driver);

	void load();
	void save() const;

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();

	const DynamicArray<Client>& getClients() const;
	const DynamicArray<Driver>& getDrivers() const;
	const DynamicArray<Order>& getOrders() const;

	const UniquePointer<User>& getLoggedUser() const;
	UniquePointer<User>& getLoggedUser();
	bool getIsLoggedUserClient() const;

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addDriver(const Driver& driver);
	void addDriver(Driver&& driver);
	void addOrder(const Order& order);
	void addOrder(Order&& order);

	void removeOrder(size_t orderId);
	void cancelOrder(size_t orderId);
};

