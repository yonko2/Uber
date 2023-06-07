#pragma once
#include "UberApplication.h"

namespace ClientEvents
{
	void order(UberApplication* uberApplication);
	void checkOrder(UberApplication* uberApplication);
	void cancelOrder(UberApplication* uberApplication);
	void pay(UberApplication* uberApplication);
	void rate(UberApplication* uberApplication);
	void addMoney(UberApplication* uberApplication);
}
