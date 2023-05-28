#pragma once
#include "MyString.h"

struct HashingModule
{
	static int hashString(const MyString& input);
	HashingModule() = delete;
};

