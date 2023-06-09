#include "HashingModule.h"

/**
 * @source https://dev.to/muiz6/string-hashing-in-c-1np3
 */
int HashingModule::hashString(const MyString& input)
{
	const int PRIME_CONST = 31;

	int hashCode = 0;
	const size_t inputLength = input.length();
	for (size_t i = 0; i < inputLength; i++) {
		hashCode += input[i] * pow(PRIME_CONST, i);
	}
	return hashCode;
}
