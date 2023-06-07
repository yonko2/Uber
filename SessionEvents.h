#pragma once
#include "UberApplication.h"

namespace SessionEvents
{
	void registerClient(UberApplication* uberApplication);
	void registerDriver(UberApplication* uberApplication);
	void registerUser(UberApplication* uberApplication);
	void login(UberApplication* uberApplication);
}
