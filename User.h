#pragma once
#include "MyString.h"
#include "SessionManager.h"

class User
{
	static size_t latestId = 1;

	size_t id = 0;
	MyString username;
	int passwordHash = 0;

	MyString firstName;
	MyString lastName;
	double balance = 0;

protected:
	User();
	User(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);

	static void logout(SessionManager* session);
public:
	size_t getId() const;
	const MyString& getUsername() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getBalance() const;

	bool comparePassword(const MyString& password) const;

};

