#include "MainMenuEvents.h"

ClientActions MenuInputGetters::getClientAction()
{
	const short MIN_CLIENT_ACTION = 1;
	const short MAX_CLIENT_ACTION = 8;

	std::cout << "\nChoose an option:\n1) Make order\n2) Check order\n3) Cancel order\n"
		<< "4) Pay\n5) Rate\n6) Add money\n7) Logout\n8) Exit\n";
	short clientOption = 0;
	std::cin >> clientOption;

	while (!isInRange(clientOption, MIN_CLIENT_ACTION, MAX_CLIENT_ACTION))
	{
		std::cout << INVALID_OPTION_MESSAGE;
		std::cin.clear();
		std::cin.ignore();
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

SessionActions MenuInputGetters::getSessionAction()
{
	const short MIN_SESSION_ACTION = 1;
	const short MAX_SESSION_ACTION = 4;

	std::cout << "\nChoose an option:\n1) Register user\n" <<
			  "2) Login\n3) Stats\n4) Exit\n";
	short sessionOption = 0;
	std::cin >> sessionOption;

	while (!isInRange(sessionOption, MIN_SESSION_ACTION, MAX_SESSION_ACTION))
	{
		std::cout << INVALID_OPTION_MESSAGE;
		std::cin.clear();
		std::cin.ignore();
		std::cin >> sessionOption;
	}

	switch (sessionOption)
	{
	case 1: return SessionActions::registerUser;
	case 2: return SessionActions::login;
	case 3: return SessionActions::stats;
	case 4: return SessionActions::exit;
	default:
		throw std::logic_error("Unknown command.");
	}
}

DriverActions MenuInputGetters::getDriverAction()
{
	const short MIN_DRIVER_ACTION = 1;
	const short MAX_DRIVER_ACTION = 8;

	std::cout << "\nChoose an option:\n1) Change address\n2) Check messages\n"
		<< "3) Accept order\n4) Decline order\n5) Finish order\n6) Accept payment\n"
		<< "7) Logout\n8) Exit\n";
	short sessionOption = 0;
	std::cin >> sessionOption;

	while (!isInRange(sessionOption, MIN_DRIVER_ACTION, MAX_DRIVER_ACTION))
	{
		std::cout << INVALID_OPTION_MESSAGE;
		std::cin.clear();
		std::cin.ignore();
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

void MainMenuEvents::handleLoginOrRegisterMenu(UberApplication* uberApplication)
{
	switch (MenuInputGetters::getSessionAction())
	{
	case SessionActions::registerUser:
		SessionEvents::registerUser(uberApplication);
		break;
	case SessionActions::login:
		SessionEvents::login(uberApplication);
		break;
	case SessionActions::stats:
		SessionEvents::stats(uberApplication);
		break;
	case SessionActions::exit:
		exitApplication(uberApplication);
		break;
	default:
		throw std::logic_error("Unknown command.");
	}
}

void MainMenuEvents::handleClientMenu(UberApplication* uberApplication)
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

void MainMenuEvents::handleDriverMenu(UberApplication* uberApplication)
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

void exitApplication(UberApplication* uberApplication)
{
	uberApplication->save();
	exit(EXIT_SUCCESS);
}
