#include "User.h"

#include "../external/HashingModule.h"

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

User::User(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName)
{
	this->id = latestId;
	latestId++;

	this->username = std::move(username);
	this->passwordHash = HashingModule::hashString(std::move(password));
	this->firstName = std::move(firstName);
	this->lastName = std::move(lastName);
}

size_t User::getLatestId()
{
	return User::latestId;
}

void User::setLatestId(const size_t latestId)
{
	User::latestId = latestId;
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

void User::addToBalance(const double amount)
{
	this->balance += amount;
}

bool User::comparePassword(const MyString& password) const
{
	return HashingModule::hashString(password) == this->passwordHash;
}

void User::saveToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof id);
	username.saveToFile(ofs);
	ofs.write((const char*)&passwordHash, sizeof passwordHash);
	firstName.saveToFile(ofs);
	lastName.saveToFile(ofs);
	ofs.write((const char*)&balance, sizeof balance);
}

void User::readFromFile(std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof id);
	username.readFromFile(ifs);
	ifs.read((char*)&passwordHash, sizeof passwordHash);
	firstName.readFromFile(ifs);
	lastName.readFromFile(ifs);
	ifs.read((char*)&balance, sizeof balance);
}

void User::print() const
{
	std::cout << "Username: " << username << '\n'
		<< "First name: " << firstName << '\n'
		<< "Last name: " << lastName << '\n';
		//<< "Balance: " << balance << std::endl;
}
