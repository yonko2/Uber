#pragma once
#include "../classes/UberApplication.h"

namespace DriverEvents
{
	void acceptPayment(UberApplication* uberApplication);
	void acceptOrder(UberApplication* uberApplication);
	void checkMessages(UberApplication* uberApplication);
	void changeAddress(UberApplication* uberApplication);
	void declineOrder(UberApplication* uberApplication);
	void finishOrder(UberApplication* uberApplication);
}

