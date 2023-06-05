#include <iostream>

#include "UberApplication.h"

const char* INVALID_OPTION_MESSAGE = "Please input a valid option.\n";

static bool isInRange(const short num, const short LOWER_BOUND, const short UPPER_BOUND)
{
	return num >= LOWER_BOUND && num <= UPPER_BOUND;
}

namespace MenuInputGetters
{
	ClientActions getClientAction()
	{
		const short MIN_CLIENT_ACTION = 1;
		const short MAX_CLIENT_ACTION = 8;

		std::cout << "Choose an option:\n1) Make order\n2) Check order3) Cancel order\n"
			<< "4) Pay\n5) Rate\n6) Add money\n7) Logout\n8) Exit";
		short clientOption = 0;
		std::cin >> clientOption;

		while (!isInRange(clientOption, MIN_CLIENT_ACTION, MAX_CLIENT_ACTION))
		{
			std::cout << INVALID_OPTION_MESSAGE;
			std::cin >> clientOption;
		}

		switch (clientOption)
		{
		case 1: return ClientActions::order;
		case 2: return ClientActions::checkOrder;
		case 3: return ClientActions::cancelOrder;
		case 4: return ClientActions::pay;
		case 5: return ClientActions::rate;
		case 6: return ClientActions::add_money;
		case 7: return ClientActions::logout;
		case 8: return ClientActions::exit;
		default:
			throw std::logic_error("Unknown command.");
		}
	}

	SessionActions getSessionAction()
	{
		const short MIN_SESSION_ACTION = 1;
		const short MAX_SESSION_ACTION = 3;

		std::cout << "Choose an option:\n1) Register user\n2) Login\n3) Exit\n";
		short sessionOption = 0;
		std::cin >> sessionOption;

		while (!isInRange(sessionOption, MIN_SESSION_ACTION, MAX_SESSION_ACTION))
		{
			std::cout << INVALID_OPTION_MESSAGE;
			std::cin >> sessionOption;
		}

		switch (sessionOption)
		{
		case 1: return SessionActions::registerUser;
		case 2: return SessionActions::login;
		case 3: return SessionActions::exit;
		default:
			throw std::logic_error("Unknown command.");
		}
	}

	DriverActions getDriverAction()
	{
		const short MIN_DRIVER_ACTION = 1;
		const short MAX_DRIVER_ACTION = 7;

		std::cout << "Choose an option:\n1) Change address\2) Check messages\n"
			<< "3) Accept order\n4) Decline order\n5) Finish order\n6) Accept payment\n"
			<< "7) Logout\n8) Exit\n";
		short sessionOption = 0;
		std::cin >> sessionOption;

		while (!isInRange(sessionOption, MIN_DRIVER_ACTION, MAX_DRIVER_ACTION))
		{
			std::cout << INVALID_OPTION_MESSAGE;
			std::cin >> sessionOption;
		}

		switch (sessionOption)
		{
		case 1:return DriverActions::changeAddress;
		case 2:return DriverActions::checkMessages;
		case 3:return DriverActions::acceptOrder;
		case 4:return DriverActions::declineOrder;
		case 5:return DriverActions::finishOrder;
		case 6:return DriverActions::acceptPayment;
		case 7:return DriverActions::logout;
		case 8:return DriverActions::exit;
		default:
			throw std::logic_error("Unknown command.");
		}
	}
}

namespace EventHandlers
{
	void exitApplication(UberApplication* uberApplication)
	{
		uberApplication->save();
		exit(EXIT_SUCCESS);
	}

	namespace SessionEvents
	{
		void registerClient(UberApplication* uberApplication) {
			do
			{
				try
				{
					MyString username, password, firstName, lastName;
					std::cout << "Input username: ";
					std::cin >> username;
					std::cout << "Input password: ";
					std::cin >> password;
					std::cout << "Input first name: ";
					std::cin >> firstName;
					std::cout << "Input last name: ";
					std::cin >> lastName;

					uberApplication->registerClient(Client{
						std::move(username),std::move(password),std::move(firstName),std::move(lastName) });
					break;
				}
				catch (std::runtime_error& rex)
				{
					std::cout << rex.what() << std::endl;
				}
			} while (true);

			std::cout << "\nClient registered successfully\n";
		}

		void registerDriver(UberApplication* uberApplication) {
			do
			{
				try
				{
					MyString username, password, firstName, lastName, carNumber, phoneNumber;
					std::cout << "\nInput username: ";
					std::cin >> username;
					std::cout << "\nInput password: ";
					std::cin >> password;
					std::cout << "\nInput first name: ";
					std::cin >> firstName;
					std::cout << "\nInput last name: ";
					std::cin >> lastName;
					std::cout << "\nInput car number: ";
					std::cin >> carNumber;
					std::cout << "\nInput phone number: ";
					std::cin >> phoneNumber;

					uberApplication->registerDriver(
						Driver{ username,password,firstName,lastName,carNumber,phoneNumber });
					break;
				}
				catch (std::runtime_error& rex)
				{
					std::cout << rex.what() << std::endl;
				}
			} while (true);

			std::cout << "\nDriver registered successfully\n";
		}

