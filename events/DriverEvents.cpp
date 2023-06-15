#include "DriverEvents.h"

void DriverEvents::acceptPayment(UberApplication* uberApplication) {
	size_t orderId = 0;
	std::cout << "Input order ID: ";
	std::cin >> orderId;

	try
	{
		uberApplication->acceptPayment(orderId);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void DriverEvents::acceptOrder(UberApplication* uberApplication) {
	size_t orderId = 0;
	std::cout << "Input order ID: ";
	std::cin >> orderId;
	short minutes = 0;
	std::cout << "Input minutes: ";
	std::cin >> minutes;

	try
	{
		uberApplication->acceptOrder(orderId, minutes);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void DriverEvents::checkMessages(UberApplication* uberApplication) {
	uberApplication->checkMessages();
}

void DriverEvents::changeAddress(UberApplication* uberApplication) {
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

	uberApplication->changeAddress(std::move(address));
	std::cout << "Address changed successfully." << std::endl;
}

void DriverEvents::declineOrder(UberApplication* uberApplication) {
	size_t orderId = 0;
	std::cout << "Input order ID: ";
	std::cin >> orderId;

	try
	{
		uberApplication->declineOrder(orderId);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}

void DriverEvents::finishOrder(UberApplication* uberApplication) {
	size_t orderId = 0;
	std::cout << "Input order ID: ";
	std::cin >> orderId;

	try
	{
		uberApplication->finishOrder(orderId);
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
}