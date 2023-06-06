#pragma once
#include "MyString.h"

class User
{
	static size_t latestId;

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
	User(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName);

public:
	static size_t getLatestId();
	static void setLatestId(size_t latestId);

	size_t getId() const;
	const MyString& getUsername() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getBalance() const;

	void addToBalance(double amount);

	bool comparePassword(const MyString& password) const;

	virtual void saveToFile(std::ofstream& ofs) const;
	virtual void readFromFile(std::ifstream& ifs);
	virtual void print() const;

	virtual ~User() = default;
};

