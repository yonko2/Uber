#include "Driver.h"

Driver::Driver(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName,
	const MyString& carNumber, const MyString& phoneNumber) :
	User(username, password, firstName, lastName)
{
	this->carNumber = carNumber;
	this->phoneNumber = phoneNumber;
}

Driver::Driver(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName,
	MyString&& carNumber, MyString&& phoneNumber) :
	User(std::move(username), std::move(password), std::move(firstName), std::move(lastName))
{
	this->carNumber = std::move(carNumber);
	this->phoneNumber = std::move(phoneNumber);
}

const Address& Driver::getAddress() const
{
	return this->address;
}

void Driver::setAddress(const Address& address)
{
	this->address = address;
}

void Driver::setAddress(Address&& address)
{
	this->address = std::move(address);
}

void Driver::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
	ofs.write((const char*)&rating, sizeof rating);
	carNumber.saveToFile(ofs);
	phoneNumber.saveToFile(ofs);
	address.saveToFile(ofs);
	ofs.write((const char*)&ratingsCount, sizeof ratingsCount);
	ofs.write((const char*)&ratingSum, sizeof ratingSum);
}

void Driver::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);
	ifs.read((char*)&rating, sizeof rating);
	carNumber.readFromFile(ifs);
	phoneNumber.readFromFile(ifs);
	address.readFromFile(ifs);
	ifs.read((char*)&ratingsCount, sizeof ratingsCount);
	ifs.read((char*)&ratingSum, sizeof ratingSum);
}

void Driver::print() const
{
	std::cout << "Driver ";
	User::print();
	std::cout << "Rating: ";
	if (rating != -1)
	{
		std::cout << rating << '\n';
	}
	else std::cout << "N/A\n";

	std::cout << "Car number: " << carNumber << '\n'
		<< "Phone number: " << phoneNumber << std::endl;
}

void Driver::giveRating(const double rating)
{
	this->ratingSum += rating;
	this->ratingsCount++;
	this->rating = this->ratingSum / this->ratingsCount;
}
