#pragma once
#include "SessionEvents.h"
#include "ClientEvents.h"
#include "DriverEvents.h"

inline const char* INVALID_OPTION_MESSAGE = "Please input a valid option.\n";

inline bool isInRange(const short num, const short LOWER_BOUND, const short UPPER_BOUND)
{
	return num >= LOWER_BOUND && num <= UPPER_BOUND;
}

inline bool isInRange(const double num, const double LOWER_BOUND, const double UPPER_BOUND)
{
	return (num - LOWER_BOUND >= 0) && (num - UPPER_BOUND <= 0);
}

void exitApplication(UberApplication* uberApplication);

namespace MenuInputGetters
{
	ClientActions getClientAction();
	SessionActions getSessionAction();
	DriverActions getDriverAction();
	
}

namespace MainMenuEvents
{
	void handleLoginOrRegisterMenu(UberApplication* uberApplication);
	void handleClientMenu(UberApplication* uberApplication);
	void handleDriverMenu(UberApplication* uberApplication);
}