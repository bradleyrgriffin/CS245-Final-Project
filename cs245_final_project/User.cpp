#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include "Properties.h"


User::User()
{
}

User::User(const string & username, const string & password)
{
	this->password = Password(password);
	this->username = username;
}


User::~User()
{
}

void User::setUsername(const string & username)
{
	this->username = username;
}

void User::setPassword(const string & password)
{
	this->password = Password(password);
}

bool User::verifyLogin()
{
    Properties props = Properties();
    auto properties = props.getProperties();

    cout << "The hash of the entered password: " << this->password.getHashedPassword() << endl;
    if (properties["password"] != this->password.getHashedPassword()) {
		return false;
	}
	
    if (properties["username"] != this->username) {
		return false;
	}

	return true;


}