		void registerUser(UberApplication* uberApplication) {
			const short MIN_USER_OPTION = 1;
			const short MAX_USER_OPTION = 2;

			std::cout << "Choose: 1) Client 2) Driver: ";
			short userType = 0;
			std::cin >> userType;

			while (!isInRange(userType, MIN_USER_OPTION, MAX_USER_OPTION))
			{
				std::cout << INVALID_OPTION_MESSAGE;
				std::cin >> userType;
			}

			switch (userType)
			{
			case 1:
				SessionEvents::registerClient(uberApplication);
				break;
			case 2:
				SessionEvents::registerDriver(uberApplication);
				break;
			default:
				throw std::logic_error("Unknown command.");
			}
		}

		void login(UberApplication* uberApplication) {
			do
			{
				MyString username, password;
				std::cout << "\nInput username: ";
				std::cin >> username;
				std::cout << "\nInput password: ";
				std::cin >> password;

				try
				{
					uberApplication->login(std::move(username), std::move(password));
					std::cout << "Login successful.\n";
					break;
				}
				catch (std::logic_error& lex) // no users
				{
					std::cout << lex.what() << std::endl;
					break;
				}
				catch (std::runtime_error& rtex)
				{
					std::cout << rtex.what() << std::endl;
				}
			} while (true);
		}
	}

	namespace ClientEvents
	{
		void order(UberApplication* uberApplication) {
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

			Order order{
				dynamic_cast<Client*>(uberApplication->getLoggedUser().operator->()),
				nullptr,
				std::move(address),
				std::move(destination),
				passengersCount };

			std::cout << "Order ID: " << order.getId() << std::endl;
			uberApplication->addOrder(std::move(order));
		}
		void checkOrder(UberApplication* uberApplication) {
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
		void cancelOrder(UberApplication* uberApplication) {
			try
			{
				size_t orderId = 0;
				std::cout << "Input order ID: ";
				std::cin >> orderId;

				uberApplication->removeOrder(orderId);
			}
			catch (std::runtime_error& rex)
			{
				std::cout << rex.what() << std::endl;
			}
		}
		void pay(UberApplication* uberApplication) {

		}
		void rate(UberApplication* uberApplication) {

		}
		void addMoney(UberApplication* uberApplication) {

		}
	}

	namespace DriverEvents
	{
		void acceptPayment(UberApplication* uberApplication) {

		}
		void acceptOrder(UberApplication* uberApplication) {

		}
		void checkMessages(UberApplication* uberApplication) {

		}
		void changeAddress(UberApplication* uberApplication) {

		}
		void declineOrder(UberApplication* uberApplication) {

		}
		void finishOrder(UberApplication* uberApplication) {

		}
	}

	namespace MainMenuEvents
	{
		void handleLoginOrRegisterMenu(UberApplication* uberApplication)
		{
			switch (MenuInputGetters::getSessionAction())
			{
			case SessionActions::registerUser:
				SessionEvents::registerUser(uberApplication);
				break;
			case SessionActions::login:
				SessionEvents::login(uberApplication);
				break;
			case SessionActions::exit:
				exitApplication(uberApplication);
				break;
			default:
				throw std::logic_error("Unknown command.");
			}
		}

		void handleClientMenu(UberApplication* uberApplication)
		{
			ClientActions clientAction = MenuInputGetters::getClientAction();
			while (clientAction != ClientActions::logout)
			{
				switch (clientAction)
				{
				case ClientActions::order:
					ClientEvents::order(uberApplication);
					break;
				case ClientActions::checkOrder:
					ClientEvents::checkOrder(uberApplication);
					break;
				case ClientActions::cancelOrder:
					ClientEvents::cancelOrder(uberApplication);
					break;
				case ClientActions::pay:
					ClientEvents::pay(uberApplication);
					break;
				case ClientActions::rate:
					ClientEvents::rate(uberApplication);
					break;
				case ClientActions::add_money:
					ClientEvents::addMoney(uberApplication);
					break;
				case ClientActions::exit:
					exitApplication(uberApplication);
					break;
				default:
					throw std::logic_error("Unknown command.");
				}

				clientAction = MenuInputGetters::getClientAction();
			}

			uberApplication->logout();
		}

		void handleDriverMenu(UberApplication* uberApplication)
		{
			DriverActions driverAction = MenuInputGetters::getDriverAction();
			while (driverAction != DriverActions::logout)
			{
				switch (driverAction)
				{
				case DriverActions::changeAddress:
					DriverEvents::changeAddress(uberApplication);
					break;
				case DriverActions::checkMessages:
					DriverEvents::checkMessages(uberApplication);
					break;
				case DriverActions::acceptOrder:
					DriverEvents::acceptOrder(uberApplication);
					break;
				case DriverActions::declineOrder:
					DriverEvents::declineOrder(uberApplication);
					break;
				case DriverActions::finishOrder:
					DriverEvents::finishOrder(uberApplication);
					break;
				case DriverActions::acceptPayment:
					DriverEvents::acceptPayment(uberApplication);
					break;
				case DriverActions::exit:
					exitApplication(uberApplication);
					break;
				default:
					throw std::logic_error("Unknown command.");
				}

				driverAction = MenuInputGetters::getDriverAction();
			}

			uberApplication->logout();
		}
	}
}

int main()
{
	UberApplication uberApplication;
	uberApplication.load();

	do
	{
		if (uberApplication.getLoggedUser().operator->() == nullptr)
		{
			EventHandlers::MainMenuEvents::handleLoginOrRegisterMenu(&uberApplication);
		}
		else if (uberApplication.getIsLoggedUserClient())
		{
			EventHandlers::MainMenuEvents::handleClientMenu(&uberApplication);
		}
		else
		{
			EventHandlers::MainMenuEvents::handleDriverMenu(&uberApplication);
		}
	} while (true);
}
