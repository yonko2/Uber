#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "Order.h"

class UberApplication // singleton
{
	UniquePointer<User> loggedUser = nullptr;
	bool isClient = true;

	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

public:
	UberApplication() = default;
	UberApplication(const UberApplication& other) = delete; // because of UniquePointer
	UberApplication& operator=(const UberApplication& other) = delete; // because ofUniquePointer

	void registerClient(Client&& client);
	void registerDriver(Driver&& driver);

	void load() const;
	void save() const;

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();

	const DynamicArray<Client>& getClients() const;
};

