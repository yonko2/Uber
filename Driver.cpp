#include "Driver.h"

Driver::Driver(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName,
	const MyString& carNumber, const MyString& phoneNumber) :
	User(username, password, firstName, lastName)
{
	this->carNumber = carNumber;
	this->phoneNumber = phoneNumber;
}
