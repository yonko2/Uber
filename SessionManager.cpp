#include "SessionManager.h"

void SessionManager::registerClient(UberApplication* system, const Client& client)
{
	system->clients.pushBack(client);
}

void SessionManager::registerClient(UberApplication* system, Client&& client)
{
	system->clients.pushBack(std::move(client));
}

void SessionManager::registerDriver(UberApplication* system, const Driver& driver)
{
	system->drivers.pushBack(driver);
}

void SessionManager::registerDriver(UberApplication* system, Driver&& driver)
{
	system->drivers.pushBack(std::move(driver));
}

void SessionManager::login(UberApplication* system, const MyString& username, const MyString& password)
{
	const size_t clientsCount = system->clients.getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (system->clients[i].getUsername() == username)
		{
			if (system->clients[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &system->clients[i] };
				this->isClient = true;
				return;
			}
		}
	}

	const size_t driversCount = system->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (system->drivers[i].getUsername() == username)
		{
			if (system->drivers[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &system->drivers[i] };
				this->isClient = false;
				return;
			}
		}
	}
}

void SessionManager::login(UberApplication* system, MyString&& username, MyString&& password)
{
	const size_t clientsCount = system->clients.getSize();
	for (size_t i = 0; i < clientsCount; i++)
	{
		if (system->clients[i].getUsername() == username)
		{
			if (system->clients[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &system->clients[i] };
				this->isClient = true;
				return;
			}
		}
	}

	const size_t driversCount = system->drivers.getSize();
	for (size_t i = 0; i < driversCount; i++)
	{
		if (system->drivers[i].getUsername() == username)
		{
			if (system->drivers[i].comparePassword(password))
			{
				this->loggedUser = UniquePointer<User>{ &system->drivers[i] };
				this->isClient = false;
				return;
			}
		}
	}
}

void SessionManager::logout()
{
	loggedUser.release();
}
