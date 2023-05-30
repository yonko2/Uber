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
		const short MAX_CLIENT_ACTION = 7;

		std::cout << "Choose an option:\n1) Make order\n2) Check order3) Cancel order\n"
			<< "4) Pay\n5) Rate\n6) Add money\n7) Logout";
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
		default:
			throw std::logic_error("Unknown command.");
		}
	}

	SessionActions getSessionAction()
	{
		const short MIN_SESSION_ACTION = 1;
		const short MAX_SESSION_ACTION = 2;

		std::cout << "Choose an option:\n1) Register user\2) Login\n";
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
		default:
			throw std::logic_error("Unknown command.");
		}
	}

	DriverActions getDriverAction()
	{
		const short MIN_SESSION_ACTION = 1;
		const short MAX_SESSION_ACTION = 7;

		std::cout << "Choose an option:\n1) Change address\2) Check messages\n"
			<< "3) Accept order\n4) Decline order\n5) Finish order\n6) Accept payment\n"
			<< "7) Logout\n";
		short sessionOption = 0;
		std::cin >> sessionOption;

		while (!isInRange(sessionOption, MIN_SESSION_ACTION, MAX_SESSION_ACTION))
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
		default:
			throw std::logic_error("Unknown command.");
		}
	}
}

namespace EventHandlers
{
	namespace SessionEvents
	{
		void registerUser(UberApplication* uberApplication) {

		}
		void login(UberApplication* uberApplication) {

		}
	}

	namespace ClientEvents
	{
		void order(UberApplication* uberApplication) {

		}
		void checkOrder(UberApplication* uberApplication) {

		}
		void cancelOrder(UberApplication* uberApplication) {

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
			switch (SessionActions sessionActions = MenuInputGetters::getSessionAction())
			{
			case SessionActions::registerUser:
				SessionEvents::registerUser(uberApplication);
				break;
			case SessionActions::login:
				SessionEvents::login(uberApplication);
				break;
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
}
