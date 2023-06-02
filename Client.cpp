#include "Client.h"

Client::Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName) :
User(username,password,firstName,lastName)
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
