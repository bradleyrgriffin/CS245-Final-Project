#include "Password.h"


Password::Password()
{
}

Password::Password(const string & unEncodedPassword)
{
	encodePassword(unEncodedPassword);
}


Password::~Password()
{
}

void Password::encodePassword(const string & unEncodedPassword)
{
	hash<string> hasher;

	this->hashedString = hasher(unEncodedPassword);
}

string Password::getHashedPassword()
{
	return to_string(hashedString);
}
