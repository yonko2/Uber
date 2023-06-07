#include "UberApplication.h"
#include "MainMenuEvents.h"

int main()
{
	UberApplication uberApplication;
	uberApplication.load();

	do
	{
		if (uberApplication.getLoggedUser().operator->() == nullptr)
		{
			MainMenuEvents::handleLoginOrRegisterMenu(&uberApplication);
		}
		else if (uberApplication.getIsLoggedUserClient())
		{
			MainMenuEvents::handleClientMenu(&uberApplication);
		}
		else
		{
			MainMenuEvents::handleDriverMenu(&uberApplication);
		}
	} while (true);
}
