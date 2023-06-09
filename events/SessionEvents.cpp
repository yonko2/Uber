#include "SessionEvents.h"
#include "MainMenuEvents.h"

void SessionEvents::registerClient(UberApplication* uberApplication) {
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

void SessionEvents::registerDriver(UberApplication* uberApplication) {
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

void SessionEvents::registerUser(UberApplication* uberApplication) {
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

void SessionEvents::login(UberApplication* uberApplication) {
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