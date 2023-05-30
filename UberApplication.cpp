#include "UberApplication.h"

//void UberApplication::registerClient(const Client& client)
//{
//	this->clients.pushBack(client);
//}

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
}

void UberApplication::logout()
{
	loggedUser.release();
}
