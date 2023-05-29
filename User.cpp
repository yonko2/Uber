#include "User.h"

#include "HashingModule.h"

size_t User::latestId = 1;

User::User()
{
	this->id = latestId;
	latestId++;
}

User::User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName)
{
	this->id = latestId;
	latestId++;

	this->username = username;
	this->passwordHash = HashingModule::hashString(password);
	this->firstName = firstName;
	this->lastName = lastName;
}

size_t User::getId() const
{
	return this->id;
}

const MyString& User::getUsername() const
{
	return this->username;
}

const MyString& User::getFirstName() const
{
	return this->firstName;
}

const MyString& User::getLastName() const
{
	return this->lastName;
}

double User::getBalance() const
{
	return this->balance;
}

bool User::comparePassword(const MyString& password) const
{
	return HashingModule::hashString(password) == this->passwordHash;
}
