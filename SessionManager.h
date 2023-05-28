#pragma once
#include "UberApplication.h"
#include "UniquePointer.hpp"
#include "User.h"

class SessionManager // singleton
{
	UniquePointer<User> loggedUser;
	bool isClient = true;

	void registerUser();
	void login();
	void logout();
};

