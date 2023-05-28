#pragma once
#include "MyString.h"

class User
{
	size_t id = 0;
	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;
	double balance = 0;

	void logout() const; // call sessionManager
};

