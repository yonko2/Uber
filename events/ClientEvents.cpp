#include "ClientEvents.h"

#include "MainMenuEvents.h"

void ClientEvents::order(UberApplication* uberApplication) {
	MyString addressName;
	int coordXAddress = 0, coordYAddress = 0;

	std::cout << "Input address name: ";
	std::cin >> addressName;
	std::cout << "Input address coordinates: ";
	std::cin >> coordXAddress;
	std::cin >> coordYAddress;
	std::cout << "Input address description (Press Enter for none): ";
	char buffer[256]{};
	std::cin.getline(buffer, 256);
	std::cin.ignore();
	MyString addressDescription{ buffer };

	Address address{ addressName, coordXAddress, coordYAddress, addressDescription };

	unsigned passengersCount = 0;
	std::cin >> passengersCount;

	MyString destinationName;
	int coordXDestination = 0, coordYDestination = 0;

	std::cout << "Input destination name: ";
	std::cin >> destinationName;
	std::cin >> coordXDestination;
	std::cin >> coordYDestination;
	std::cout << "Input destination description (Press Enter for none): ";
	char bufferDest[256]{};
	std::cin.getline(bufferDest, 256);
	std::cin.ignore();
	MyString destinationDescription{ buffer };

	Address destination{ destinationName, coordXDestination, coordYDestination, destinationDescription };

	try
	{
		Order order{
		dynamic_cast<Client*>(uberApplication->getLoggedUser().operator->()),
		uberApplication->getNearestFreeDriverPtr(address.coordinates),
		std::move(address),
		std::move(destination),
		passengersCount };

		std::cout << "Order ID: " << order.getId() << std::endl;
		uberApplication->addOrder(std::move(order));
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void ClientEvents::checkOrder(UberApplication* uberApplication) {
	try
	{
		size_t orderId = 0;
		std::cout << "Input order ID: ";
		std::cin >> orderId;

		const DynamicArray<Order>* ordersPtr = &uberApplication->getOrders();
		bool orderFound = false;
		for (size_t i = 0; i < ordersPtr->getSize(); i++)
		{
			if (ordersPtr->operator[](i).getId() == orderId)
			{
				ordersPtr->operator[](i).print();
				orderFound = true;
				break;
			}
		}
		if (!orderFound)
		{
			throw std::runtime_error("ID not found");
		}
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void ClientEvents::cancelOrder(UberApplication* uberApplication) {
	try
	{
		size_t orderId = 0;
		std::cout << "Input order ID: ";
		std::cin >> orderId;

		//uberApplication->removeOrder(orderId);
		uberApplication->cancelOrder(orderId);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void ClientEvents::pay(UberApplication* uberApplication) {
	size_t orderId = 0;
	std::cout << "Input order ID: ";
	std::cin >> orderId;
	double amount = 0;
	std::cout << "Input amount: ";
	std::cin >> amount;

	try
	{
		uberApplication->pay(orderId, amount);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void ClientEvents::rate(UberApplication* uberApplication) {
	MyString username;

	while (true)
	{
		try
		{
			std::cout << "Input driver username: ";
			std::cin >> username;

			if (!uberApplication->usernameDriverExists(username))
			{
				throw std::runtime_error("Driver doesn't exist.");
			}
			break;
		}
		catch (std::runtime_error& rex)
		{
			std::cout << rex.what() << std::endl;
		}
	}

	double rating = 0;

	while (true)
	{
		try
		{
			std::cout << "Input rating (1-5): ";
			std::cin >> rating;

			if (isInRange(rating,1,5))
			{
				throw std::runtime_error("Rating not in range.");
			}
			break;
		}
		catch (std::runtime_error& rex)
		{
			std::cout << rex.what() << std::endl;
		}
	}

	try
	{
		uberApplication->addDriverRating(username, rating);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void ClientEvents::addMoney(UberApplication* uberApplication) {
	try
	{
		double amount = 0;
		std::cout << "Input amount: ";
		std::cin >> amount;
		if (amount <= 0)
		{
			throw std::runtime_error("Money amount must be positive.");
		}

		uberApplication->getLoggedUser()->addToBalance(amount);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what();
	}
}