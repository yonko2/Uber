#pragma once
#include "UberApplication.h"
#include "UniquePointer.hpp"
#include "User.h"
#include "Client.h"
#include "Driver.h"

struct SessionManager // singleton
{
	UniquePointer<User> loggedUser;
	bool isClient = true;

	static void registerClient(UberApplication* system, const Client& client);
	static void registerClient(UberApplication* system, Client&& client);
	static void registerDriver(UberApplication* system, const Driver& driver);
	static void registerDriver(UberApplication* system, Driver&& driver);
	void login(UberApplication* system, const MyString& username, const MyString& password);
	void login(UberApplication* system, MyString&& username, MyString&& password);
	void logout();
};

