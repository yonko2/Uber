#include "Client.h"

Client::Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName) :
User(username,password,firstName,lastName)
{
}

Client::Client(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName):
User(std::move(username),std::move(password),std::move(firstName),std::move(lastName))
{
}

void Client::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
}

void Client::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);
}

void Client::print() const
{
	User::print();
}
